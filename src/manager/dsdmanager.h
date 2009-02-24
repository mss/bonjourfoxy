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

  /* void handleEvent (in AString from, in nsIArray data); */
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, nsIArray *data) = 0;

  /* readonly attribute PRBool acceptEvents; */
  NS_SCRIPTABLE NS_IMETHOD GetAcceptEvents(PRBool *aAcceptEvents) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IDSDMANAGER, IDSDMANAGER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IDSDMANAGER \
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, nsIArray *data); \
  NS_SCRIPTABLE NS_IMETHOD GetAcceptEvents(PRBool *aAcceptEvents); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IDSDMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, nsIArray *data) { return _to HandleEvent(from, data); } \
  NS_SCRIPTABLE NS_IMETHOD GetAcceptEvents(PRBool *aAcceptEvents) { return _to GetAcceptEvents(aAcceptEvents); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IDSDMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD HandleEvent(const nsAString & from, nsIArray *data) { return !_to ? NS_ERROR_NULL_POINTER : _to->HandleEvent(from, data); } \
  NS_SCRIPTABLE NS_IMETHOD GetAcceptEvents(PRBool *aAcceptEvents) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAcceptEvents(aAcceptEvents); } 

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

/* void handleEvent (in AString from, in nsIArray data); */
NS_IMETHODIMP _MYCLASS_::HandleEvent(const nsAString & from, nsIArray *data)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRBool acceptEvents; */
NS_IMETHODIMP _MYCLASS_::GetAcceptEvents(PRBool *aAcceptEvents)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_dsdmanager_h__ */
