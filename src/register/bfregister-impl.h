#ifndef __BFREGISTER_IMPL_H__
#define __BFREGISTER_IMPL_H__

#include "bfregister.h"
#include "bfregistercallback.h"
#include "dns_sd.h"
#include "nsStringAPI.h"
#include "nsITimer.h"
#include "nsCOMPtr.h"

#define BFREGISTER_CONTRACTID "@bonjourfoxy.net/bfregister;1"
#define BFREGISTER_CLASSNAME "BFRegister"
#define BFREGISTER_CID \
  {0x7a4a1e8f, 0x0387, 0x48c4, \
    { 0xbc, 0xd1, 0xb8, 0x9a, 0x2b, 0x07, 0xaf, 0x85 }}

class CBFREGISTER : public BFRegister
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFREGISTER

  CBFREGISTER();

private:
  ~CBFREGISTER();
  void PollSelect(void *inContext);
  void Log(const PRUnichar* message);
  void StartTimer(void *inContext);    // appears to be dupe of below
  nsresult StartTimer();               // or the opposite.... fixy, fixy
  static void DNSSD_API Callback(
                DNSServiceRef                   inSdRef,
                DNSServiceFlags                 inFlags,
                DNSServiceErrorType             inErrorCode,
                const char *                    inName, 
                const char *                    inRegType,
                const char *                    inRegDomain,
                void *                          inContext );  
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;

protected:
  DNSServiceRef mSdRef;
  
  long mInterfaceIndex;
  PRBool mAutorename;
  nsString mServiceName;
  nsString mRegistrationType;
  nsString mRegistrationDomain;
  nsString mTargetHost;
  long mTargetPort;
  nsString mTxtRecordKey;
  nsString mTxtRecordValue;
  nsCOMPtr<BFRegisterCallback> mCallback;
};

#endif