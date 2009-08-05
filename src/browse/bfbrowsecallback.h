/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfbrowsecallback.idl
 */

#ifndef __gen_bfbrowsecallback_h__
#define __gen_bfbrowsecallback_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    BFBrowseCallback */
#define BFBROWSECALLBACK_IID_STR "3ec0d8fa-0c42-403c-8a35-c161d1f1541e"

#define BFBROWSECALLBACK_IID \
  {0x3ec0d8fa, 0x0c42, 0x403c, \
    { 0x8a, 0x35, 0xc1, 0x61, 0xd1, 0xf1, 0x54, 0x1e }}

class NS_NO_VTABLE NS_SCRIPTABLE BFBrowseCallback : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(BFBROWSECALLBACK_IID)

  /* void callback (in long error, in PRBool add, in long interfaceIndex, in AString serviceName, in AString registrationType, in AString registrationDomain); */
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(BFBrowseCallback, BFBROWSECALLBACK_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_BFBROWSECALLBACK \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_BFBROWSECALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain) { return _to Callback(error, add, interfaceIndex, serviceName, registrationType, registrationDomain); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_BFBROWSECALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->Callback(error, add, interfaceIndex, serviceName, registrationType, registrationDomain); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public BFBrowseCallback
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFBROWSECALLBACK

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, BFBrowseCallback)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void callback (in long error, in PRBool add, in long interfaceIndex, in AString serviceName, in AString registrationType, in AString registrationDomain); */
NS_IMETHODIMP _MYCLASS_::Callback(PRInt32 error, PRBool add, PRInt32 interfaceIndex, const nsAString & serviceName, const nsAString & registrationType, const nsAString & registrationDomain)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_bfbrowsecallback_h__ */
