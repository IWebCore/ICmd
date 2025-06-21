#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ICmdAction;
class ICmdRequest;
class ICmdActionOption
{
public:
    using ParamType = std::array<void*, 11>;

public:
    void execute(ICmdAction& action, const ICmdRequest& request);

private:
    void invokePreMethod(ICmdAction& action, const ICmdRequest& request);
    void invokePostMethod(ICmdAction& action, const ICmdRequest& request);
    void invokeSetValueMethod(ICmdAction& action, const ICmdRequest& request);

public:
    bool m_isRequired{false};
    QString m_name;
    QString m_shortName;

    QMetaProperty m_prop;
    QMetaMethod m_method;           // 设置 method
    QMetaMethod m_preMethod;
    QMetaMethod m_postMethod;
};


$PackageWebCoreEnd
