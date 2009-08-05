/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfresolvecallback.idl
 */

#ifndef __gen_bfresolvecallback_h__
#define __gen_bfresolvecallback_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    BFResolveCallback */
#define BFRESOLVECALLBACK_IID_STR "5ad26d20-a085-4bee-a3a9-06925bad5aad"

#define BFRESOLVECALLBACK_IID \
  {0x5ad26d20, 0xa085, 0x4bee, \
    { 0xa3, 0xa9, 0x06, 0x92, 0x5b, 0xad, 0x5a, 0xad }}

class NS_NO_VTABLE NS_SCRIPTABLE BFResolveCallback : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(BFRESOLVECALLBACK_IID)

  /* void callback (in long error, in long interfaceIndex, in AString hostname, in long port, in AString txtKey, in AString txtValue); */
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, const nsAString & hostname, PRInt32 port, const nsAString & txtKey, const nsAString & txtValue) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(BFResolveCallback, BFRESOLVECALLBACK_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_BFRESOLVECALLBACK \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, const nsAString & hostname, PRInt32 port, const nsAString & txtKey, const nsAString & txtValue); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_BFRESOLVECALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, const nsAString & hostname, PRInt32 port, const nsAString & txtKey, const nsAString & txtValue) { return _to Callback(error, interfaceIndex, hostname, port, txtKey, txtValue); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_BFRESOLVECALLBACK(_to) \
  NS_SCRIPTABLE NS_IMETHOD Callback(PRInt32 error, PRInt32 interfaceIndex, const nsAString & hostname, PRInt32 port, const nsAString & txtKey, const nsAString & txtValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->Callback(error, interfaceIndex, hostname, port, txtKey, txtValue); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public BFResolveCallback
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFRESOLVECALLBACK

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, BFResolveCallback)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void callback (in long error, in long interfaceIndex, in AString hostname, in long port, in AString txtKey, in AString txtValue); */
NS_IMETHODIMP _MYCLASS_::Callback(PRInt32 error, PRInt32 interfaceIndex, const nsAString & hostname, PRInt32 port, const nsAString & txtKey, const nsAString & txtValue)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_bfresolvecallback_h__ */
