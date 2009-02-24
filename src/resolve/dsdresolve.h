/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM dsdresolve.idl
 */

#ifndef __gen_dsdresolve_h__
#define __gen_dsdresolve_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsITimer_h__
#include "nsITimer.h"
#endif

#ifndef __gen_nsIServiceManager_h__
#include "nsIServiceManager.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IDSDRESOLVE */
#define IDSDRESOLVE_IID_STR "0c8ea066-3bd8-4018-aad7-fb32205dc4ac"

#define IDSDRESOLVE_IID \
  {0x0c8ea066, 0x3bd8, 0x4018, \
    { 0xaa, 0xd7, 0xfb, 0x32, 0x20, 0x5d, 0xc4, 0xac }}

class NS_NO_VTABLE NS_SCRIPTABLE IDSDRESOLVE : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IDSDRESOLVE_IID)

  /* void start (); */
  NS_SCRIPTABLE NS_IMETHOD Start(void) = 0;

  /* void stop (); */
  NS_SCRIPTABLE NS_IMETHOD Stop(void) = 0;

  /* attribute long interfaceIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) = 0;

  /* attribute AString name; */
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) = 0;

  /* attribute AString registrationType; */
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) = 0;

  /* attribute AString registrationDomain; */
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) = 0;

  /* readonly attribute long lastFlags; */
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) = 0;

  /* readonly attribute long lastInterface; */
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) = 0;

  /* readonly attribute long lastErrorcode; */
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) = 0;

  /* readonly attribute AString lastFQDN; */
  NS_SCRIPTABLE NS_IMETHOD GetLastFQDN(nsAString & aLastFQDN) = 0;

  /* readonly attribute AString lastHostname; */
  NS_SCRIPTABLE NS_IMETHOD GetLastHostname(nsAString & aLastHostname) = 0;

  /* readonly attribute long lastPort; */
  NS_SCRIPTABLE NS_IMETHOD GetLastPort(PRInt32 *aLastPort) = 0;

  /* readonly attribute AString lastTxtRecord; */
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecord(nsAString & aLastTxtRecord) = 0;

  /* readonly attribute AString lastTxtRecordKey; */
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordKey(nsAString & aLastTxtRecordKey) = 0;

  /* readonly attribute AString lastTxtRecordValue; */
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordValue(nsAString & aLastTxtRecordValue) = 0;

  /* readonly attribute long status; */
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IDSDRESOLVE, IDSDRESOLVE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IDSDRESOLVE \
  NS_SCRIPTABLE NS_IMETHOD Start(void); \
  NS_SCRIPTABLE NS_IMETHOD Stop(void); \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName); \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain); \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags); \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface); \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode); \
  NS_SCRIPTABLE NS_IMETHOD GetLastFQDN(nsAString & aLastFQDN); \
  NS_SCRIPTABLE NS_IMETHOD GetLastHostname(nsAString & aLastHostname); \
  NS_SCRIPTABLE NS_IMETHOD GetLastPort(PRInt32 *aLastPort); \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecord(nsAString & aLastTxtRecord); \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordKey(nsAString & aLastTxtRecordKey); \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordValue(nsAString & aLastTxtRecordValue); \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IDSDRESOLVE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return _to Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return _to Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return _to GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return _to SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return _to GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return _to SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return _to GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return _to SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return _to GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return _to SetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return _to GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) { return _to GetLastInterface(aLastInterface); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return _to GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFQDN(nsAString & aLastFQDN) { return _to GetLastFQDN(aLastFQDN); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastHostname(nsAString & aLastHostname) { return _to GetLastHostname(aLastHostname); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastPort(PRInt32 *aLastPort) { return _to GetLastPort(aLastPort); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecord(nsAString & aLastTxtRecord) { return _to GetLastTxtRecord(aLastTxtRecord); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordKey(nsAString & aLastTxtRecordKey) { return _to GetLastTxtRecordKey(aLastTxtRecordKey); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordValue(nsAString & aLastTxtRecordValue) { return _to GetLastTxtRecordValue(aLastTxtRecordValue); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return _to GetStatus(aStatus); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IDSDRESOLVE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastInterface(aLastInterface); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFQDN(nsAString & aLastFQDN) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastFQDN(aLastFQDN); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastHostname(nsAString & aLastHostname) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastHostname(aLastHostname); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastPort(PRInt32 *aLastPort) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastPort(aLastPort); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecord(nsAString & aLastTxtRecord) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastTxtRecord(aLastTxtRecord); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordKey(nsAString & aLastTxtRecordKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastTxtRecordKey(aLastTxtRecordKey); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastTxtRecordValue(nsAString & aLastTxtRecordValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastTxtRecordValue(aLastTxtRecordValue); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStatus(aStatus); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IDSDRESOLVE
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDRESOLVE

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IDSDRESOLVE)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void start (); */
NS_IMETHODIMP _MYCLASS_::Start()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void stop (); */
NS_IMETHODIMP _MYCLASS_::Stop()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long interfaceIndex; */
NS_IMETHODIMP _MYCLASS_::GetInterfaceIndex(PRInt32 *aInterfaceIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetInterfaceIndex(PRInt32 aInterfaceIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString name; */
NS_IMETHODIMP _MYCLASS_::GetName(nsAString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetName(const nsAString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString registrationType; */
NS_IMETHODIMP _MYCLASS_::GetRegistrationType(nsAString & aRegistrationType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetRegistrationType(const nsAString & aRegistrationType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString registrationDomain; */
NS_IMETHODIMP _MYCLASS_::GetRegistrationDomain(nsAString & aRegistrationDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetRegistrationDomain(const nsAString & aRegistrationDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long lastFlags; */
NS_IMETHODIMP _MYCLASS_::GetLastFlags(PRInt32 *aLastFlags)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long lastInterface; */
NS_IMETHODIMP _MYCLASS_::GetLastInterface(PRInt32 *aLastInterface)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long lastErrorcode; */
NS_IMETHODIMP _MYCLASS_::GetLastErrorcode(PRInt32 *aLastErrorcode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString lastFQDN; */
NS_IMETHODIMP _MYCLASS_::GetLastFQDN(nsAString & aLastFQDN)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString lastHostname; */
NS_IMETHODIMP _MYCLASS_::GetLastHostname(nsAString & aLastHostname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long lastPort; */
NS_IMETHODIMP _MYCLASS_::GetLastPort(PRInt32 *aLastPort)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString lastTxtRecord; */
NS_IMETHODIMP _MYCLASS_::GetLastTxtRecord(nsAString & aLastTxtRecord)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString lastTxtRecordKey; */
NS_IMETHODIMP _MYCLASS_::GetLastTxtRecordKey(nsAString & aLastTxtRecordKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString lastTxtRecordValue; */
NS_IMETHODIMP _MYCLASS_::GetLastTxtRecordValue(nsAString & aLastTxtRecordValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long status; */
NS_IMETHODIMP _MYCLASS_::GetStatus(PRInt32 *aStatus)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_dsdresolve_h__ */
