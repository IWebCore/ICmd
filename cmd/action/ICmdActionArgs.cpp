#include "ICmdActionArgs.h"
#include "cmd/action/ICmdAction.h"
#include "cmd/ICmdRequest.h"

$PackageWebCoreBegin

ICmdActionArgs::ICmdActionArgs()
{
}

void ICmdActionArgs::execute(ICmdAction &action, const ICmdRequest &request)
{
    if(!validate(action, request)){
        return;
    }

    if(m_preMethod.isValid()){
        invokePreMethod(action, request);
    }

    invokeSetValueMethod(action, request);

    if(m_postMethod.isValid()){
        invokePostMethod(action, request);
    }
}

bool ICmdActionArgs::validate(ICmdAction &action, const ICmdRequest &request)
{
    Q_UNUSED(action)
    const auto& values = request.m_arguments;
    if(values.isEmpty() && !m_nullable){
        if(!m_nullable){
            qFatal("can not be invoked");   // TODO: throw!!!
        }
        return false;
    }
    return true;
}

void ICmdActionArgs::invokePreMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_preMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionArgs::invokePostMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_postMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionArgs::invokeSetValueMethod(ICmdAction &action, const ICmdRequest &request)
{
    auto values = request.m_arguments;

    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = &values;

    auto index = m_method.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

$PackageWebCoreEnd
