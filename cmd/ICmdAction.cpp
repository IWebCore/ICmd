#include "ICmdAction.h"
#include "cmd/ICmdRequest.h"
#include "cmd/ICmdActionOption.h"

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
    executeMain(request);
}

void ICmdAction::executeOptions(const ICmdRequest &request)
{
    for(auto option : m_options){
        option->execute(*this, request);
    }
}

void ICmdAction::executeMain(const ICmdRequest& request)
{
    auto params = createParams(request);

    auto index = m_method.methodIndex();
    auto obj = static_cast<QObject*>(m_ptr);
    m_callable(obj, QMetaObject::InvokeMetaMethod, index, params.data());

    destroyParams(params);
}

ICmdAction::ParamType ICmdAction::createParams(const ICmdRequest &request)
{
    ParamType params{0};
    params[0] = QMetaType::create(QMetaType::Void);
    return params;
}

void ICmdAction::destroyParams(const ICmdAction::ParamType &param)
{
    QMetaType::destroy(QMetaType::Void, param[0]);
}

$PackageWebCoreEnd
