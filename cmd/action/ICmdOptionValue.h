#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ICmdAction;
class ICmdRequest;
class ICmdOption;
class ICmdOptionValue
{
private:
    using ParamType = std::array<void*, 11>;

public:
    void execute(ICmdAction& action, const ICmdRequest& request);
    void printHelp();

private:
    bool validate(ICmdAction& action, const ICmdRequest& request);
    void invokePreMethod(ICmdAction& action, const ICmdRequest& request);
    void invokePostMethod(ICmdAction& action, const ICmdRequest& request);
    void invokeSetValueMethod(ICmdAction& action, const ICmdRequest& request);

private:
    QStringList getOptionValues(const ICmdRequest& request) const;

public:
    ICmdOption* m_option{};
    QString m_name;
    QString m_shortName;
    QString m_memo;

    QString m_valueName;

    QMetaProperty m_prop;
    QMetaMethod m_method;
    QMetaMethod m_preMethod;
    QMetaMethod m_postMethod;
};


$PackageWebCoreEnd
