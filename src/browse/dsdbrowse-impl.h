#ifndef __DSDBROWSE_IMPL_H__
#define __DSDBROWSE_IMPL_H__

#include "dsdbrowse.h"

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

#define DSDBROWSE_CONTRACTID "@andrew.tj.id.au/dsdbrowse;1"
#define DSDBROWSE_CLASSNAME "DSDBROWSE"
#define DSDBROWSE_CID \
  {0xc38472d2, 0x9010, 0x4899, \
    { 0xb2, 0xae, 0x89, 0xad, 0xc8, 0xeb, 0x12, 0x46 }}
    
class CDSDBROWSE : public IDSDBROWSE
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDBROWSE

  CDSDBROWSE();

private:
  ~CDSDBROWSE();
  void PollSelect(void *inContext);
  void StartTimer(void *inContext);
  nsresult StartTimer();
  static void DNSSD_API Callback (
  	DNSServiceRef			inSdRef,
	DNSServiceFlags			inFlags,
	uint32_t 				inInterfaceIndex,
	DNSServiceErrorType		inErrorCode,
	const char 			*	inReplyName,
	const char 			   *inReplyType,
	const char 			   *inReplyDomain,
	void 				*	inContext);
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;

  
  
protected:
  /* additional members */
  
  DNSServiceRef mSdRef;

  long mInterfaceIndex;
  nsString mRegistrationType;
  nsString mRegistrationDomain;
  long mLastFlags;
  long mLastInterface;
  long mLastErrorcode;  
  nsString mLastName;
  nsString mLastRegType;
  nsString mLastDomain;
  long mStatus;
  
};

#endif