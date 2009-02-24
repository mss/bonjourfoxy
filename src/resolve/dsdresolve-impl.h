#ifndef __DSDRESOLVE_IMPL_H__
#define __DSDRESOLVE_IMPL_H__

#include "dsdresolve.h"

#include "nsStringAPI.h"

#include "dns_sd.h"

#include "nsITimer.h"
#include "nsCOMPtr.h"

// #include "nsString.h"

/*
#ifdef _WIN32
#include <process.h>
#include <winsock2.h>
typedef	int	pid_t;
#else
#include <arpa/inet.h>		// For inet_addr()
#endif
*/

#define DSDRESOLVE_CONTRACTID "@andrew.tj.id.au/dsdresolve;1"
#define DSDRESOLVE_CLASSNAME "DSDRESOLVE"
#define DSDRESOLVE_CID \
  {0x0c8ea066, 0x3bd8, 0x4018, \
    { 0xaa, 0xd7, 0xfb, 0x32, 0x20, 0x5d, 0xc4, 0xac }}

class CDSDRESOLVE : public IDSDRESOLVE
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDRESOLVE

  CDSDRESOLVE();

private:
  ~CDSDRESOLVE();
  void PollSelect(void *inContext);
  void StartTimer(void *inContext);
  nsresult StartTimer();
  static void DNSSD_API Callback(
		DNSServiceRef			inSdRef,
		DNSServiceFlags			inFlags,
		uint32_t				inInterfaceIndex,
		DNSServiceErrorType		inErrorCode,
		const char *			inFQDN,	
		const char *			inHostname, 
		uint16_t 				inPort,
		uint16_t 				inTxtLen,
		const char *			inTxtRecord,
		void *					inContext );  
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;
  
protected:
  /* additional members */
  
  DNSServiceRef mSdRef;

  long mInterfaceIndex;
  nsString mName;
  nsString mRegistrationType;
  nsString mRegistrationDomain;
  long mLastFlags;
  long mLastInterface;
  long mLastErrorcode;  
  nsString mLastFQDN;
  nsString mLastHostname;
  long mLastPort;
  nsString mLastTxtRecord;
  nsString mLastTxtRecordKey;
  nsString mLastTxtRecordValue;
  long mStatus;
    
};

#endif