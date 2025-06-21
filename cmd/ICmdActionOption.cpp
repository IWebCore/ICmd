#include "ICmdActionOption.h"
#include "cmd/ICmdAction.h"
#include "cmd/ICmdRequest.h"

$PackageWebCoreBegin

void ICmdActionOption::execute(ICmdAction &action, const ICmdRequest &request)
{
    auto values = request.m_options.value(m_name);
    if(values.isEmpty() && m_isRequired){
        qFatal("can not be invoked");
    }

    if(m_preMethod.isValid()){
        invokePreMethod(action, request);
    }

    invokeSetValueMethod(action, request);

    if(m_postMethod.isValid()){
        invokePostMethod(action, request);
    }
}

void ICmdActionOption::invokePreMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_preMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionOption::invokePostMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_postMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionOption::invokeSetValueMethod(ICmdAction &action, const ICmdRequest &request)
{
    auto values = request.m_options[m_name];

    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = &values;

    auto index = m_method.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}


$PackageWebCoreEnd
