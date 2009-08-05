#include "bfregister-impl.h"
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
#else
#define snprintf _snprintf
#endif

#define EMPTY_STRING NS_LITERAL_STRING("")

typedef union { unsigned char b[2]; unsigned short NotAnInteger; } Opaque16;

NS_IMPL_ISUPPORTS1(CBFREGISTER, BFRegister)

CBFREGISTER::CBFREGISTER()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Register Component Created")));
}

CBFREGISTER::~CBFREGISTER()
{
    if (mTimer) mTimer->Cancel();
    DNSServiceRefDeallocate(mSdRef);
    Log(ToNewUnicode(NS_LITERAL_STRING("Register Component Destroyed")));
}

/* void register (); */
NS_IMETHODIMP CBFREGISTER::Register()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Enumerate Started")));
    if (!mCallback) return NS_ERROR_FAILURE;
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
    DNSServiceFlags flags = 0;
    if (mAutorename == PR_FALSE)
    {
        flags += kDNSServiceFlagsNoAutoRename; // is this the right operator to use??
    }
    Opaque16 registerPort = { { mTargetPort >> 8, mTargetPort & 0xFF } };
    TXTRecordRef txt;
    TXTRecordCreate(&txt,0,0);      
    void* tTxtRecordValue = ToNewUTF8String(mTxtRecordValue);
    err = TXTRecordSetValue(&txt, ToNewUTF8String(mTxtRecordKey), mTxtRecordValue.Length(), tTxtRecordValue); 
    if (err != kDNSServiceErr_NoError) return NS_ERROR_FAILURE;
    err = DNSServiceRegister(&mSdRef,
                             mInterfaceIndex,
                             flags,
                             ToNewUTF8String(mServiceName),
                             ToNewUTF8String(mRegistrationType),
                             ToNewUTF8String(mRegistrationDomain),
                             ToNewUTF8String(mTargetHost),
                             registerPort.NotAnInteger,
                             TXTRecordGetLength(&txt),
                             TXTRecordGetBytesPtr(&txt),
                             (DNSServiceRegisterReply) Callback,
                             this);
    if (err != kDNSServiceErr_NoError) return NS_ERROR_FAILURE;
    StartTimer();
    return NS_OK;
}

/* attribute BFRegisterCallback callback; */
NS_IMETHODIMP CBFREGISTER::GetCallback(BFRegisterCallback * *aCallback)
{
    *aCallback = mCallback;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetCallback(BFRegisterCallback * aCallback)
{
    mCallback = aCallback;
    return NS_OK;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP CBFREGISTER::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
    *aInterfaceIndex = mInterfaceIndex;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
    mInterfaceIndex = aInterfaceIndex;
    return NS_OK;
}

/* attribute PRBool autorename; */
NS_IMETHODIMP CBFREGISTER::GetAutorename(PRBool *aAutorename)
{
    *aAutorename = mAutorename;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetAutorename(PRBool aAutorename)
{
    mAutorename = aAutorename;
    return NS_OK;
}

/* attribute AString name; */
NS_IMETHODIMP CBFREGISTER::GetServiceName(nsAString & aServiceName)
{
    aServiceName = mServiceName;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetServiceName(const nsAString & aServiceName)
{
    mServiceName = aServiceName;
    return NS_OK;
}

/* attribute AString registrationType; */
NS_IMETHODIMP CBFREGISTER::GetRegistrationType(nsAString & aRegistrationType)
{
    aRegistrationType = mRegistrationType;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetRegistrationType(const nsAString & aRegistrationType)
{
    mRegistrationType = aRegistrationType;
    return NS_OK;
}

/* attribute AString registrationDomain; */
NS_IMETHODIMP CBFREGISTER::GetRegistrationDomain(nsAString & aRegistrationDomain)
{
    aRegistrationDomain = mRegistrationDomain;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetRegistrationDomain(const nsAString & aRegistrationDomain)
{
    mRegistrationDomain = aRegistrationDomain;
    return NS_OK;
}

/* attribute AString targetHost; */
NS_IMETHODIMP CBFREGISTER::GetTargetHost(nsAString & aTargetHost)
{
    aTargetHost = mTargetHost;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetTargetHost(const nsAString & aTargetHost)
{
    mTargetHost = aTargetHost;
    return NS_OK;
}

/* attribute long targetPort; */
NS_IMETHODIMP CBFREGISTER::GetTargetPort(PRInt32 *aTargetPort)
{
    *aTargetPort = mTargetPort;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetTargetPort(PRInt32 aTargetPort)
{
    mTargetPort = aTargetPort;
    return NS_OK;
}

/* attribute AString txtRecordKey; */
NS_IMETHODIMP CBFREGISTER::GetTxtRecordKey(nsAString & aTxtRecordKey)
{
    aTxtRecordKey = mTxtRecordKey;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetTxtRecordKey(const nsAString & aTxtRecordKey)
{
    mTxtRecordKey = aTxtRecordKey;
    return NS_OK;
}

/* attribute AString txtRecordValue; */
NS_IMETHODIMP CBFREGISTER::GetTxtRecordValue(nsAString & aTxtRecordValue)
{
    aTxtRecordValue = mTxtRecordValue;
    return NS_OK;
}
NS_IMETHODIMP CBFREGISTER::SetTxtRecordValue(const nsAString & aTxtRecordValue)
{
    mTxtRecordValue = aTxtRecordValue;
    return NS_OK;
}

void DNSSD_API CBFREGISTER::Callback(
                DNSServiceRef                   inSdRef,
                DNSServiceFlags                 inFlags,
                DNSServiceErrorType             inErrorCode,
                const char *                    inName, 
                const char *                    inRegType,
                const char *                    inRegDomain,
                void *                          inContext )
{
    CBFREGISTER * self;
    self = reinterpret_cast <CBFREGISTER*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Register Component Recieved Callback")));
    if (self->mCallback)
    {
        if (inErrorCode & kDNSServiceErr_NoError) // comparison operator needs to be checked in other files
        {
            PRBool oAdd = PR_FALSE;
            if (inFlags & kDNSServiceFlagsAdd) oAdd = PR_TRUE;
            self->mCallback->Callback(0, self->mInterfaceIndex, oAdd, NS_ConvertUTF8toUTF16(inName), NS_ConvertUTF8toUTF16(inRegType), NS_ConvertUTF8toUTF16(inRegDomain));            
        }
        else
        {
            self->mCallback->Callback(99, -1, PR_FALSE, EMPTY_STRING, EMPTY_STRING, EMPTY_STRING);
        }
    }
}

void CBFREGISTER::PollSelect(void *inContext)
{
    CBFREGISTER * self;
    self = reinterpret_cast <CBFREGISTER*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Register Component Polling for Result")));
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
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Register Component Results Recieved > 0 Results")));
            DNSServiceErrorType err = kDNSServiceErr_NoError;
            if (self->mSdRef && FD_ISSET(dns_sd_fd , &readfds))
            {
                err = DNSServiceProcessResult(self->mSdRef);
            }
        }
        else
        {
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Register Component Results Recieved 0 Results")));
        }
    }
    else
    {
        if (errno != EINTR) 
        {
        self->Log(ToNewUnicode(NS_LITERAL_STRING("Register Component Recieved an error other than Interrupted System Call (EINTR)")));
        if (mTimer) mTimer->Cancel(); // should probably call the callback with something useful
        }
    }
}    

nsresult CBFREGISTER::StartTimer()
{
    mTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (!mTimer)
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Register StartTimer was unable to get an instance of Timer")));
        return NS_ERROR_OUT_OF_MEMORY;
    }
    else
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Register StartTimer got a Timer instance")));
        return mTimer->InitWithFuncCallback(this->TimeoutHandler,
                                            this,
                                            100, 
                                            nsITimer::TYPE_REPEATING_SLACK);
    }
}

void CBFREGISTER::TimeoutHandler(nsITimer *aTimer, void *aClosure)
{
    CBFREGISTER *self = reinterpret_cast<CBFREGISTER*>(aClosure);
    if (!self) {
        NS_ERROR("No self\n");
        return;
    }
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Register Timeout Handler Fired")));
    self->PollSelect(self);
}

void CBFREGISTER::Log(const PRUnichar* message)
{
    nsCOMPtr<nsIPrefService> prefService = do_GetService("@mozilla.org/preferences-service;1");
    if (prefService)
    {
        nsCOMPtr<nsIPrefBranch> prefs;
        prefService->GetBranch("extensions.bonjourfoxy.log.", getter_AddRefs(prefs));
        PRBool doLog;
        prefs->GetBoolPref("register", &doLog);
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
