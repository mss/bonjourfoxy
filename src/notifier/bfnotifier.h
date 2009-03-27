/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM bfnotifier.idl
 */

#ifndef __gen_bfnotifier_h__
#define __gen_bfnotifier_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIArray_h__
#include "nsIArray.h"
#endif

#ifndef __gen_nsIMutableArray_h__
#include "nsIMutableArray.h"
#endif

#ifndef __gen_nsIObserver_h__
#include "nsIObserver.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IBFNOTIFIER */
#define IBFNOTIFIER_IID_STR "72427b4d-f37d-4bf8-a6be-41510b27e6a3"

#define IBFNOTIFIER_IID \
  {0x72427b4d, 0xf37d, 0x4bf8, \
    { 0xa6, 0xbe, 0x41, 0x51, 0x0b, 0x27, 0xe6, 0xa3 }}

class NS_NO_VTABLE NS_SCRIPTABLE IBFNOTIFIER : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IBFNOTIFIER_IID)

  /* void observe (in nsISupports aSubject, in string aTopic, in wstring aData); */
  NS_SCRIPTABLE NS_IMETHOD Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IBFNOTIFIER, IBFNOTIFIER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IBFNOTIFIER \
  NS_SCRIPTABLE NS_IMETHOD Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IBFNOTIFIER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData) { return _to Observe(aSubject, aTopic, aData); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IBFNOTIFIER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData) { return !_to ? NS_ERROR_NULL_POINTER : _to->Observe(aSubject, aTopic, aData); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IBFNOTIFIER
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IBFNOTIFIER

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IBFNOTIFIER)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void observe (in nsISupports aSubject, in string aTopic, in wstring aData); */
NS_IMETHODIMP _MYCLASS_::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *aData)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_bfnotifier_h__ */
