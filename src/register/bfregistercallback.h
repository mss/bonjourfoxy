/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfregistercallback.idl
 */

#ifndef __gen_bfregistercallback_h__
#define __gen_bfregistercallback_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    BFRegisterCallback */
#define BFREGISTERCALLBACK_IID_STR "d30b69b4-d734-425e-b476-c08a011de5d8"

#define BFREGISTERCALLBACK_IID \
  {0xd30b69b4, 0xd734, 0x425e, \
    { 0xb4, 0x76, 0xc0, 0x8a, 0x01, 0x1d, 0xe5, 0xd8 }}

class NS_NO_VTABLE NS_SCRIPTABLE BFRegisterCallback : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(BFREGISTERCALLBACK_IID)

  /* void callback (in long error, in long interfaceIndex, in PRBool add, in AString serviceName, in AString registrationType, in AString registrationDomain); */
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, PRBool add, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(BFRegisterCallback, BFREGISTERCALLBACK_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_BFREGISTERCALLBACK \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, PRBool add, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_BFREGISTERCALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, PRBool add, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain) { return _to Callback(error, interfaceIndex, add, serviceName, registrationType, registrationDomain); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_BFREGISTERCALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, PRBool add, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->Callback(error, interfaceIndex, add, serviceName, registrationType, registrationDomain); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public BFRegisterCallback
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFREGISTERCALLBACK

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, BFRegisterCallback)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void callback (in long error, in long interfaceIndex, in PRBool add, in AString serviceName, in AString registrationType, in AString registrationDomain); */
NS_IMETHODIMP _MYCLASS_::Callback(PRInt32 error, PRInt32 interfaceIndex, PRBool add, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_bfregistercallback_h__ */
