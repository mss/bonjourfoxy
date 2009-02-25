#ifndef __DSDREGISTER_IMPL_H__
#define __DSDREGISTER_IMPL_H__

#include "dsdregister.h"

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

#define DSDREGISTER_CONTRACTID "@andrew.tj.id.au/dsdregister;1"
#define DSDREGISTER_CLASSNAME "DSDREGISTER"
#define DSDREGISTER_CID \
  {0x3da74016, 0xfbf0, 0x4088, \
    { 0xa7, 0xb6, 0x82, 0xc5, 0x7e, 0xe9, 0x0d, 0x52 }}

class CDSDREGISTER : public IDSDREGISTER
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDREGISTER

  CDSDREGISTER();

private:
  ~CDSDREGISTER();
  void PollSelect(void *inContext);
  void StartTimer(void *inContext);
  nsresult StartTimer();
  static void DNSSD_API Callback(
		DNSServiceRef			inSdRef,
		DNSServiceFlags			inFlags,
		DNSServiceErrorType		inErrorCode,
		const char *			inName,	
		const char *			inRegType,
		const char *			inRegDomain,
		void *					inContext );  
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;
  
protected:
  /* additional members */

  DNSServiceRef mSdRef;
  
  long mInterfaceIndex;
  PRBool mAutorename;
  nsString mName;
  nsString mRegistrationType;
  nsString mRegistrationDomain;
  nsString mTargetHost;
  long mTargetPort;
  nsString mTxtRecordKey;
  nsString mTxtRecordValue;
  long mLastFlags;
  long mLastErrorcode;
  nsString mLastName;
  nsString mLastRegType;
  nsString mLastDomain;
  long mStatus;
};

#endif