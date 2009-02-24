#include "dsdresolve-impl.h"

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

#include <string>

#ifndef _WIN32
#include <sys/time.h>
#endif

#include <errno.h>			// For errno, EINTR

NS_IMPL_ISUPPORTS1(CDSDRESOLVE, IDSDRESOLVE)


CDSDRESOLVE::CDSDRESOLVE()
{
  /* member initializers and constructor code */
  mSdRef = NULL;
  mInterfaceIndex = NULL;
  mLastFlags = NULL;
  mLastInterface = NULL;
  mLastErrorcode = NULL;
  mLastFQDN = NS_LITERAL_STRING("");
  mLastHostname = NS_LITERAL_STRING("");
  mLastPort = NULL;
  mLastTxtRecord = NS_LITERAL_STRING("");
  mStatus = 0;
}

CDSDRESOLVE::~CDSDRESOLVE()
{
  /* destructor code */
  mStatus = 99;
  if (mTimer)
    mTimer->Cancel();
  if (mSdRef)
    DNSServiceRefDeallocate(mSdRef); 
}

/* void start (); */
NS_IMETHODIMP CDSDRESOLVE::Start()
{
    DNSServiceErrorType err = kDNSServiceErr_Unknown;
    if (mStatus == 99) {
        return NS_ERROR_FAILURE;
    }
	err = DNSServiceResolve(&mSdRef, 0, mInterfaceIndex, ToNewUTF8String(mName) , ToNewUTF8String(mRegistrationType), ToNewUTF8String(mRegistrationDomain), (DNSServiceResolveReply) Callback, this);
	if (err != kDNSServiceErr_NoError) {
        mLastErrorcode = err;
        mStatus = 99;
		printf("%d\n", err);
        return NS_ERROR_FAILURE;
	}
	mStatus = 1;
	StartTimer();
    return NS_OK;
}

/* void stop (); */
NS_IMETHODIMP CDSDRESOLVE::Stop()
{	
    mStatus = 0;
    if (mTimer)
      mTimer->Cancel();
    if (mSdRef)
      DNSServiceRefDeallocate(mSdRef);
    return NS_OK;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP CDSDRESOLVE::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
	*aInterfaceIndex = mInterfaceIndex;
    return NS_OK;
}
NS_IMETHODIMP CDSDRESOLVE::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
	mInterfaceIndex = aInterfaceIndex;
    return NS_OK;
}

/* attribute AString name; */
NS_IMETHODIMP CDSDRESOLVE::GetName(nsAString & aName)
{
	aName = mName;
    return NS_OK;
}
NS_IMETHODIMP CDSDRESOLVE::SetName(const nsAString & aName)
{
	mName = aName;
    return NS_OK;
}

/* attribute AString registrationType; */
NS_IMETHODIMP CDSDRESOLVE::GetRegistrationType(nsAString & aRegistrationType)
{
	aRegistrationType = mRegistrationType;
    return NS_OK;
}
NS_IMETHODIMP CDSDRESOLVE::SetRegistrationType(const nsAString & aRegistrationType)
{
	mRegistrationType = aRegistrationType;
    return NS_OK;
}

/* attribute AString registrationDomain; */
NS_IMETHODIMP CDSDRESOLVE::GetRegistrationDomain(nsAString & aRegistrationDomain)
{
	aRegistrationDomain = mRegistrationDomain;
    return NS_OK;
}
NS_IMETHODIMP CDSDRESOLVE::SetRegistrationDomain(const nsAString & aRegistrationDomain)
{
	mRegistrationDomain = aRegistrationDomain;
    return NS_OK;
}

/* readonly attribute long lastFlags; */
NS_IMETHODIMP CDSDRESOLVE::GetLastFlags(PRInt32 *aLastFlags)
{
	*aLastFlags = mLastFlags;
    return NS_OK;
}

/* readonly attribute long lastInterface; */
NS_IMETHODIMP CDSDRESOLVE::GetLastInterface(PRInt32 *aLastInterface)
{
	*aLastInterface = mLastInterface;
    return NS_OK;
}

/* readonly attribute long lastErrorcode; */
NS_IMETHODIMP CDSDRESOLVE::GetLastErrorcode(PRInt32 *aLastErrorcode)
{
	*aLastErrorcode = mLastErrorcode;
    return NS_OK;
}

/* readonly attribute AString lastFQDN; */
NS_IMETHODIMP CDSDRESOLVE::GetLastFQDN(nsAString & aLastFQDN)
{
	aLastFQDN = mLastFQDN;
    return NS_OK;
}

/* readonly attribute AString lastHostname; */
NS_IMETHODIMP CDSDRESOLVE::GetLastHostname(nsAString & aLastHostname)
{
	aLastHostname = mLastHostname;
    return NS_OK;
}

/* readonly attribute long lastPort; */
NS_IMETHODIMP CDSDRESOLVE::GetLastPort(PRInt32 *aLastPort)
{
	*aLastPort = mLastPort;
    return NS_OK;
}

/* readonly attribute AString lastTxtRecord; */
NS_IMETHODIMP CDSDRESOLVE::GetLastTxtRecord(nsAString & aLastTxtRecord)
{
	aLastTxtRecord = mLastTxtRecord;
    return NS_OK;
}

/* readonly attribute AString lastTxtRecordKey; */
NS_IMETHODIMP CDSDRESOLVE::GetLastTxtRecordKey(nsAString & aLastTxtRecordKey)
{
	aLastTxtRecordKey = mLastTxtRecordKey;
    return NS_OK;
}

/* readonly attribute AString lastTxtRecordValue; */
NS_IMETHODIMP CDSDRESOLVE::GetLastTxtRecordValue(nsAString & aLastTxtRecordValue)
{
	aLastTxtRecordValue = mLastTxtRecordValue;
    return NS_OK;
}

/* readonly attribute long status; */
NS_IMETHODIMP CDSDRESOLVE::GetStatus(PRInt32 *aStatus)
{
	*aStatus = mStatus;
    return NS_OK;
}

void DNSSD_API CDSDRESOLVE::Callback(
		DNSServiceRef			inSdRef,
		DNSServiceFlags			inFlags,
		uint32_t				inInterfaceIndex,
		DNSServiceErrorType		inErrorCode,
		const char *			inFQDN,	
		const char *			inHostname, 
		uint16_t 				inPort,
		uint16_t 				inTxtLen,
		const char *			inTxtRecord,
		void *					inContext )
{
    // printf("CDSDRESOLVE::Callback()\n");
	CDSDRESOLVE * self;
	self = reinterpret_cast <CDSDRESOLVE*>( inContext );
	// const unsigned char *tTxtRecord = inTxtRecord;
	// printf("HAPPY!\n");
	// printf("%s\n", inReplyDomain);
	nsCOMPtr<nsIServiceManager> servMan;
    nsresult rv = NS_GetServiceManager(getter_AddRefs(servMan)); 
    if (NS_FAILED(rv)) {
        self->mStatus = 99;
    } else {
        nsCOMPtr<IDSDMANAGER> dsdmanager;
        rv = servMan->GetServiceByContractID("@andrew.tj.id.au/dsdmanager;1", NS_GET_IID(IDSDMANAGER), getter_AddRefs(dsdmanager));

        nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);

		
        nsCOMPtr<nsIWritableVariant> oFlags = do_CreateInstance("@mozilla.org/variant;1");
        oFlags->SetAsInt32(inFlags);
        array->AppendElement(oFlags, PR_FALSE);
        self->mLastFlags = inFlags;

        nsCOMPtr<nsIWritableVariant> oInterfaceIndex = do_CreateInstance("@mozilla.org/variant;1");
        oInterfaceIndex->SetAsInt32(inInterfaceIndex);
        array->AppendElement(oInterfaceIndex, PR_FALSE);        
        self->mLastInterface = inInterfaceIndex;

        nsCOMPtr<nsIWritableVariant> oErrorCode = do_CreateInstance("@mozilla.org/variant;1");
        oErrorCode->SetAsInt32(inErrorCode);
        array->AppendElement(oErrorCode, PR_FALSE);        
        self->mLastErrorcode = inErrorCode;

        nsCOMPtr<nsIWritableVariant> oFQDN = do_CreateInstance("@mozilla.org/variant;1");        
        oFQDN->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(inFQDN)) );
        array->AppendElement(oFQDN, PR_FALSE);
        self->mLastFQDN = NS_ConvertUTF8toUTF16(inFQDN);  

        nsCOMPtr<nsIWritableVariant> oHostname = do_CreateInstance("@mozilla.org/variant;1");        
        oHostname->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(inHostname)) );
        array->AppendElement(oHostname, PR_FALSE);
        self->mLastHostname = NS_ConvertUTF8toUTF16(inHostname);

        nsCOMPtr<nsIWritableVariant> oPort = do_CreateInstance("@mozilla.org/variant;1");
		union { uint16_t s; u_char b[2]; } port = { inPort };
		uint16_t PortAsNumber = ((uint16_t)port.b[0]) << 8 | port.b[1];
        oPort->SetAsInt32(PortAsNumber);
        array->AppendElement(oPort, PR_FALSE);        
        self->mLastPort = PortAsNumber;


		self->mLastTxtRecordKey=NS_LITERAL_STRING("");		
		self->mLastTxtRecordKey=NS_LITERAL_STRING("");
		self->mLastTxtRecordValue=NS_LITERAL_STRING("");

		char key[256];
		int index=0;
		uint8_t valueLen;
		const void *voidValue = 0;
		while (TXTRecordGetItemAtIndex(inTxtLen,inTxtRecord,index++,256,key, &valueLen,
		&voidValue) == kDNSServiceErr_NoError) 
        {
			// printf("Key: %s Value: %s\n", key, voidValue);
			
			nsCOMPtr<nsIMutableArray> oTxtRecord = do_CreateInstance(NS_ARRAY_CONTRACTID);
			
			self->mLastTxtRecordKey=NS_ConvertUTF8toUTF16(key);
			nsCOMPtr<nsIWritableVariant> outKey = do_CreateInstance("@mozilla.org/variant;1");
			outKey->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(key)) );
			
			char tValue[valueLen+1];
			snprintf (tValue, sizeof(tValue), "%.*s\n", (int) valueLen, voidValue);
			self->mLastTxtRecordValue=NS_ConvertUTF8toUTF16(tValue);
			nsCOMPtr<nsIWritableVariant> outValue = do_CreateInstance("@mozilla.org/variant;1");        
			outValue->SetAsAUTF8String( NS_ConvertUTF16toUTF8(NS_ConvertUTF8toUTF16(tValue)) );
			
			oTxtRecord->AppendElement(outKey, PR_FALSE);
			oTxtRecord->AppendElement(outValue, PR_FALSE);
			
			array->AppendElement(oTxtRecord, PR_FALSE);
        }
    	dsdmanager->HandleEvent(NS_LITERAL_STRING("resolve"),array);
    }
}

void CDSDRESOLVE::PollSelect(void *inContext)
{
    // printf("CDSDRESOLVE::PollSelect()\n");
	CDSDRESOLVE * self;
	self = reinterpret_cast <CDSDRESOLVE*>( inContext );
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
		// printf("Results: %d\n", result);
		DNSServiceErrorType err = kDNSServiceErr_NoError;
		if (self->mSdRef && FD_ISSET(dns_sd_fd , &readfds)) {
			err = DNSServiceProcessResult(self->mSdRef);
			}
        /*
		if (err) {
			// printf("DNSServiceProcessResult returned %d\n", err);
			}
		*/
		}
	else if (result == 0)
	    {
		// printf("No Results\n");
	    }
	else
		{		  
		// printf("select() returned %d errno %d %s\n", result, errno, strerror(errno));
		if (errno != EINTR) self->mStatus = 99;
		}
    if (self->mStatus != 1)    {
        DNSServiceRefDeallocate(self->mSdRef);
		if (mTimer)
			mTimer->Cancel();
    }
}    

nsresult CDSDRESOLVE::StartTimer()
{
    // printf("CDSDRESOLVE::StartTimer()\n");
    mTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (!mTimer)
        return NS_ERROR_FAILURE;
    return mTimer->InitWithFuncCallback(this->TimeoutHandler, this, 1000, 
                                        nsITimer::TYPE_REPEATING_SLACK);
}


void CDSDRESOLVE::TimeoutHandler(nsITimer *aTimer, void *aClosure)
{
    // printf("CDSDRESOLVE::TimeoutHandler()\n");
    CDSDRESOLVE *self = reinterpret_cast<CDSDRESOLVE*>(aClosure);
    if (!self) {
        NS_ERROR("no self\n");
        return;
    }
    self->PollSelect(self);
}