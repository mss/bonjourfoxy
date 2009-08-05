#include "bfresolve-impl.h"
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

NS_IMPL_ISUPPORTS1(CBFRESOLVE, BFResolve)

CBFRESOLVE::CBFRESOLVE()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Component Created")));
    mInterfaceIndex = 0;
    mServiceName = EMPTY_STRING;
    mRegistrationType = EMPTY_STRING;
    mRegistrationDomain = EMPTY_STRING;
}

CBFRESOLVE::~CBFRESOLVE()
{
    if (mTimer) mTimer->Cancel();
    DNSServiceRefDeallocate(mSdRef);
    Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Component Destroyed")));
}

/* void resolve (); */
NS_IMETHODIMP CBFRESOLVE::Resolve()
{
    Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Started")));
    if (!mCallback) return NS_ERROR_FAILURE;
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
    err = DNSServiceResolve(&mSdRef, 0, mInterfaceIndex, ToNewUTF8String(mServiceName) , ToNewUTF8String(mRegistrationType), ToNewUTF8String(mRegistrationDomain), (DNSServiceResolveReply) Callback, this);
    if (err != kDNSServiceErr_NoError) return NS_ERROR_FAILURE;
    StartTimer();
    return NS_OK;
}

/* attribute BFResolveCallback callback; */
NS_IMETHODIMP CBFRESOLVE::GetCallback(BFResolveCallback * *aCallback)
{
    *aCallback = mCallback;
    return NS_OK;
}
NS_IMETHODIMP CBFRESOLVE::SetCallback(BFResolveCallback * aCallback)
{
    mCallback = aCallback;
    return NS_OK;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP CBFRESOLVE::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
    *aInterfaceIndex = mInterfaceIndex;
    return NS_OK;
}
NS_IMETHODIMP CBFRESOLVE::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
    mInterfaceIndex = aInterfaceIndex;
    return NS_OK;
}

/* attribute AString serviceName; */
NS_IMETHODIMP CBFRESOLVE::GetServiceName(nsAString & aServiceName)
{
    aServiceName = mServiceName;
    return NS_OK;
}
NS_IMETHODIMP CBFRESOLVE::SetServiceName(const nsAString & aServiceName)
{
    mServiceName = aServiceName;
    return NS_OK;
}

/* attribute AString registrationType; */
NS_IMETHODIMP CBFRESOLVE::GetRegistrationType(nsAString & aRegistrationType)
{
    aRegistrationType = mRegistrationType;
    return NS_OK;
}
NS_IMETHODIMP CBFRESOLVE::SetRegistrationType(const nsAString & aRegistrationType)
{
    mRegistrationType = aRegistrationType;
    return NS_OK;
}

/* attribute AString registrationDomain; */
NS_IMETHODIMP CBFRESOLVE::GetRegistrationDomain(nsAString & aRegistrationDomain)
{
    aRegistrationDomain = mRegistrationDomain;
    return NS_OK;
}
NS_IMETHODIMP CBFRESOLVE::SetRegistrationDomain(const nsAString & aRegistrationDomain)
{
    mRegistrationDomain = aRegistrationDomain;
    return NS_OK;
}

void DNSSD_API CBFRESOLVE::Callback(
        DNSServiceRef           inSdRef,
        DNSServiceFlags         inFlags,
        uint32_t                inInterfaceIndex,
        DNSServiceErrorType     inErrorCode,
        const char *            inFQDN, 
        const char *            inHostname, 
        uint16_t                inPort,
        uint16_t                inTxtLen,
        const char *            inTxtRecord,
        void *                  inContext )
{
    CBFRESOLVE * self;
    self = reinterpret_cast <CBFRESOLVE*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Component Recieved Callback")));
    if (inErrorCode == kDNSServiceErr_NoError)
    {
        if (self->mTimer) self->mTimer->Cancel();
        if (self->mCallback)
        {
            nsString oHostname;
            oHostname.Assign(NS_ConvertUTF8toUTF16(inHostname));
            union { uint16_t s; u_char b[2]; } port = { inPort };
            uint16_t oPort = ((uint16_t)port.b[0]) << 8 | port.b[1];
            nsString oTxtKey;
            nsString oTxtValue;
            char tKey[256];
            int index=0;
            uint8_t valueLen;
            const void *voidValue = 0;            
            // Bonjour API indicates only the 'primary text record' is supplied to the callback
            if (TXTRecordGetItemAtIndex(inTxtLen,
                                        inTxtRecord,
                                        index++,
                                        256,
                                        tKey,
                                        &valueLen,
                                        &voidValue) == kDNSServiceErr_NoError) 
            {
                char *tValue = NULL;
                tValue = new char[valueLen+1];
                snprintf (tValue, valueLen+1, "%.*s\n", (int) valueLen, voidValue);
                tValue[valueLen] = '\0';
                oTxtKey.Assign(NS_ConvertUTF8toUTF16(tKey));
                oTxtValue.Assign(NS_ConvertUTF8toUTF16(tValue));
            }
            self->mCallback->Callback(0, inInterfaceIndex, oHostname, oPort, oTxtKey, oTxtValue);
        }
        DNSServiceRefDeallocate(self->mSdRef);
    }
    else
    {
        if (self->mTimer) self->mTimer->Cancel();
        if (self->mCallback)
        {
            self->mCallback->Callback(99, -1, EMPTY_STRING, -1, EMPTY_STRING, EMPTY_STRING);
        }
    }
}

void CBFRESOLVE::PollSelect(void *inContext)
{
    CBFRESOLVE * self;
    self = reinterpret_cast <CBFRESOLVE*>( inContext );
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Component Polling for Result")));
    struct timeval tv;
    int result; 
    fd_set readfds;

    int dns_sd_fd = DNSServiceRefSockFD(self->mSdRef);  
    int nfds = dns_sd_fd + 1;

    FD_ZERO(&readfds);
    FD_SET(dns_sd_fd, &readfds);
    tv.tv_sec = 0;  // was set to 0
    tv.tv_usec = 1; // was set to 1

    result = select(nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);

    if (result >= 0)
    {
        if (result > 0)
        {
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Component Results Recieved > 0 Results")));
            DNSServiceErrorType err = kDNSServiceErr_NoError;
            if (self->mSdRef && FD_ISSET(dns_sd_fd , &readfds))
            {
                err = DNSServiceProcessResult(self->mSdRef);
            }
        }
        else
        {
            self->Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Component Results Recieved 0 Results")));
        }
    }
    else
    {
        if (errno != EINTR) 
        {
        self->Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Component Recieved an error other than Interrupted System Call (EINTR)")));
        if (mTimer) mTimer->Cancel(); // should probably call the callback with something useful
        }
    }
}    

nsresult CBFRESOLVE::StartTimer()
{
    mTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (!mTimer)
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Resolve StartTimer was unable to get an instance of Timer")));
        return NS_ERROR_OUT_OF_MEMORY;
    }
    else
    {
        Log(ToNewUnicode(NS_LITERAL_STRING("Resolve StartTimer got a Timer instance")));
        return mTimer->InitWithFuncCallback(this->TimeoutHandler,
                                            this,
                                            100, 
                                            nsITimer::TYPE_REPEATING_SLACK);
    }
}

void CBFRESOLVE::TimeoutHandler(nsITimer *aTimer, void *aClosure)
{
    CBFRESOLVE *self = reinterpret_cast<CBFRESOLVE*>(aClosure);
    if (!self) {
        NS_ERROR("No self\n");
        return;
    }
    self->Log(ToNewUnicode(NS_LITERAL_STRING("Resolve Timeout Handler Fired")));
    self->PollSelect(self);
}

void CBFRESOLVE::Log(const PRUnichar* message)
{
    nsCOMPtr<nsIPrefService> prefService = do_GetService("@mozilla.org/preferences-service;1");
    if (prefService)
    {
        nsCOMPtr<nsIPrefBranch> prefs;
        prefService->GetBranch("extensions.bonjourfoxy.log.", getter_AddRefs(prefs));
        PRBool doLog;
        prefs->GetBoolPref("resolve", &doLog);
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
