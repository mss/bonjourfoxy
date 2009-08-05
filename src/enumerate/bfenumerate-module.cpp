#include "nsIGenericFactory.h"
#include "bfenumerate-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CBFENUMERATE)

static nsModuleComponentInfo components[] =
{
    {
       BFENUMERATE_CLASSNAME, 
       BFENUMERATE_CID,
       BFENUMERATE_CONTRACTID,
       CBFENUMERATEConstructor,
    }
};

NS_IMPL_NSGETMODULE("CBFENUMERATEModule", components) 

