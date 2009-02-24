#include "nsIGenericFactory.h"
#include "dsdenumerate-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CDSDENUMERATE)

static nsModuleComponentInfo components[] =
{
    {
       DSDENUMERATE_CLASSNAME, 
       DSDENUMERATE_CID,
       DSDENUMERATE_CONTRACTID,
       CDSDENUMERATEConstructor,
    }
};

NS_IMPL_NSGETMODULE("DSDENUMERATEModule", components) 

