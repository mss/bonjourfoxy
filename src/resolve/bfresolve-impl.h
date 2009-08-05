#ifndef __BFRESOLVE_IMPL_H__
#define __BFRESOLVE_IMPL_H__

#include "bfresolve.h"
#include "bfresolvecallback.h"
#include "dns_sd.h"
#include "nsStringAPI.h"
#include "nsITimer.h"
#include "nsCOMPtr.h"

#define BFRESOLVE_CONTRACTID "@bonjourfoxy.net/bfresolve;1"
#define BFRESOLVE_CLASSNAME "BFResolve"
#define BFRESOLVE_CID \
  {0x1fcc2895, 0x535a, 0x4b14, \
    { 0x8c, 0xb3, 0x62, 0xd8, 0xb7, 0xba, 0xa6, 0x78 }}

class CBFRESOLVE : public BFResolve
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFRESOLVE

  CBFRESOLVE();

private:
  ~CBFRESOLVE();
  void PollSelect(void *inContext);
  void StartTimer(void *inContext);
  void Log(const PRUnichar* message);
  nsresult StartTimer();
  static void DNSSD_API Callback(
        DNSServiceRef           inSdRef,
        DNSServiceFlags         inFlags,
        uint32_t                inInterfaceIndex,
        DNSServiceErrorType     inErrorCode,
        const char *            inFQDN, 
        const char *            inHostname, 
        uint16_t                inPort,
        uint16_t                inTxtLen,
        const char *            inTxtRecord,
        void *                  inContext );  
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;
  
protected:
  DNSServiceRef mSdRef; 
  long mInterfaceIndex;
  nsString mServiceName;
  nsString mRegistrationType;
  nsString mRegistrationDomain;
  nsCOMPtr<BFResolveCallback> mCallback;
};

#endif