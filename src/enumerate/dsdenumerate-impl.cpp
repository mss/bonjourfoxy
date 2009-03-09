#include "dsdenumerate-impl.h"

//#include "nsIServiceManager.h"

#include "nsComponentManagerUtils.h"

// #include "nsStringAPI.h"

// #include "dns_sd.h"

#include <stdio.h>

#include "dsdmanager.h"

#include "nsIArray.h"
#include "nsIMutableArray.h"
#include "nsIVariant.h"
// #include "nsISupportsPrimitives.h"

#ifndef _WIN32
#include <sys/time.h>
#endif

#include <errno.h>			// For errno, EINTR

NS_IMPL_ISUPPORTS1(CDSDENUMERATE, IDSDENUMERATE)

CDSDENUMERATE::CDSDENUMERATE()
{
  /* member initializers and constructor code */
  //printf("CDSDENUMERATE::CDSDENUMERATE()\n");
  mSdRef = NULL;
  mType = 0;
  mInterfaceIndex = NULL;
  mLastFlags = NULL;
  mLastInterface = NULL;
  mLastErrorcode = NULL;
  mLastDomain = NS_LITERAL_STRING("");
  mStatus = 0;
}

CDSDENUMERATE::~CDSDENUMERATE()
{
  /* destructor code */
  //printf("CDSDENUMERATE::~CDSDENUMERATE()\n");
  mStatus = 99;
  if (mTimer)
    mTimer->Cancel();
  if (mSdRef)
    DNSServiceRefDeallocate(mSdRef);  
}

/* void start (); */
NS_IMETHODIMP CDSDENUMERATE::Start()
{
  //printf("CDSDENUMERATE::Start()\n");
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
    if (mType == 0) {
        return NS_ERROR_INVALID_ARG;
    } 
    if (mStatus == 99) {
        return NS_ERROR_FAILURE;
    }
    if (mType == 2) {
        err = DNSServiceEnumerateDomains(&mSdRef, kDNSServiceFlagsRegistrationDomains, mInterfaceIndex, (DNSServiceDomainEnumReply) Callback, this);
    } else {
        err = DNSServiceEnumerateDomains(&mSdRef, kDNSServiceFlagsBrowseDomains, mInterfaceIndex, (DNSServiceDomainEnumReply) Callback, this);
    }
	if (err != kDNSServiceErr_NoError) {
        mLastErrorcode = err;
        mStatus = 99;
        return NS_ERROR_FAILURE;
	}
	mStatus = 1;
	StartTimer();
    return NS_OK;
}

/* void stop (); */
NS_IMETHODIMP CDSDENUMERATE::Stop()
{
    //printf("CDSDENUMERATE::Stop()\n");
    mStatus = 2;
    return NS_OK;
}

/* attribute long type; */
NS_IMETHODIMP CDSDENUMERATE::GetType(PRInt32 *aType)
{
  //printf("CDSDENUMERATE::GetType()\n");
    *aType = mType;
    return NS_OK;
}
NS_IMETHODIMP CDSDENUMERATE::SetType(PRInt32 aType)
{
  //printf("CDSDENUMERATE::SetType()\n");
    if (aType == 1) {
        mType = 1;
    } else if (aType == 2) {
        mType = 2;
    } else {
        return NS_ERROR_INVALID_ARG;
    }
    return NS_OK;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP CDSDENUMERATE::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
  //printf("CDSDENUMERATE::GetInterfaceIndex()\n");
    *aInterfaceIndex = mInterfaceIndex;
    return NS_OK;
}
NS_IMETHODIMP CDSDENUMERATE::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
  //printf("CDSDENUMERATE::SetInterfaceIndex()\n");
    mInterfaceIndex = aInterfaceIndex;
    return NS_OK;
}

/* readonly attribute long lastFlags; */
NS_IMETHODIMP CDSDENUMERATE::GetLastFlags(PRInt32 *aLastFlags)
{
  //printf("CDSDENUMERATE::GetLastFlags()\n");
    *aLastFlags = mLastFlags;
    return NS_OK;
}

/* readonly attribute long lastInterface; */
NS_IMETHODIMP CDSDENUMERATE::GetLastInterface(PRInt32 *aLastInterface)
{
  //printf("CDSDENUMERATE::GetLastInterface()\n");
    *aLastInterface = mLastInterface;
    return NS_OK;
}

/* readonly attribute long lastErrorcode; */
NS_IMETHODIMP CDSDENUMERATE::GetLastErrorcode(PRInt32 *aLastErrorcode)
{
  //printf("CDSDENUMERATE::GetLastErrorcode()\n");
    *aLastErrorcode = mLastErrorcode;
    return NS_OK;
}

/* readonly attribute AString lastDomain; */
NS_IMETHODIMP CDSDENUMERATE::GetLastDomain(nsAString & aLastDomain)
{
  //printf("CDSDENUMERATE::GetLastDomain()\n");
    aLastDomain = mLastDomain;
    return NS_OK;
}

/* readonly attribute long status; */
NS_IMETHODIMP CDSDENUMERATE::GetStatus(PRInt32 *aStatus)
{
  //printf("CDSDENUMERATE::GetStatus()\n");
    *aStatus = mStatus;
    return NS_OK;
}

void DNSSD_API CDSDENUMERATE::Callback (
    DNSServiceRef inSdRef,
    DNSServiceFlags inFlags,
    uint32_t inInterfaceIndex,
    DNSServiceErrorType inErrorCode,
    const char * inReplyDomain,
    void * inContext)
{
  //printf("CDSDENUMERATE::Callback()\n");
	CDSDENUMERATE * self;
	self = reinterpret_cast <CDSDENUMERATE*>( inContext );
	nsCOMPtr<nsIServiceManager> servMan;
    nsresult rv = NS_GetServiceManager(getter_AddRefs(servMan)); 
    if (NS_FAILED(rv)) {
        self->mStatus = 99;
    } else {
        nsCOMPtr<IDSDMANAGER> dsdmanager;
        rv = servMan->GetServiceByContractID("@andrew.tj.id.au/dsdmanager;1", NS_GET_IID(IDSDMANAGER), getter_AddRefs(dsdmanager));


        nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);

        self->mLastErrorcode = inErrorCode;        
        if (inErrorCode == kDNSServiceErr_NoError)
        {

            nsCOMPtr<nsIWritableVariant> oFlags = do_CreateInstance("@mozilla.org/variant;1");
            if (inFlags & kDNSServiceFlagsAdd)  {
                oFlags->SetAsAUTF8String(NS_ConvertUTF16toUTF8(NS_LITERAL_STRING("add")));
            } else {
                oFlags->SetAsAUTF8String(NS_ConvertUTF16toUTF8(NS_LITERAL_STRING("rmv")));
            }
            array->AppendElement(oFlags, PR_FALSE);
            self->mLastFlags = inFlags;
    
            nsCOMPtr<nsIWritableVariant> oType = do_CreateInstance("@mozilla.org/variant;1");
            if (self->mType == 2) {
                oType->SetAsAUTF8String(NS_ConvertUTF16toUTF8(NS_LITERAL_STRING("registration")));
            } else {
                oType->SetAsAUTF8String(NS_ConvertUTF16toUTF8(NS_LITERAL_STRING("browse")));
            }
            array->AppendElement(oType, PR_FALSE);

            nsCOMPtr<nsIWritableVariant> oInterfaceIndex = do_CreateInstance("@mozilla.org/variant;1");
            oInterfaceIndex->SetAsInt32(inInterfaceIndex);
            array->AppendElement(oInterfaceIndex, PR_FALSE);        
            self->mLastInterface = inInterfaceIndex;
        
            nsCOMPtr<nsIWritableVariant> oReplyDomain = do_CreateInstance("@mozilla.org/variant;1");        
            oReplyDomain->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(inReplyDomain)) );
            array->AppendElement(oReplyDomain, PR_FALSE);
            self->mLastDomain = NS_ConvertUTF8toUTF16(inReplyDomain);        
            
        	dsdmanager->HandleEvent(NS_LITERAL_STRING("enumerate"),PR_FALSE,array);
        } else {
            self->mStatus=99;
            if (self->mTimer)
                self->mTimer->Cancel();
            nsCOMPtr<nsIWritableVariant> oErrorCode = do_CreateInstance("@mozilla.org/variant;1");
            oErrorCode->SetAsInt32(inErrorCode);
            array->AppendElement(oErrorCode, PR_FALSE);        
            // DNSServiceRefDeallocate(self->mSdRef);
        	dsdmanager->HandleEvent(NS_LITERAL_STRING("enumerate"),PR_TRUE,array);
        }            
    }
}

void CDSDENUMERATE::PollSelect(void *inContext)
{
  //printf("CDSDENUMERATE::PollSelect()\n");
	CDSDENUMERATE * self;
	self = reinterpret_cast <CDSDENUMERATE*>( inContext );
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

	if (result > 0)
		{
		//printf("Results: %d\n", result);
		DNSServiceErrorType err = kDNSServiceErr_NoError;
		if (self->mSdRef && FD_ISSET(dns_sd_fd , &readfds)) {
			err = DNSServiceProcessResult(self->mSdRef);
			}
        /*
		if (err) {
			//printf("DNSServiceProcessResult returned %d\n", err);
			}
		*/
		}
	else if (result == 0)
	    {
		//printf("No Results\n");
	    }
	else
		{		  
		//printf("select() returned %d errno %d %s\n", result, errno, strerror(errno));
		if (errno != EINTR) self->mStatus = 99;
		}
    if (self->mStatus != 1)    {
        // DNSServiceRefDeallocate(self->mSdRef);
		if (mTimer)
			mTimer->Cancel();
    }
}    

nsresult CDSDENUMERATE::StartTimer()
{
  //printf("CDSDENUMERATE::StartTimer()\n");
    mTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (!mTimer)
        return NS_ERROR_FAILURE;
    return mTimer->InitWithFuncCallback(this->TimeoutHandler, this, 100, 
                                        nsITimer::TYPE_REPEATING_SLACK);
}


void CDSDENUMERATE::TimeoutHandler(nsITimer *aTimer, void *aClosure)
{
  //printf("CDSDENUMERATE::TimeoutHandler()\n");
    CDSDENUMERATE *self = reinterpret_cast<CDSDENUMERATE*>(aClosure);
    if (!self) {
        NS_ERROR("no self\n");
        return;
    }
    self->PollSelect(self);
}
