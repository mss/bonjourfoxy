/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM dsdenumerate.idl
 */

#ifndef __gen_dsdenumerate_h__
#define __gen_dsdenumerate_h__


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

/* starting interface:    IDSDENUMERATE */
#define IDSDENUMERATE_IID_STR "ae851af1-534b-4d18-ac5f-105a6a49fbb2"

#define IDSDENUMERATE_IID \
  {0xae851af1, 0x534b, 0x4d18, \
    { 0xac, 0x5f, 0x10, 0x5a, 0x6a, 0x49, 0xfb, 0xb2 }}

class NS_NO_VTABLE NS_SCRIPTABLE IDSDENUMERATE : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IDSDENUMERATE_IID)

  /* void start (); */
  NS_SCRIPTABLE NS_IMETHOD Start(void) = 0;

  /* void stop (); */
  NS_SCRIPTABLE NS_IMETHOD Stop(void) = 0;

  /* attribute long type; */
  NS_SCRIPTABLE NS_IMETHOD GetType(PRInt32 *aType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetType(PRInt32 aType) = 0;

  /* attribute long interfaceIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) = 0;

  /* readonly attribute long lastFlags; */
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) = 0;

  /* readonly attribute long lastInterface; */
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) = 0;

  /* readonly attribute long lastErrorcode; */
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) = 0;

  /* readonly attribute AString lastDomain; */
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) = 0;

  /* readonly attribute long status; */
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IDSDENUMERATE, IDSDENUMERATE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IDSDENUMERATE \
  NS_SCRIPTABLE NS_IMETHOD Start(void); \
  NS_SCRIPTABLE NS_IMETHOD Stop(void); \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRInt32 *aType); \
  NS_SCRIPTABLE NS_IMETHOD SetType(PRInt32 aType); \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags); \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface); \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode); \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain); \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IDSDENUMERATE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return _to Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return _to Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRInt32 *aType) { return _to GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(PRInt32 aType) { return _to SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return _to GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return _to SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return _to GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) { return _to GetLastInterface(aLastInterface); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return _to GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) { return _to GetLastDomain(aLastDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return _to GetStatus(aStatus); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IDSDENUMERATE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRInt32 *aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD SetType(PRInt32 aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetType(aType); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastInterface(aLastInterface); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastDomain(aLastDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStatus(aStatus); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IDSDENUMERATE
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDENUMERATE

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IDSDENUMERATE)

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

/* attribute long type; */
NS_IMETHODIMP _MYCLASS_::GetType(PRInt32 *aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetType(PRInt32 aType)
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

/* readonly attribute AString lastDomain; */
NS_IMETHODIMP _MYCLASS_::GetLastDomain(nsAString & aLastDomain)
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


#endif /* __gen_dsdenumerate_h__ */
