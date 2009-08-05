/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfenumeratecallback.idl
 */

#ifndef __gen_bfenumeratecallback_h__
#define __gen_bfenumeratecallback_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    BFEnumerateCallback */
#define BFENUMERATECALLBACK_IID_STR "ddcb0a51-162f-46f0-9c59-d529061b184d"

#define BFENUMERATECALLBACK_IID \
  {0xddcb0a51, 0x162f, 0x46f0, \
    { 0x9c, 0x59, 0xd5, 0x29, 0x06, 0x1b, 0x18, 0x4d }}

class NS_NO_VTABLE NS_SCRIPTABLE BFEnumerateCallback : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(BFENUMERATECALLBACK_IID)

  /* void callback (in long error, in PRBool add, in long interfaceIndex, in PRBool registrationDomainType, in AString registrationDomain); */
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, PRBool registrationDomainType, const nsAString & registrationDomain) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(BFEnumerateCallback, BFENUMERATECALLBACK_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_BFENUMERATECALLBACK \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, PRBool registrationDomainType, const nsAString & registrationDomain); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_BFENUMERATECALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, PRBool registrationDomainType, const nsAString & registrationDomain) { return _to Callback(error, add, interfaceIndex, registrationDomainType, registrationDomain); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_BFENUMERATECALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, PRBool registrationDomainType, const nsAString & registrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->Callback(error, add, interfaceIndex, registrationDomainType, registrationDomain); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public BFEnumerateCallback
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFENUMERATECALLBACK

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, BFEnumerateCallback)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void callback (in long error, in PRBool add, in long interfaceIndex, in PRBool registrationDomainType, in AString registrationDomain); */
NS_IMETHODIMP _MYCLASS_::Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, PRBool registrationDomainType, const nsAString & registrationDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_bfenumeratecallback_h__ */
