#include "bfenumerate-impl.h"
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

NS_IMPL_ISUPPORTS1(CBFENUMERATE, BFEnumerate)

CBFENUMERATE::CBFENUMERATE()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Component Created")));
}

CBFENUMERATE::~CBFENUMERATE()
{
    if (mTimer) mTimer->Cancel();
    DNSServiceRefDeallocate(mSdRef);
    Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Component Destroyed")));
}

/* void enumerate (); */
NS_IMETHODIMP CBFENUMERATE::Enumerate()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Started")));
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
    if (mType == PR_TRUE)
    {
        err = DNSServiceEnumerateDomains(&mSdRef, kDNSServiceFlagsRegistrationDomains, mInterfaceIndex, (DNSServiceDomainEnumReply) Callback, this);
    }
    else
    {
        err = DNSServiceEnumerateDomains(&mSdRef, kDNSServiceFlagsBrowseDomains, mInterfaceIndex, (DNSServiceDomainEnumReply) Callback, this);
    }    
    if (err != kDNSServiceErr_NoError) return NS_ERROR_FAILURE;
    StartTimer();
    return NS_OK;
}

/* attribute BFEnumerateCallback callback; */
NS_IMETHODIMP CBFENUMERATE::GetCallback(BFEnumerateCallback * *aCallback)
{
    *aCallback = mCallback;
    return NS_OK;
}
NS_IMETHODIMP CBFENUMERATE::SetCallback(BFEnumerateCallback * aCallback)
{
    mCallback = aCallback;
    return NS_OK;
}

/* attribute PRBool type; */
NS_IMETHODIMP CBFENUMERATE::GetType(PRBool *aType)
{
    *aType = mType;
    return NS_OK;
}
NS_IMETHODIMP CBFENUMERATE::SetType(PRBool aType)
{
    mType = aType;
    return NS_OK;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP CBFENUMERATE::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
    *aInterfaceIndex = mInterfaceIndex; // should check *
    return NS_OK;
}
NS_IMETHODIMP CBFENUMERATE::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
    mInterfaceIndex = aInterfaceIndex;
    return NS_OK;
}

void DNSSD_API CBFENUMERATE::Callback (
    DNSServiceRef inSdRef,
    DNSServiceFlags inFlags,
    uint32_t inInterfaceIndex,
    DNSServiceErrorType inErrorCode,
    const char * inReplyDomain,
    void * inContext)
{
    CBFENUMERATE * self;
    self = reinterpret_cast <CBFENUMERATE*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Component Recieved Callback")));
    if (self->mCallback)
    {
        if (inErrorCode == kDNSServiceErr_NoError)
        {
            PRBool oAdd = PR_FALSE;
            nsString oRegistrationDomain;
            if (inFlags & kDNSServiceFlagsAdd)
            {
                oAdd = PR_TRUE;
            }
            oRegistrationDomain.Assign(NS_ConvertUTF8toUTF16(inReplyDomain));
            self->mCallback->Callback(0, oAdd, inInterfaceIndex, self->mType, oRegistrationDomain);
        }
        else
        {
            self->mCallback->Callback(99, PR_FALSE, -1, PR_FALSE, EMPTY_STRING);
        }
    }
}

void CBFENUMERATE::PollSelect(void *inContext)
{
    CBFENUMERATE * self;

    self = reinterpret_cast <CBFENUMERATE*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Component Polling for Result")));
    struct timeval tv;
    int result; 
    fd_set readfds;

    int dns_sd_fd = DNSServiceRefSockFD(self->mSdRef);  
    int nfds = dns_sd_fd + 1;

    FD_ZERO(&readfds);
    FD_SET(dns_sd_fd, &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 1;

    result = select(nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);

    if (result >= 0)
    {
        if (result > 0)
        {
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Component Results Recieved > 0 Results")));
            DNSServiceErrorType err = kDNSServiceErr_NoError;
            if (self->mSdRef && FD_ISSET(dns_sd_fd , &readfds))
            {
                err = DNSServiceProcessResult(self->mSdRef);
            }
        }
        else
        {
        self->Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Component Results Recieved 0 Results")));
        }
    }
    else
    {
        // Log(nsPrintfCString("select() returned %d errno %d %s\n", result, errno, strerror(errno)));
        if (errno != EINTR) 
        {
        self->Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Component Recieved an error other than Interrupted System Call (EINTR)")));
        if (mTimer) mTimer->Cancel(); // should probably call the callback with something useful
        }
    }
}    

nsresult CBFENUMERATE::StartTimer()
{
    mTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (!mTimer)
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate StartTimer was unable to get an instance of Timer")));
        return NS_ERROR_FAILURE;
    }
    else
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate StartTimer got a Timer instance")));
        return mTimer->InitWithFuncCallback(this->TimeoutHandler, this, 100, 
                                        nsITimer::TYPE_REPEATING_SLACK);
    }
}


void CBFENUMERATE::TimeoutHandler(nsITimer *aTimer, void *aClosure)
{
    CBFENUMERATE *self = reinterpret_cast<CBFENUMERATE*>(aClosure);
    if (!self) {
        NS_ERROR("no self\n");
        return;
    }
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Timeout Handler Fired")));
    self->PollSelect(self);
}

void CBFENUMERATE::Log(const PRUnichar* message)
{
    nsCOMPtr<nsIPrefService> prefService = do_GetService("@mozilla.org/preferences-service;1");
    if (prefService)
    {
        nsCOMPtr<nsIPrefBranch> prefs;
        prefService->GetBranch("extensions.bonjourfoxy.log.", getter_AddRefs(prefs));
        PRBool doLog;
        prefs->GetBoolPref("enumerate", &doLog);
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
