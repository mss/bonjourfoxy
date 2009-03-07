/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM dsdmanager.idl
 */

#ifndef __gen_dsdmanager_h__
#define __gen_dsdmanager_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIArray_h__
#include "nsIArray.h"
#endif

#ifndef __gen_nsIMutableArray_h__
#include "nsIMutableArray.h"
#endif

#ifndef __gen_dsdmanager_h__
#include "dsdmanager.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IDSDMANAGER */
#define IDSDMANAGER_IID_STR "2a4a57ac-0b06-4fdc-aa3a-f8e4e9195f50"

#define IDSDMANAGER_IID \
  {0x2a4a57ac, 0x0b06, 0x4fdc, \
    { 0xaa, 0x3a, 0xf8, 0xe4, 0xe9, 0x19, 0x5f, 0x50 }}

class NS_NO_VTABLE NS_SCRIPTABLE IDSDMANAGER : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IDSDMANAGER_IID)

  /* void handleEvent (in AString from, in PRBool isError, in nsIArray data); */
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, PRBool isError, nsIArray *data) = 0;

  /* PRBool discoverServices (in AString regType, in AString regDomain); */
  NS_SCRIPTABLE NS_IMETHOD DiscoverServices(const nsAString & regType, const nsAString & regDomain, PRBool *_retval) = 0;

  /* nsIArray getDiscoveredDomains (in AString domainType); */
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomains(const nsAString & domainType, nsIArray **_retval) = 0;

  /* PRUint32 getDiscoveredDomainsCount (in AString domainType); */
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomainsCount(const nsAString & domainType, PRUint32 *_retval) = 0;

  /* nsIArray getDiscoveredServices (in AString regType, in AString regDomain); */
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServices(const nsAString & regType, const nsAString & regDomain, nsIArray **_retval) = 0;

  /* PRUint32 getDiscoveredServicesCount (in AString regType, in AString regDomain); */
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServicesCount(const nsAString & regType, const nsAString & regDomain, PRUint32 *_retval) = 0;

  /* nsIArray resolveService (in AString serviceName, in AString regType, in AString regDomain, in long timeout); */
  NS_SCRIPTABLE NS_IMETHOD ResolveService(const nsAString & serviceName, const nsAString & regType, const nsAString & regDomain, PRInt32 timeout, nsIArray **_retval) = 0;

  /* AString addService (in AString serviceName, in AString regType, in AString targetHost, in long targetPort, in AString txtKey, in AString txtValue, in AString regDomain); */
  NS_SCRIPTABLE NS_IMETHOD AddService(const nsAString & serviceName, const nsAString & regType, const nsAString & targetHost, PRInt32 targetPort, const nsAString & txtKey, const nsAString & txtValue, const nsAString & regDomain, nsAString & _retval) = 0;

  /* void removeService (in AString identifier); */
  NS_SCRIPTABLE NS_IMETHOD RemoveService(const nsAString & identifier) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IDSDMANAGER, IDSDMANAGER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IDSDMANAGER \
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, PRBool isError, nsIArray *data); \
  NS_SCRIPTABLE NS_IMETHOD DiscoverServices(const nsAString & regType, const nsAString & regDomain, PRBool *_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomains(const nsAString & domainType, nsIArray **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomainsCount(const nsAString & domainType, PRUint32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServices(const nsAString & regType, const nsAString & regDomain, nsIArray **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServicesCount(const nsAString & regType, const nsAString & regDomain, PRUint32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD ResolveService(const nsAString & serviceName, const nsAString & regType, const nsAString & regDomain, PRInt32 timeout, nsIArray **_retval); \
  NS_SCRIPTABLE NS_IMETHOD AddService(const nsAString & serviceName, const nsAString & regType, const nsAString & targetHost, PRInt32 targetPort, const nsAString & txtKey, const nsAString & txtValue, const nsAString & regDomain, nsAString & _retval); \
  NS_SCRIPTABLE NS_IMETHOD RemoveService(const nsAString & identifier); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IDSDMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, PRBool isError, nsIArray *data) { return _to HandleEvent(from, isError, data); } \
  NS_SCRIPTABLE NS_IMETHOD DiscoverServices(const nsAString & regType, const nsAString & regDomain, PRBool *_retval) { return _to DiscoverServices(regType, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomains(const nsAString & domainType, nsIArray **_retval) { return _to GetDiscoveredDomains(domainType, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomainsCount(const nsAString & domainType, PRUint32 *_retval) { return _to GetDiscoveredDomainsCount(domainType, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServices(const nsAString & regType, const nsAString & regDomain, nsIArray **_retval) { return _to GetDiscoveredServices(regType, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServicesCount(const nsAString & regType, const nsAString & regDomain, PRUint32 *_retval) { return _to GetDiscoveredServicesCount(regType, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD ResolveService(const nsAString & serviceName, const nsAString & regType, const nsAString & regDomain, PRInt32 timeout, nsIArray **_retval) { return _to ResolveService(serviceName, regType, regDomain, timeout, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddService(const nsAString & serviceName, const nsAString & regType, const nsAString & targetHost, PRInt32 targetPort, const nsAString & txtKey, const nsAString & txtValue, const nsAString & regDomain, nsAString & _retval) { return _to AddService(serviceName, regType, targetHost, targetPort, txtKey, txtValue, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveService(const nsAString & identifier) { return _to RemoveService(identifier); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IDSDMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, PRBool isError, nsIArray *data) { return !_to ? NS_ERROR_NULL_POINTER : _to->HandleEvent(from, isError, data); } \
  NS_SCRIPTABLE NS_IMETHOD DiscoverServices(const nsAString & regType, const nsAString & regDomain, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->DiscoverServices(regType, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomains(const nsAString & domainType, nsIArray **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDiscoveredDomains(domainType, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredDomainsCount(const nsAString & domainType, PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDiscoveredDomainsCount(domainType, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServices(const nsAString & regType, const nsAString & regDomain, nsIArray **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDiscoveredServices(regType, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDiscoveredServicesCount(const nsAString & regType, const nsAString & regDomain, PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDiscoveredServicesCount(regType, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD ResolveService(const nsAString & serviceName, const nsAString & regType, const nsAString & regDomain, PRInt32 timeout, nsIArray **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ResolveService(serviceName, regType, regDomain, timeout, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AddService(const nsAString & serviceName, const nsAString & regType, const nsAString & targetHost, PRInt32 targetPort, const nsAString & txtKey, const nsAString & txtValue, const nsAString & regDomain, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddService(serviceName, regType, targetHost, targetPort, txtKey, txtValue, regDomain, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD RemoveService(const nsAString & identifier) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveService(identifier); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IDSDMANAGER
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDSDMANAGER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IDSDMANAGER)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void handleEvent (in AString from, in PRBool isError, in nsIArray data); */
NS_IMETHODIMP _MYCLASS_::HandleEvent(const nsAString & from, PRBool isError, nsIArray *data)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* PRBool discoverServices (in AString regType, in AString regDomain); */
NS_IMETHODIMP _MYCLASS_::DiscoverServices(const nsAString & regType, const nsAString & regDomain, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIArray getDiscoveredDomains (in AString domainType); */
NS_IMETHODIMP _MYCLASS_::GetDiscoveredDomains(const nsAString & domainType, nsIArray **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* PRUint32 getDiscoveredDomainsCount (in AString domainType); */
NS_IMETHODIMP _MYCLASS_::GetDiscoveredDomainsCount(const nsAString & domainType, PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIArray getDiscoveredServices (in AString regType, in AString regDomain); */
NS_IMETHODIMP _MYCLASS_::GetDiscoveredServices(const nsAString & regType, const nsAString & regDomain, nsIArray **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* PRUint32 getDiscoveredServicesCount (in AString regType, in AString regDomain); */
NS_IMETHODIMP _MYCLASS_::GetDiscoveredServicesCount(const nsAString & regType, const nsAString & regDomain, PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIArray resolveService (in AString serviceName, in AString regType, in AString regDomain, in long timeout); */
NS_IMETHODIMP _MYCLASS_::ResolveService(const nsAString & serviceName, const nsAString & regType, const nsAString & regDomain, PRInt32 timeout, nsIArray **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AString addService (in AString serviceName, in AString regType, in AString targetHost, in long targetPort, in AString txtKey, in AString txtValue, in AString regDomain); */
NS_IMETHODIMP _MYCLASS_::AddService(const nsAString & serviceName, const nsAString & regType, const nsAString & targetHost, PRInt32 targetPort, const nsAString & txtKey, const nsAString & txtValue, const nsAString & regDomain, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeService (in AString identifier); */
NS_IMETHODIMP _MYCLASS_::RemoveService(const nsAString & identifier)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_dsdmanager_h__ */
