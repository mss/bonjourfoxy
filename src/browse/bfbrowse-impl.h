#ifndef __BFBROWSE_IMPL_H__
#define __BFBROWSE_IMPL_H__

#include "bfbrowse.h"

#include "nsStringAPI.h"

#include "dns_sd.h"

#include "nsITimer.h"
#include "nsCOMPtr.h"

#define BFBROWSE_CONTRACTID "@bonjourfoxy.net/bfbrowse;1"
#define BFBROWSE_CLASSNAME "BFBrowse"
#define BFBROWSE_CID \
  {0xb165f500, 0x4972, 0x47a9, \
    { 0x80, 0xc8, 0x65, 0xed, 0xb6, 0xdf, 0xcc, 0x59 }}

class CBFBROWSE : public BFBrowse
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFBROWSE

  CBFBROWSE();

private:
  ~CBFBROWSE();
  void PollSelect(void *inContext);
  void StartTimer(void *inContext);
  void Log(const PRUnichar* message);
  nsresult StartTimer();
  static void DNSSD_API Callback (
    DNSServiceRef           inSdRef,
    DNSServiceFlags         inFlags,
    uint32_t                inInterfaceIndex,
    DNSServiceErrorType     inErrorCode,
    const char *            inReplyName,
    const char *            inReplyType,
    const char *            inReplyDomain,
    void *                  inContext);
  static void TimeoutHandler(nsITimer *aTimer, void *aClosure);
  nsCOMPtr<nsITimer>        mTimer;


protected:
  DNSServiceRef mSdRef;
  long mInterfaceIndex;
  nsString mRegistrationType;
  nsString mRegistrationDomain;
  nsCOMPtr<BFBrowseCallback> mCallback;
};

#endif