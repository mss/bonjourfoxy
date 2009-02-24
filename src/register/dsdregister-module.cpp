#include "nsIGenericFactory.h"
#include "dsdregister-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CDSDREGISTER)

static nsModuleComponentInfo components[] =
{
    {
       DSDREGISTER_CLASSNAME, 
       DSDREGISTER_CID,
       DSDREGISTER_CONTRACTID,
       CDSDREGISTERConstructor,
    }
};

NS_IMPL_NSGETMODULE("DSDREGISTERModule", components) 

