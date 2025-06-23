﻿#include "ICmdActionArgx.h"
#include "cmd/ICmdRequest.h"
#include "cmd/ICmdException.h"
#include "cmd/action/ICmdAction.h"

$PackageWebCoreBegin

ICmdActionArgx::ICmdActionArgx()
{
}

void ICmdActionArgx::execute(ICmdAction &action, const ICmdRequest &request)
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

bool ICmdActionArgx::validate(ICmdAction &action, const ICmdRequest &request)
{
    Q_UNUSED(action)
    auto values = request.m_arguments;
    if(values.length() < m_index){
        if(!m_nullable){
            throw ICmdException("args list too short for argx to retrive data. arg count less than " + QString::number(m_index));
        }
        return false;
    }
    return true;
}

void ICmdActionArgx::invokePreMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_preMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionArgx::invokePostMethod(ICmdAction &action, const ICmdRequest &request)
{
    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = const_cast<ICmdRequest*>(&request);

    auto index = m_postMethod.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

void ICmdActionArgx::invokeSetValueMethod(ICmdAction &action, const ICmdRequest &request)
{
    auto value = request.m_arguments[m_index-1];
    QStringList values;
    values.append(value);

    ParamType param;
    param[0] = QMetaType::create(QMetaType::Void);
    param[1] = &values;

    auto index = m_method.methodIndex();
    auto obj = static_cast<QObject*>(action.m_ptr);
    action.m_callable(obj, QMetaObject::InvokeMetaMethod, index, param.data());
    QMetaType::destroy(QMetaType::Void, param[0]);
}

$PackageWebCoreEnd
