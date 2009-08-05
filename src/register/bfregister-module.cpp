#include "nsIGenericFactory.h"
#include "bfregister-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CBFREGISTER)

static nsModuleComponentInfo components[] =
{
    {
       BFREGISTER_CLASSNAME, 
       BFREGISTER_CID,
       BFREGISTER_CONTRACTID,
       CBFREGISTERConstructor,
    }
};

NS_IMPL_NSGETMODULE("BFREGISTERModule", components) 

