#include "ICmdManage.h"
#include "cmd/ICmdRequest.h"
#include "cmd/action/ICmdAction.h"
#include "core/application/IApplication.h"

$PackageWebCoreBegin

void ICmdManage::printHelp()
{
    qDebug().noquote() << "your input cmd do not match any action";
    qDebug().noquote() << "[Avaliable Cmds]:";

    int length{0};
    for(auto act : m_actions){
        length = std::max({length, act->m_paths.join(" ").length()});
    }
    length += ( IApplication::instance().appName().length() + 4);

    for(auto act : m_actions){
        QString memo;
        if(!act->m_memo.isEmpty()){
            memo = "[Memo]: " + act->m_memo;
        }
        qDebug().noquote().nospace() << qSetFieldWidth(length) << left << (IApplication::instance().appName() + " " + act->m_paths.join(" ")) << memo;
    }
}

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
