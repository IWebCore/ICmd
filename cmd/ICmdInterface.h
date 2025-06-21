#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISoloUnit.h"
#include "cmd/ICmdManage.h"
#include "cmd/ICmdCatagory.h"
#include "cmd/ICmdWare.h"
#include "cmd/pp/IAsCmdPreProcessor.h"
#include "cmd/pp/ICmdMappingPreProcessor.h"
#include "cmd/pp/ICmdOptionPreProcessor.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"
#include "cmd/pp/ICmdArgsPreProcessor.h"
#include "cmd/pp/ICmdArg1PreProcessor.h"

$PackageWebCoreBegin

namespace detail
{
    template<typename T>
    void setValue(T& value, const QStringList& raws)
    {
        using Type = T;

        if constexpr(std::is_same_v<Type, QStringList>){
            value = raws;
        } else if constexpr (std::is_same_v<Type, QString>){
            value = raws.first();
        } else if constexpr (std::is_same_v<Type, int>){
            value = raws.first().toInt();
        }
    }
}

template<typename T, bool enabled=true>
class ICmdInterface : public ICmdWare, public ITaskWareUnit<T, ICmdCatagory, enabled>, public ISoloUnit<T>
{
public:
    ICmdInterface() = default;

public:
    virtual void $task() final;
};

template<typename T, bool enabled>
void ICmdInterface<T, enabled>::$task()
{
    auto clsInfos = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    auto methods = IMetaUtil::getMetaMethods(T::staticMetaObject);
    auto props = IMetaUtil::getMetaProperties(T::staticMetaObject);
    parseAction(this, clsInfos, methods, props);
}

$PackageWebCoreEnd
