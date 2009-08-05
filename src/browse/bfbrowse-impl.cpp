#include "bfbrowse-impl.h"
#include "nsComponentManagerUtils.h" // for do_CreateInstance
// #include "nsITimer.h"
#include "nsServiceManagerUtils.h"   // for do_GetService
#include "nsIConsoleService.h"
#include "nsIPrefService.h"
#include <errno.h>                   // For errno, EINTR
#include <stdio.h>                   // for snprintf - applies on win32?
// #include "nsStringAPI.h"

#ifndef _WIN32
#include <sys/time.h>
#endif

#include <errno.h>          // For errno, EINTR

#define EMPTY_STRING NS_LITERAL_STRING("")

NS_IMPL_ISUPPORTS1(CBFBROWSE, BFBrowse)

CBFBROWSE::CBFBROWSE()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Browse Component Created")));
}

CBFBROWSE::~CBFBROWSE()
{
    if (mTimer) mTimer->Cancel();
    DNSServiceRefDeallocate(mSdRef);
    Log(ToNewUnicode(NS_LITERAL_STRING("Browse Component Destroyed")));
}

/* void browse (); */
NS_IMETHODIMP CBFBROWSE::Browse()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Browse Started")));
    if (!mCallback) return NS_ERROR_FAILURE;
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
    err = DNSServiceBrowse(&mSdRef, 0, mInterfaceIndex, ToNewUTF8String(mRegistrationType), ToNewUTF8String(mRegistrationDomain), (DNSServiceBrowseReply) Callback, this);
    if (err != kDNSServiceErr_NoError) return NS_ERROR_FAILURE;
    StartTimer();
    return NS_OK;
}

/* attribute BFBrowseCallback callback; */
NS_IMETHODIMP CBFBROWSE::GetCallback(BFBrowseCallback * *aCallback)
{
    *aCallback = mCallback;
    return NS_OK;
}
NS_IMETHODIMP CBFBROWSE::SetCallback(BFBrowseCallback * aCallback)
{
    mCallback = aCallback;
    return NS_OK;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP CBFBROWSE::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
    *aInterfaceIndex = mInterfaceIndex;
    return NS_OK;
}
NS_IMETHODIMP CBFBROWSE::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
    mInterfaceIndex = aInterfaceIndex;
    return NS_OK;
}

/* attribute AString registrationType; */
NS_IMETHODIMP CBFBROWSE::GetRegistrationType(nsAString & aRegistrationType)
{
    aRegistrationType = mRegistrationType;
    return NS_OK;
}
NS_IMETHODIMP CBFBROWSE::SetRegistrationType(const nsAString & aRegistrationType)
{
    mRegistrationType = aRegistrationType;
    return NS_OK;
}

/* attribute AString registrationDomain; */
NS_IMETHODIMP CBFBROWSE::GetRegistrationDomain(nsAString & aRegistrationDomain)
{
    aRegistrationDomain = mRegistrationDomain;
    return NS_OK;
}
NS_IMETHODIMP CBFBROWSE::SetRegistrationDomain(const nsAString & aRegistrationDomain)
{
    mRegistrationDomain = aRegistrationDomain;
    return NS_OK;
}


void DNSSD_API CBFBROWSE::Callback(
    DNSServiceRef           inSdRef,
    DNSServiceFlags         inFlags,
    uint32_t                inInterfaceIndex,
    DNSServiceErrorType     inErrorCode,
    const char *            inReplyName,
    const char *            inReplyType,
    const char *            inReplyDomain,
    void *                  inContext)
{

    CBFBROWSE * self;
    self = reinterpret_cast <CBFBROWSE*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Browse Component Recieved Callback")));
    if (self->mCallback)
    {
        if (inErrorCode == kDNSServiceErr_NoError)
        {
            PRBool oAdd = PR_FALSE;
            if (inFlags & kDNSServiceFlagsAdd) oAdd = PR_TRUE;
            nsString oServiceName;
            nsString oRegistrationType;
            nsString oRegistrationDomain;
            oServiceName.Assign(NS_ConvertUTF8toUTF16(inReplyName));
            oRegistrationType.Assign(NS_ConvertUTF8toUTF16(inReplyType));
            oRegistrationDomain.Assign(NS_ConvertUTF8toUTF16(inReplyDomain));
            self->mCallback->Callback(0, oAdd, inInterfaceIndex, oServiceName, oRegistrationType, oRegistrationDomain);
        }
        else
        {
            if (self->mTimer) self->mTimer->Cancel();
            self->mCallback->Callback(99, PR_FALSE, -1, EMPTY_STRING, EMPTY_STRING, EMPTY_STRING);
        }
    }
}

void CBFBROWSE::PollSelect(void *inContext)
{
    CBFBROWSE * self;
    self = reinterpret_cast <CBFBROWSE*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Browse Component Polling for Result")));
    struct timeval tv;
    int result; 
    fd_set readfds;

    int dns_sd_fd = DNSServiceRefSockFD(self->mSdRef);  
    int nfds = dns_sd_fd + 1;

    FD_ZERO(&readfds);
    FD_SET(dns_sd_fd, &readfds);
    tv.tv_sec = 0;  // was 0
    tv.tv_usec = 1; // was 1

    result = select(nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);

    if (result >= 0)
    {
        //printf("Results: %d\n", result);
        if (result > 0)
        {
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Browse Component Results Recieved > 0 Results")));
            DNSServiceErrorType err = kDNSServiceErr_NoError;
            if (self->mSdRef && FD_ISSET(dns_sd_fd , &readfds)) err = DNSServiceProcessResult(self->mSdRef);
        }
        else
        {
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Browse Component Results Recieved 0 Results")));
        }
    }
    else
    {         
        //printf("select() returned %d errno %d %s\n", result, errno, strerror(errno));
        if (errno != EINTR)
        {
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Browse Component Recieved an error other than Interrupted System Call (EINTR)")));
            if (mTimer) mTimer->Cancel();
        }
    }
} 

nsresult CBFBROWSE::StartTimer()
{
    mTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (!mTimer)
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Browe StartTimer was unable to get an instance of Timer")));
        return NS_ERROR_OUT_OF_MEMORY;
    }
    else
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Browse StartTimer got a Timer instance")));
        return mTimer->InitWithFuncCallback(this->TimeoutHandler,
                                            this,
                                            100, 
                                            nsITimer::TYPE_REPEATING_SLACK);
    }
}

void CBFBROWSE::TimeoutHandler(nsITimer *aTimer, void *aClosure)
{
    //printf("CDSDBROWSE::TimeoutHandler()\n");
    CBFBROWSE *self = reinterpret_cast<CBFBROWSE*>(aClosure);
    if (!self) {
        NS_ERROR("no self\n");
        return;
    }
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Browse Timeout Handler Fired")));
    self->PollSelect(self);
}

void CBFBROWSE::Log(const PRUnichar* message)
{
    nsCOMPtr<nsIPrefService> prefService = do_GetService("@mozilla.org/preferences-service;1");
    if (prefService)
    {
        nsCOMPtr<nsIPrefBranch> prefs;
        prefService->GetBranch("extensions.bonjourfoxy.log.", getter_AddRefs(prefs));
        PRBool doLog;
        prefs->GetBoolPref("browse", &doLog);
        if (doLog == PR_TRUE)
        {
            nsCOMPtr<nsIConsoleService> consoleService = do_GetService("@mozilla.org/consoleservice;1");
            if (consoleService)
            {
                consoleService->LogStringMessage(message);
            }
        }
    }
}
