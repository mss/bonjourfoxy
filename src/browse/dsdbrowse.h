/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM dsdbrowse.idl
 */

#ifndef __gen_dsdbrowse_h__
#define __gen_dsdbrowse_h__


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

/* starting interface:    IDSDBROWSE */
#define IDSDBROWSE_IID_STR "c38472d2-9010-4899-b2ae-89adc8eb1246"

#define IDSDBROWSE_IID \
  {0xc38472d2, 0x9010, 0x4899, \
    { 0xb2, 0xae, 0x89, 0xad, 0xc8, 0xeb, 0x12, 0x46 }}

class NS_NO_VTABLE NS_SCRIPTABLE IDSDBROWSE : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IDSDBROWSE_IID)

  /* void start (); */
  NS_SCRIPTABLE NS_IMETHOD Start(void) = 0;

  /* void stop (); */
  NS_SCRIPTABLE NS_IMETHOD Stop(void) = 0;

  /* attribute long interfaceIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) = 0;

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

  /* readonly attribute AString lastName; */
  NS_SCRIPTABLE NS_IMETHOD GetLastName(nsAString & aLastName) = 0;

  /* readonly attribute AString lastRegType; */
  NS_SCRIPTABLE NS_IMETHOD GetLastRegType(nsAString & aLastRegType) = 0;

  /* readonly attribute AString lastDomain; */
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) = 0;

  /* readonly attribute long status; */
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IDSDBROWSE, IDSDBROWSE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IDSDBROWSE \
  NS_SCRIPTABLE NS_IMETHOD Start(void); \
  NS_SCRIPTABLE NS_IMETHOD Stop(void); \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType); \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain); \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain); \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags); \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface); \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode); \
  NS_SCRIPTABLE NS_IMETHOD GetLastName(nsAString & aLastName); \
  NS_SCRIPTABLE NS_IMETHOD GetLastRegType(nsAString & aLastRegType); \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain); \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IDSDBROWSE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return _to Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return _to Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return _to GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return _to SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return _to GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return _to SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return _to GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return _to SetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return _to GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) { return _to GetLastInterface(aLastInterface); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return _to GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastName(nsAString & aLastName) { return _to GetLastName(aLastName); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastRegType(nsAString & aLastRegType) { return _to GetLastRegType(aLastRegType); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) { return _to GetLastDomain(aLastDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return _to GetStatus(aStatus); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IDSDBROWSE(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationType(nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationType(const nsAString & aRegistrationType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationType(aRegistrationType); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegistrationDomain(nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD SetRegistrationDomain(const nsAString & aRegistrationDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetRegistrationDomain(aRegistrationDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastInterface(PRInt32 *aLastInterface) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastInterface(aLastInterface); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastName(nsAString & aLastName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastName(aLastName); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastRegType(nsAString & aLastRegType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastRegType(aLastRegType); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastDomain(aLastDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStatus(aStatus); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IDSDBROWSE
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDBROWSE

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IDSDBROWSE)

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

/* readonly attribute AString lastName; */
NS_IMETHODIMP _MYCLASS_::GetLastName(nsAString & aLastName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute AString lastRegType; */
NS_IMETHODIMP _MYCLASS_::GetLastRegType(nsAString & aLastRegType)
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


#endif /* __gen_dsdbrowse_h__ */
