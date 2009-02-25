/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM dsdregister.idl
 */

#ifndef __gen_dsdregister_h__
#define __gen_dsdregister_h__


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

/* starting interface:    IDSDREGISTER */
#define IDSDREGISTER_IID_STR "3da74016-fbf0-4088-a7b6-82c57ee90d52"

#define IDSDREGISTER_IID \
  {0x3da74016, 0xfbf0, 0x4088, \
    { 0xa7, 0xb6, 0x82, 0xc5, 0x7e, 0xe9, 0x0d, 0x52 }}

class NS_NO_VTABLE NS_SCRIPTABLE IDSDREGISTER : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IDSDREGISTER_IID)

  /* void start (); */
  NS_SCRIPTABLE NS_IMETHOD Start(void) = 0;

  /* void stop (); */
  NS_SCRIPTABLE NS_IMETHOD Stop(void) = 0;

  /* attribute long interfaceIndex; */
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) = 0;

  /* attribute PRBool autorename; */
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename) = 0;

  /* attribute AString name; */
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) = 0;

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

  /* readonly attribute long lastFlags; */
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) = 0;

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

  NS_DEFINE_STATIC_IID_ACCESSOR(IDSDREGISTER, IDSDREGISTER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IDSDREGISTER \
  NS_SCRIPTABLE NS_IMETHOD Start(void); \
  NS_SCRIPTABLE NS_IMETHOD Stop(void); \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex); \
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename); \
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename); \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName); \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName); \
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
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordValue(const nsAString & aTxtRecordValue); \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags); \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode); \
  NS_SCRIPTABLE NS_IMETHOD GetLastName(nsAString & aLastName); \
  NS_SCRIPTABLE NS_IMETHOD GetLastRegType(nsAString & aLastRegType); \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain); \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IDSDREGISTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return _to Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return _to Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return _to GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return _to SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename) { return _to GetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename) { return _to SetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return _to GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return _to SetName(aName); } \
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
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordValue(const nsAString & aTxtRecordValue) { return _to SetTxtRecordValue(aTxtRecordValue); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return _to GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return _to GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastName(nsAString & aLastName) { return _to GetLastName(aLastName); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastRegType(nsAString & aLastRegType) { return _to GetLastRegType(aLastRegType); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) { return _to GetLastDomain(aLastDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return _to GetStatus(aStatus); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IDSDREGISTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Start(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Start(); } \
  NS_SCRIPTABLE NS_IMETHOD Stop(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Stop(); } \
  NS_SCRIPTABLE NS_IMETHOD GetInterfaceIndex(PRInt32 *aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetInterfaceIndex(PRInt32 aInterfaceIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInterfaceIndex(aInterfaceIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetAutorename(PRBool *aAutorename) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD SetAutorename(PRBool aAutorename) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAutorename(aAutorename); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetName(aName); } \
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
  NS_SCRIPTABLE NS_IMETHOD SetTxtRecordValue(const nsAString & aTxtRecordValue) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTxtRecordValue(aTxtRecordValue); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastFlags(PRInt32 *aLastFlags) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastFlags(aLastFlags); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastErrorcode(PRInt32 *aLastErrorcode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastErrorcode(aLastErrorcode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastName(nsAString & aLastName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastName(aLastName); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastRegType(nsAString & aLastRegType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastRegType(aLastRegType); } \
  NS_SCRIPTABLE NS_IMETHOD GetLastDomain(nsAString & aLastDomain) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLastDomain(aLastDomain); } \
  NS_SCRIPTABLE NS_IMETHOD GetStatus(PRInt32 *aStatus) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStatus(aStatus); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IDSDREGISTER
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDREGISTER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IDSDREGISTER)

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

/* attribute PRBool autorename; */
NS_IMETHODIMP _MYCLASS_::GetAutorename(PRBool *aAutorename)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetAutorename(PRBool aAutorename)
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

/* readonly attribute long lastFlags; */
NS_IMETHODIMP _MYCLASS_::GetLastFlags(PRInt32 *aLastFlags)
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


#endif /* __gen_dsdregister_h__ */
