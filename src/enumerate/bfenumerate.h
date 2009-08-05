/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfenumerate.idl
 */

#ifndef __gen_bfenumerate_h__
#define __gen_bfenumerate_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_bfenumeratecallback_h__
#include "bfenumeratecallback.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    BFEnumerate */
#define BFENUMERATE_IID_STR "20e5d84c-6cd9-41e7-b05d-d7c73a0882fb"

#define BFENUMERATE_IID \
  {0x20e5d84c, 0x6cd9, 0x41e7, \
    { 0xb0, 0x5d, 0xd7, 0xc7, 0x3a, 0x08, 0x82, 0xfb }}

class NS_NO_VTABLE NS_SCRIPTABLE BFEnumerate : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(BFENUMERATE_IID)

  /* void enumerate (); */
  NS_SCRIPTABLE NS_IMETHOD Enumerate(void) = 0;

  /* attribute BFEnumerateCallback callback; */
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFEnumerateCallback * *aCallback) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFEnumerateCallback * aCallback) = 0;

  /* attribute PRBool type; */
  NS_SCRIPTABLE NS_IMETHOD GetType(PRBool *aType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetType(PRBool aType) = 0;

  /* attribute long interfaceIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(BFEnumerate, BFENUMERATE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_BFENUMERATE \
  NS_SCRIPTABLE NS_IMETHOD Enumerate(void); \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFEnumerateCallback * *aCallback); \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFEnumerateCallback * aCallback); \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRBool *aType); \
  NS_SCRIPTABLE NS_IMETHOD SetType(PRBool aType); \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_BFENUMERATE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Enumerate(void) { return _to Enumerate(); } \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFEnumerateCallback * *aCallback) { return _to GetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFEnumerateCallback * aCallback) { return _to SetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRBool *aType) { return _to GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(PRBool aType) { return _to SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return _to GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return _to SetInterfaceIndex(aInterfaceIndex); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_BFENUMERATE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Enumerate(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Enumerate(); } \
  NS_SCRIPTABLE NS_IMETHOD GetCallback(BFEnumerateCallback * *aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD SetCallback(BFEnumerateCallback * aCallback) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCallback(aCallback); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRBool *aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(PRBool aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInterfaceIndex(aInterfaceIndex); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public BFEnumerate
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_BFENUMERATE

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, BFEnumerate)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void enumerate (); */
NS_IMETHODIMP _MYCLASS_::Enumerate()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute BFEnumerateCallback callback; */
NS_IMETHODIMP _MYCLASS_::GetCallback(BFEnumerateCallback * *aCallback)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetCallback(BFEnumerateCallback * aCallback)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute PRBool type; */
NS_IMETHODIMP _MYCLASS_::GetType(PRBool *aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetType(PRBool aType)
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

/* End of implementation class template. */
#endif


#endif /* __gen_bfenumerate_h__ */
