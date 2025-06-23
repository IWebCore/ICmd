#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ICmdAction;
class ICmdRequest;
// TODO: OptionON 和 Option 定义反了, 应该先有 OptionON, 再有 Option.
class ICmdActionOptionOn
{
private:
    using ParamType = std::array<void*, 11>;

public:
    ICmdActionOptionOn();

public:
    void execute(ICmdAction& action, const ICmdRequest& request);

private:
    bool validate(ICmdAction& action, const ICmdRequest& request);
    void invokePreMethod(ICmdAction& action, const ICmdRequest& request);
    void invokePostMethod(ICmdAction& action, const ICmdRequest& request);
    void invokeSetValueMethod(ICmdAction& action, const ICmdRequest& request);

private:
    bool existOption(const ICmdRequest& request) const;

public:
    QString m_name;
    QString m_shortName;
    bool m_isRequired{false};

    QMetaProperty m_property;
    QMetaMethod m_method;           // 设置 method
    QMetaMethod m_preMethod;
    QMetaMethod m_postMethod;
};

$PackageWebCoreEnd
