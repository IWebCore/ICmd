#include "ICmdAction.h"
#include "core/application/IApplication.h"
#include "cmd/ICmdRequest.h"
#include "cmd/ICmdException.h"
#include "cmd/action/ICmdOptionValue.h"
#include "cmd/action/ICmdOption.h"
#include "cmd/action/ICmdArgs.h"
#include "cmd/action/ICmdArgx.h"

$PackageWebCoreBegin

ICmdAction::ICmdAction()
{
}

bool ICmdAction::isMatch(const ICmdRequest &request)
{
    if(request.m_paths == m_paths){
        return true;
    }
    return false;
}

void ICmdAction::execute(const ICmdRequest &request)
{
    executeOptions(request);
    executeOptionOns(request);
    executeArgs(request);
    executeArgx(request);
    executeMain(request);
}

void ICmdAction::printHelp()
{
    qDebug().noquote() << "[Memo]: " << m_memo;
    qDebug().noquote() << IApplication::instance().appName() << m_paths.join(" ");
    if(!m_options.isEmpty()){
        qDebug().noquote() << "Options:";
    }
    for(auto opt : m_options){
        opt->printHelp();
        for(auto optVal : m_optionValues){
            if(optVal->m_name == opt->m_name){
                optVal->printHelp();
            }
        }
    }

    if(m_args != nullptr){
        qDebug().noquote() << "Args:";
        m_args->printHelp();
    }
    for(auto argx : m_argxes){
        argx->printHelp();
    }
}

void ICmdAction::executeOptions(const ICmdRequest &request)
{
    for(auto option : m_optionValues){
        try{
            option->execute(*this, request);
        }catch(ICmdException e){
            QString tip = e.getCause();
            qDebug() << "ERROR OCCURED: " << tip << " [Cmd Path]: " << request.m_paths.join(" ")
                     << " [Cmd Arg Type]: Option"
                     << " [Cmd Option Name]: " << option->m_name;
            exit(1);
        }
    }
}

void ICmdAction::executeOptionOns(const ICmdRequest &request)
{
    for(auto on : m_options){
        try{
            on->execute(*this, request);
        }catch(ICmdException e){
            QString tip = e.getCause();
            qDebug() << "ERROR OCCURED: " << tip << " [Cmd Path]: " << request.m_paths.join(" ")
                     << " [Cmd Arg Type]: OptionON"
                     << " [Cmd Option ON Name]: " << on->m_name;
            exit(1);
        }
    }
}

void ICmdAction::executeArgs(const ICmdRequest &request)
{
    if(m_args){
        try{
            m_args->execute(*this, request);
        }catch(ICmdException e){
            QString tip = e.getCause();
            qDebug() << "ERROR OCCURED: " << tip << " [Cmd Path]: " << request.m_paths.join(" ")
                     << " [Cmd Arg Type]: Args"
                     << " [Cmd Arg Values]: " << request.m_arguments.join(", ");
            exit(1);
        }
    }
}

void ICmdAction::executeArgx(const ICmdRequest &request)
{
    for(auto argx : m_argxes){
        try{
           argx->execute(*this, request);
        } catch(ICmdException e){
            QString tip = e.getCause();
            qDebug() << "ERROR OCCURED: " << tip << " [Cmd Path]: " << request.m_paths.join(" ")
                     << " [Cmd Arg Type]: ArgX" << " [ArgX Name]: " << argx->m_name
                     << " [ArgX Index]: " << QString::number(argx->m_index);
            exit(1);
        }
    }
}

void ICmdAction::executeMain(const ICmdRequest& request)
{
    ParamType params{0};
    params[0] = QMetaType::create(QMetaType::Void);
    params[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_method.methodIndex();
    auto obj = static_cast<QObject*>(m_ptr);
    m_callable(obj, QMetaObject::InvokeMetaMethod, index, params.data());

    QMetaType::destroy(QMetaType::Void, params[0]);
}

$PackageWebCoreEnd
