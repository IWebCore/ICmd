#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ICmdAction;
class ICmdRequest;
class ICmdActionOptionValue
{
private:
    using ParamType = std::array<void*, 11>;

public:
    void execute(ICmdAction& action, const ICmdRequest& request);

private:
    bool validate(ICmdAction& action, const ICmdRequest& request);
    void invokePreMethod(ICmdAction& action, const ICmdRequest& request);
    void invokePostMethod(ICmdAction& action, const ICmdRequest& request);
    void invokeSetValueMethod(ICmdAction& action, const ICmdRequest& request);

private:
    QStringList getOptionValues(const ICmdRequest& request) const;

public:
    bool m_isRequired{false};
    QString m_name;
    QString m_shortName;

    QMetaProperty m_prop;
    QMetaMethod m_method;           // 设置 method
    QMetaMethod m_preMethod;
    QMetaMethod m_postMethod;

public:
    QString m_memo;
};


$PackageWebCoreEnd
