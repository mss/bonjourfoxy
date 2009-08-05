#include "nsIGenericFactory.h"
#include "bfresolve-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CBFRESOLVE)

static nsModuleComponentInfo components[] =
{
    {
       BFRESOLVE_CLASSNAME, 
       BFRESOLVE_CID,
       BFRESOLVE_CONTRACTID,
       CBFRESOLVEConstructor,
    }
};

NS_IMPL_NSGETMODULE("CBFResolveModule", components) 

