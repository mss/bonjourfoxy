#ifndef __DSDENUMERATE_IMPL_H__
#define __DSDENUMERATE_IMPL_H__

#include "dsdenumerate.h"

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

#define DSDENUMERATE_CONTRACTID "@andrew.tj.id.au/dsdenumerate;1"
#define DSDENUMERATE_CLASSNAME "DSDENUMERATE"
#define DSDENUMERATE_CID \
  {0xae851af1, 0x534b, 0x4d18, \
    { 0xac, 0x5f, 0x10, 0x5a, 0x6a, 0x49, 0xfb, 0xb2 }}

class CDSDENUMERATE : public IDSDENUMERATE
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDENUMERATE

  CDSDENUMERATE();

private:
  ~CDSDENUMERATE();
  void PollSelect(void *inContext);
  void StartTimer(void *inContext);
  nsresult StartTimer();
  static void DNSSD_API Callback (
    DNSServiceRef			inSdRef,
	DNSServiceFlags			inFlags,
	uint32_t				inInterfaceIndex,
	DNSServiceErrorType		inErrorCode,
	const char			*	inReplyDomain,
	void				*	inContext
    );
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;
  
protected:
  /* additional members */
  
  DNSServiceRef mSdRef;

  long mType;
  long mInterfaceIndex;
  long mLastFlags;
  long mLastInterface;
  long mLastErrorcode;  
  nsString mLastDomain;
  long mStatus;
    
};

#endif