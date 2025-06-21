#include "ICmdServer.h"
#include "core/application/IAsioApplication.h"
#include "cmd/ICmdRequest.h"
#include "cmd/ICmdManage.h"
#include "cmd/ICmdAction.h"

$PackageWebCoreBegin

ICmdServer::ICmdServer()
{
    const auto& arguments = IApplication::instance().arguments();
    ICmdRequest request(arguments);

    auto action = ICmdManage::instance().getAction(request);
    if(!action){
        qFatal("action not found");
    }

    action->execute(request);
}

void ICmdServer::serve()
{
}

$PackageWebCoreEnd
