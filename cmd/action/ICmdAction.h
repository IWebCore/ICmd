#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IGadgetUnit.h"

$PackageWebCoreBegin

class ICmdRequest;
class ICmdActionArgs;
class ICmdActionArgx;
class ICmdActionOptionValue;
class ICmdActionOptionOn;
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
    void executeOptionOns(const ICmdRequest& request);
    void executeArgs(const ICmdRequest& request);
    void executeArgx(const ICmdRequest& request);
    void executeMain(const ICmdRequest& request);

private:
    ParamType createParams(const ICmdRequest& request);
    void destroyParams(const ParamType& param);

public:
    void* m_ptr{};
    QStringList m_paths;
    QMetaMethod m_method{};
    IGadgetUnit::StaticMetacallFunction m_callable;

    ICmdActionArgs* m_args{nullptr};
    QList<ICmdActionOptionValue*> m_options;
    QList<ICmdActionOptionOn*> m_optionOns;
    QList<ICmdActionArgx*> m_argxes;

public:
    QString m_memo;
};

$PackageWebCoreEnd
