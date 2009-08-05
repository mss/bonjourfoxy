#include "nsIGenericFactory.h"
#include "bfbrowse-impl.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(CBFBROWSE)

static nsModuleComponentInfo components[] =
{
    {
       BFBROWSE_CLASSNAME, 
       BFBROWSE_CID,
       BFBROWSE_CONTRACTID,
       CBFBROWSEConstructor,
    }
};

NS_IMPL_NSGETMODULE("BFBrowseModule", components) 

