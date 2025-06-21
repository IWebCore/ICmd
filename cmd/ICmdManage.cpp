#include "ICmdManage.h"
#include "cmd/ICmdAction.h"
#include "cmd/ICmdRequest.h"

$PackageWebCoreBegin

void ICmdManage::registAction(ICmdAction *action)
{
    m_actions.append(action);
}

ICmdAction *ICmdManage::getAction(const ICmdRequest &request)
{
    for(auto action : m_actions){
        if(action->isMatch(request)){
            return action;
        }
    }
    return nullptr;
}

$PackageWebCoreEnd
