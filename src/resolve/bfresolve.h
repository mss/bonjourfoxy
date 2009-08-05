/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfresolve.idl
 */

#ifndef __gen_bfresolve_h__
#define __gen_bfresolve_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_bfresolvecallback_h__
#include "bfresolvecallback.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    BFResolve */
#define BFRESOLVE_IID_STR "1fcc2895-535a-4b14-8cb3-62d8b7baa678"

#define BFRESOLVE_IID \
  {0x1fcc2895, 0x535a, 0x4b14, \
    { 0x8c, 0xb3, 0x62, 0xd8, 0xb7, 0xba, 0xa6, 0x78 }}

class NS_NO_VTABLE NS_SCRIPTABLE BFResolve : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(BFRESOLVE_IID)

  /* void resolve (); */
  NS_SCRIPTABLE NS_IMETHOD Resolve(void) = 0;

  /* attribute BFResolveCallback callback; */
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFResolveCallback * *aCallback) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFResolveCallback * aCallback) = 0;

  /* attribute long interfaceIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) = 0;

  /* attribute AString serviceName; */
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName) = 0;

  /* attribute AString registrationType; */
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) = 0;

  /* attribute AString registrationDomain; */
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(BFResolve, BFRESOLVE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_BFRESOLVE \
  NS_SCRIPTABLE NS_IMETHOD Resolve(void); \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFResolveCallback * *aCallback); \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFResolveCallback * aCallback); \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName); \
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_BFRESOLVE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Resolve(void) { return _to Resolve(); } \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFResolveCallback * *aCallback) { return _to GetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFResolveCallback * aCallback) { return _to SetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return _to GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return _to SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName) { return _to GetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName) { return _to SetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return _to GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return _to SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return _to GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return _to SetRegistrationDomain(aRegistrationDomain); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_BFRESOLVE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Resolve(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Resolve(); } \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFResolveCallback * *aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFResolveCallback * aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetServiceName(nsAString & aServiceName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD SetServiceName(const nsAString & aServiceName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetServiceName(aServiceName); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationDomain(aRegistrationDomain); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public BFResolve
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFRESOLVE

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, BFResolve)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void resolve (); */
NS_IMETHODIMP _MYCLASS_::Resolve()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute BFResolveCallback callback; */
NS_IMETHODIMP _MYCLASS_::GetCallback(BFResolveCallback * *aCallback)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCallback(BFResolveCallback * aCallback)
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

/* End of implementation class template. */
#endif


#endif /* __gen_bfresolve_h__ */
