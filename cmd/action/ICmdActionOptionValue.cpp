#include "ICmdActionOptionValue.h"
#include "cmd/action/ICmdAction.h"
#include "cmd/ICmdRequest.h"
#include "cmd/ICmdException.h"

$PackageWebCoreBegin

void ICmdActionOptionValue::execute(ICmdAction &action, const ICmdRequest &request)
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

bool ICmdActionOptionValue::validate(ICmdAction &action, const ICmdRequest &request)
{
    Q_UNUSED(action)
    auto values = getOptionValues(request);
    if(values.isEmpty()){
        if(m_isRequired){
            QString position = QString(" [action path]: ").append(action.m_paths.join(" "))
                    .append(" [option name]: ").append(m_name);
            throw ICmdException("action options is required. " + position);
        }
        return false;
    }
    return true;
}

void ICmdActionOptionValue::invokePreMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_preMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionOptionValue::invokePostMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_postMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionOptionValue::invokeSetValueMethod(ICmdAction &action, const ICmdRequest &request)
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

QStringList ICmdActionOptionValue::getOptionValues(const ICmdRequest &request) const
{
    auto fullName = "--" + m_name;
    if(m_shortName.isEmpty()){
        if(request.m_options.contains(fullName)){
            return request.m_options[fullName];
        }
        return {};
    }

    QStringList ret;
    if(request.m_options.contains(fullName)){
        ret = request.m_options[fullName];
    }
    auto shortName = "-" + m_shortName;
    if(request.m_options.contains(shortName)){
        auto opts = request.m_options[shortName];
        for(auto opt : opts){
            ret.append(opt);
        }
    }
    return ret;
}

$PackageWebCoreEnd
