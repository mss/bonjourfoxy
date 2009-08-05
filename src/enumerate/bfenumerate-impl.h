#ifndef __BFENUMERATE_IMPL_H__
#define __BFENUMERATE_IMPL_H__

#include "bfenumerate.h"
#include "bfenumeratecallback.h"
#include "dns_sd.h"
#include "nsStringAPI.h"
#include "nsITimer.h"
#include "nsCOMPtr.h"


#define BFENUMERATE_CONTRACTID "@bonjourfoxy.net/bfenumerate;1"
#define BFENUMERATE_CLASSNAME "BFEnumerate"
#define BFENUMERATE_CID \
  {0x20e5d84c, 0x6cd9, 0x41e7, \
    { 0xb0, 0x5d, 0xd7, 0xc7, 0x3a, 0x08, 0x82, 0xfb }}

class CBFENUMERATE : public BFEnumerate
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFENUMERATE

  CBFENUMERATE();

private:
  ~CBFENUMERATE();
  void PollSelect(void *inContext);
  void StartTimer(void *inContext);
  void Log(const PRUnichar* message);
  nsresult StartTimer();
  static void DNSSD_API Callback (
    DNSServiceRef                       inSdRef,
        DNSServiceFlags                 inFlags,
        uint32_t                                inInterfaceIndex,
        DNSServiceErrorType             inErrorCode,
        const char                      *       inReplyDomain,
        void                            *       inContext
    );
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;

protected:
  DNSServiceRef mSdRef;
  PRBool mType;
  long mInterfaceIndex;
  nsCOMPtr<BFEnumerateCallback> mCallback;
};

#endif