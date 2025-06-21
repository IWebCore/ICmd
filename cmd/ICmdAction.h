#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IGadgetUnit.h"

$PackageWebCoreBegin

class ICmdActionOption;
class ICmdRequest;
class ICmdAction
{
private:
    using ParamType = std::array<void*, 11>;

public:
    ICmdAction();

public:
    bool isMatch(const ICmdRequest&);
    void execute(const ICmdRequest& request);

private:
    void executeOptions(const ICmdRequest& request);
    void executeMain(const ICmdRequest& request);

private:
    ParamType createParams(const ICmdRequest& request);
    void destroyParams(const ParamType& param);

public:
    void* m_ptr{};
    QStringList m_paths;
    QMetaMethod m_method{};
    IGadgetUnit::StaticMetacallFunction m_callable;
    QList<ICmdActionOption*> m_options;
};

$PackageWebCoreEnd
