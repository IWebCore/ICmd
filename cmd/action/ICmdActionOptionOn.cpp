#include "ICmdActionOptionOn.h"
#include "cmd/ICmdRequest.h"
#include "cmd/action/ICmdAction.h"

ICmdActionOptionOn::ICmdActionOptionOn()
{

}

void ICmdActionOptionOn::execute(ICmdAction &action, const ICmdRequest &request)
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

bool ICmdActionOptionOn::validate(ICmdAction &action, const ICmdRequest &request)
{
    Q_UNUSED(action)
    if(!existOption(request)){
        if(m_isRequired){
            qFatal("error");
        }else{
            return false;
        }
    }
    return true;
}

void ICmdActionOptionOn::invokePreMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_preMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionOptionOn::invokePostMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_postMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionOptionOn::invokeSetValueMethod(ICmdAction &action, const ICmdRequest &request)
{
    bool m_value = existOption(request);
    m_property.writeOnGadget(action.m_ptr, m_value);
}

bool ICmdActionOptionOn::existOption(const ICmdRequest &request) const
{
    QString shortName = "-" + m_shortName;
    QString fullName = "--" + m_name;
    return request.m_options.contains(shortName) || request.m_options.contains(fullName);
}
