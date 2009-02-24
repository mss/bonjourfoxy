#include "nsIGenericFactory.h"
#include "dsdbrowse-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CDSDBROWSE)

static nsModuleComponentInfo components[] =
{
    {
       DSDBROWSE_CLASSNAME, 
       DSDBROWSE_CID,
       DSDBROWSE_CONTRACTID,
       CDSDBROWSEConstructor,
    }
};

NS_IMPL_NSGETMODULE("DSDBROWSEModule", components) 

