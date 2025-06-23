#include "ICmdManage.h"
#include "cmd/ICmdRequest.h"
#include "cmd/action/ICmdAction.h"

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
