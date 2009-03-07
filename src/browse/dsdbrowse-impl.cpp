#include "dsdbrowse-impl.h"

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

NS_IMPL_ISUPPORTS1(CDSDBROWSE, IDSDBROWSE)

CDSDBROWSE::CDSDBROWSE()
{
  /* member initializers and constructor code */
  mSdRef = NULL;
  mInterfaceIndex = NULL;
  mRegistrationType = NS_LITERAL_STRING("");
  mRegistrationDomain = NS_LITERAL_STRING("");
  mLastFlags = NULL;
  mLastInterface = NULL;
  mLastErrorcode = NULL;
  mLastName = NS_LITERAL_STRING("");
  mLastRegType = NS_LITERAL_STRING("");
  mLastDomain = NS_LITERAL_STRING("");
  mStatus = 0;
}

CDSDBROWSE::~CDSDBROWSE()
{
  /* destructor code */
  mStatus = 99;
  if (mTimer)
    mTimer->Cancel();
  if (mSdRef)
    DNSServiceRefDeallocate(mSdRef);  
}

/* void start (); */
NS_IMETHODIMP CDSDBROWSE::Start()
{
    if (mStatus == 99) {
        return NS_ERROR_FAILURE;
    }
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
	err = DNSServiceBrowse(&mSdRef, 0, mInterfaceIndex, ToNewUTF8String(mRegistrationType), ToNewUTF8String(mRegistrationDomain), (DNSServiceBrowseReply) Callback, this);
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
NS_IMETHODIMP CDSDBROWSE::Stop()
{
    //printf("CDSDBROWSE::Stop()\n");
    mStatus = 2;
    return NS_OK;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP CDSDBROWSE::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
    *aInterfaceIndex = mInterfaceIndex;
    return NS_OK;
}
NS_IMETHODIMP CDSDBROWSE::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
    mInterfaceIndex = aInterfaceIndex;
    return NS_OK;
}

/* attribute AString registrationType; */
NS_IMETHODIMP CDSDBROWSE::GetRegistrationType(nsAString & aRegistrationType)
{
    aRegistrationType = mRegistrationType;
    return NS_OK;
}
NS_IMETHODIMP CDSDBROWSE::SetRegistrationType(const nsAString & aRegistrationType)
{
	mRegistrationType = aRegistrationType;
    return NS_OK;
}

/* attribute AString registrationDomain; */
NS_IMETHODIMP CDSDBROWSE::GetRegistrationDomain(nsAString & aRegistrationDomain)
{
	aRegistrationDomain = mRegistrationDomain;
    return NS_OK;
}
NS_IMETHODIMP CDSDBROWSE::SetRegistrationDomain(const nsAString & aRegistrationDomain)
{
	mRegistrationDomain = aRegistrationDomain;
    return NS_OK;
}

/* readonly attribute long lastFlags; */
NS_IMETHODIMP CDSDBROWSE::GetLastFlags(PRInt32 *aLastFlags)
{
	*aLastFlags = mLastFlags;
    return NS_OK;
}

/* readonly attribute long lastInterface; */
NS_IMETHODIMP CDSDBROWSE::GetLastInterface(PRInt32 *aLastInterface)
{
	*aLastInterface = mLastInterface;
    return NS_OK;
}

/* readonly attribute long lastErrorcode; */
NS_IMETHODIMP CDSDBROWSE::GetLastErrorcode(PRInt32 *aLastErrorcode)
{
	*aLastErrorcode = mLastErrorcode;
    return NS_OK;
}

/* readonly attribute AString lastName; */
NS_IMETHODIMP CDSDBROWSE::GetLastName(nsAString & aLastName)
{
	aLastName = mLastName; 
    return NS_OK;
}

/* readonly attribute AString lastRegType; */
NS_IMETHODIMP CDSDBROWSE::GetLastRegType(nsAString & aLastRegType)
{
	aLastRegType = mLastRegType;
    return NS_OK;
}

/* readonly attribute AString lastDomain; */
NS_IMETHODIMP CDSDBROWSE::GetLastDomain(nsAString & aLastDomain)
{
	aLastDomain = mLastDomain;
    return NS_OK;
}

/* readonly attribute long status; */
NS_IMETHODIMP CDSDBROWSE::GetStatus(PRInt32 *aStatus)
{
	*aStatus = mStatus;
    return NS_OK;
}

void DNSSD_API CDSDBROWSE::Callback(
  	DNSServiceRef			inSdRef,
	DNSServiceFlags			inFlags,
	uint32_t 				inInterfaceIndex,
	DNSServiceErrorType		inErrorCode,
	const char 			*	inReplyName,
	const char 			   *inReplyType,
	const char 			   *inReplyDomain,
	void 				*	inContext)
{
  //printf("CDSDBROWSE::CallBack()\n");
	CDSDBROWSE * self;
	self = reinterpret_cast <CDSDBROWSE*>( inContext );
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
            /*
            oFlags->SetAsInt32(inFlags);
            array->AppendElement(oFlags, PR_FALSE);
            self->mLastFlags = inFlags;
            */
            if (inFlags & kDNSServiceFlagsAdd)  {
                oFlags->SetAsAUTF8String(NS_ConvertUTF16toUTF8(NS_LITERAL_STRING("add")));
            } else {
                oFlags->SetAsAUTF8String(NS_ConvertUTF16toUTF8(NS_LITERAL_STRING("rmv")));
            }
            array->AppendElement(oFlags, PR_FALSE);
            self->mLastFlags = inFlags;
            
            nsCOMPtr<nsIWritableVariant> oInterfaceIndex = do_CreateInstance("@mozilla.org/variant;1");
            oInterfaceIndex->SetAsInt32(inInterfaceIndex);
            array->AppendElement(oInterfaceIndex, PR_FALSE);        
            self->mLastInterface = inInterfaceIndex;
        
            nsCOMPtr<nsIWritableVariant> oReplyName = do_CreateInstance("@mozilla.org/variant;1");        
            oReplyName->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(inReplyName)) );
            array->AppendElement(oReplyName, PR_FALSE);
            self->mLastName = NS_ConvertUTF8toUTF16(inReplyName);        
    
    		
            nsCOMPtr<nsIWritableVariant> oReplyType = do_CreateInstance("@mozilla.org/variant;1");        
            oReplyType->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(inReplyType)) );
            array->AppendElement(oReplyType, PR_FALSE);
            self->mLastRegType = NS_ConvertUTF8toUTF16(inReplyType);        
    
    		
            nsCOMPtr<nsIWritableVariant> oReplyDomain = do_CreateInstance("@mozilla.org/variant;1");        
            oReplyDomain->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(inReplyDomain)) );
            array->AppendElement(oReplyDomain, PR_FALSE);
            self->mLastDomain = NS_ConvertUTF8toUTF16(inReplyDomain); 
        	dsdmanager->HandleEvent(NS_LITERAL_STRING("browse"),PR_FALSE,array);    	
        } else {       
            self->mStatus = 99;
            if (self->mTimer)
                self->mTimer->Cancel();
            nsCOMPtr<nsIWritableVariant> oErrorCode = do_CreateInstance("@mozilla.org/variant;1");
            oErrorCode->SetAsInt32(inErrorCode);
            array->AppendElement(oErrorCode, PR_FALSE);        
            // DNSServiceRefDeallocate(self->mSdRef);
        	dsdmanager->HandleEvent(NS_LITERAL_STRING("browse"),PR_TRUE,array);
        }
	}
}

void CDSDBROWSE::PollSelect(void *inContext)
{
    //printf("CDSDBROWSE::PollSelect()\n");
	CDSDBROWSE * self;
	self = reinterpret_cast <CDSDBROWSE*>( inContext );
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

nsresult CDSDBROWSE::StartTimer()
{
    //printf("CDSDBROWSE::StartTimer()\n");
    mTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (!mTimer)
        return NS_ERROR_FAILURE;
    return mTimer->InitWithFuncCallback(this->TimeoutHandler, this, 1000, 
                                        nsITimer::TYPE_REPEATING_SLACK);
}


void CDSDBROWSE::TimeoutHandler(nsITimer *aTimer, void *aClosure)
{
    //printf("CDSDBROWSE::TimeoutHandler()\n");
    CDSDBROWSE *self = reinterpret_cast<CDSDBROWSE*>(aClosure);
    if (!self) {
        NS_ERROR("no self\n");
        return;
    }
    self->PollSelect(self);
}


/* End of implementation class template. */
