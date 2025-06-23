#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ICmdAction;
class ICmdRequest;
class ICmdActionWare
{
protected:
    using ParamType = std::array<void*, 11>;

public:
    ICmdActionWare() = default;
    virtual ~ICmdActionWare() = default;

public:
    virtual void execute(ICmdAction& action, const ICmdRequest& request);

protected:
    virtual bool validate(ICmdAction& action, const ICmdRequest& request) = 0;
    virtual void invokePreMethod(ICmdAction& action, const ICmdRequest& request) = 0;
    virtual void invokePostMethod(ICmdAction& action, const ICmdRequest& request) = 0;
    virtual void invokeSetValueMethod(ICmdAction& action, const ICmdRequest& request) = 0;

public:
    QString m_name;
    QMetaProperty m_property;
    QMetaMethod m_method;           // 设置 method
    QMetaMethod m_preMethod;
    QMetaMethod m_postMethod;
};

$PackageWebCoreEnd
