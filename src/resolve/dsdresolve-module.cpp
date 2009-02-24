#include "nsIGenericFactory.h"
#include "dsdresolve-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CDSDRESOLVE)

static nsModuleComponentInfo components[] =
{
    {
       DSDRESOLVE_CLASSNAME, 
       DSDRESOLVE_CID,
       DSDRESOLVE_CONTRACTID,
       CDSDRESOLVEConstructor,
    }
};

NS_IMPL_NSGETMODULE("DSDRESOLVEModule", components) 

