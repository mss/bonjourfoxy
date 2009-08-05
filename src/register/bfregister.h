/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfregister.idl
 */

#ifndef __gen_bfregister_h__
#define __gen_bfregister_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_bfregistercallback_h__
#include "bfregistercallback.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    BFRegister */
#define BFREGISTER_IID_STR "7a4a1e8f-0387-48c4-bcd1-b89a2b07af85"

#define BFREGISTER_IID \
  {0x7a4a1e8f, 0x0387, 0x48c4, \
    { 0xbc, 0xd1, 0xb8, 0x9a, 0x2b, 0x07, 0xaf, 0x85 }}

class NS_NO_VTABLE NS_SCRIPTABLE BFRegister : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(BFREGISTER_IID)

  /* void register (); */
  NS_SCRIPTABLE NS_IMETHOD Register(void) = 0;

  /* attribute BFRegisterCallback callback; */
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFRegisterCallback * *aCallback) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFRegisterCallback * aCallback) = 0;

  /* attribute long interfaceIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) = 0;

  /* attribute PRBool autorename; */
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename) = 0;

  /* attribute AString serviceName; */
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName) = 0;

  /* attribute AString registrationType; */
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) = 0;

  /* attribute AString registrationDomain; */
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) = 0;

  /* attribute AString targetHost; */
  NS_SCRIPTABLE NS_IMETHOD GetTargetHost(nsAString & aTargetHost) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTargetHost(const nsAString & aTargetHost) = 0;

  /* attribute long targetPort; */
  NS_SCRIPTABLE NS_IMETHOD GetTargetPort(PRInt32 *aTargetPort) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTargetPort(PRInt32 aTargetPort) = 0;

  /* attribute AString txtRecordKey; */
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordKey(nsAString & aTxtRecordKey) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordKey(const nsAString & aTxtRecordKey) = 0;

  /* attribute AString txtRecordValue; */
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordValue(nsAString & aTxtRecordValue) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordValue(const nsAString & aTxtRecordValue) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(BFRegister, BFREGISTER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_BFREGISTER \
  NS_SCRIPTABLE NS_IMETHOD Register(void); \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFRegisterCallback * *aCallback); \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFRegisterCallback * aCallback); \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename); \
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename); \
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName); \
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain); \
  NS_SCRIPTABLE NS_IMETHOD GetTargetHost(nsAString & aTargetHost); \
  NS_SCRIPTABLE NS_IMETHOD SetTargetHost(const nsAString & aTargetHost); \
  NS_SCRIPTABLE NS_IMETHOD GetTargetPort(PRInt32 *aTargetPort); \
  NS_SCRIPTABLE NS_IMETHOD SetTargetPort(PRInt32 aTargetPort); \
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordKey(nsAString & aTxtRecordKey); \
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordKey(const nsAString & aTxtRecordKey); \
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordValue(nsAString & aTxtRecordValue); \
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordValue(const nsAString & aTxtRecordValue); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_BFREGISTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Register(void) { return _to Register(); } \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFRegisterCallback * *aCallback) { return _to GetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFRegisterCallback * aCallback) { return _to SetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return _to GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return _to SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename) { return _to GetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename) { return _to SetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName) { return _to GetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName) { return _to SetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return _to GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return _to SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return _to GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return _to SetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetTargetHost(nsAString & aTargetHost) { return _to GetTargetHost(aTargetHost); } \
  NS_SCRIPTABLE NS_IMETHOD SetTargetHost(const nsAString & aTargetHost) { return _to SetTargetHost(aTargetHost); } \
  NS_SCRIPTABLE NS_IMETHOD GetTargetPort(PRInt32 *aTargetPort) { return _to GetTargetPort(aTargetPort); } \
  NS_SCRIPTABLE NS_IMETHOD SetTargetPort(PRInt32 aTargetPort) { return _to SetTargetPort(aTargetPort); } \
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordKey(nsAString & aTxtRecordKey) { return _to GetTxtRecordKey(aTxtRecordKey); } \
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordKey(const nsAString & aTxtRecordKey) { return _to SetTxtRecordKey(aTxtRecordKey); } \
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordValue(nsAString & aTxtRecordValue) { return _to GetTxtRecordValue(aTxtRecordValue); } \
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordValue(const nsAString & aTxtRecordValue) { return _to SetTxtRecordValue(aTxtRecordValue); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_BFREGISTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Register(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Register(); } \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFRegisterCallback * *aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFRegisterCallback * aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetTargetHost(nsAString & aTargetHost) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTargetHost(aTargetHost); } \
  NS_SCRIPTABLE NS_IMETHOD SetTargetHost(const nsAString & aTargetHost) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTargetHost(aTargetHost); } \
  NS_SCRIPTABLE NS_IMETHOD GetTargetPort(PRInt32 *aTargetPort) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTargetPort(aTargetPort); } \
  NS_SCRIPTABLE NS_IMETHOD SetTargetPort(PRInt32 aTargetPort) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTargetPort(aTargetPort); } \
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordKey(nsAString & aTxtRecordKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTxtRecordKey(aTxtRecordKey); } \
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordKey(const nsAString & aTxtRecordKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTxtRecordKey(aTxtRecordKey); } \
  NS_SCRIPTABLE NS_IMETHOD GetTxtRecordValue(nsAString & aTxtRecordValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTxtRecordValue(aTxtRecordValue); } \
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordValue(const nsAString & aTxtRecordValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTxtRecordValue(aTxtRecordValue); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public BFRegister
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFREGISTER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, BFRegister)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void register (); */
NS_IMETHODIMP _MYCLASS_::Register()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute BFRegisterCallback callback; */
NS_IMETHODIMP _MYCLASS_::GetCallback(BFRegisterCallback * *aCallback)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCallback(BFRegisterCallback * aCallback)
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

/* attribute PRBool autorename; */
NS_IMETHODIMP _MYCLASS_::GetAutorename(PRBool *aAutorename)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetAutorename(PRBool aAutorename)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString serviceName; */
NS_IMETHODIMP _MYCLASS_::GetServiceName(nsAString & aServiceName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetServiceName(const nsAString & aServiceName)
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

/* attribute AString targetHost; */
NS_IMETHODIMP _MYCLASS_::GetTargetHost(nsAString & aTargetHost)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetTargetHost(const nsAString & aTargetHost)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long targetPort; */
NS_IMETHODIMP _MYCLASS_::GetTargetPort(PRInt32 *aTargetPort)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetTargetPort(PRInt32 aTargetPort)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString txtRecordKey; */
NS_IMETHODIMP _MYCLASS_::GetTxtRecordKey(nsAString & aTxtRecordKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetTxtRecordKey(const nsAString & aTxtRecordKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AString txtRecordValue; */
NS_IMETHODIMP _MYCLASS_::GetTxtRecordValue(nsAString & aTxtRecordValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetTxtRecordValue(const nsAString & aTxtRecordValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_bfregister_h__ */
