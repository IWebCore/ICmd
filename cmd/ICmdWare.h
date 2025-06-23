#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IGadgetUnit.h"

$PackageWebCoreBegin

class ICmdAction;
class ICmdActionArgs;
class ICmdActionArgx;
class ICmdActionOptionValue;
class ICmdActionOptionOn;
class ICmdWare : public IGadgetUnit
{
public:
    ICmdWare() = default;

protected:
    void parseAction(void* ptr, const QString& clsName, const QMap<QString, QString>& info, const QVector<QMetaMethod>& methods, const QVector<QMetaProperty>& props);

private:
    void findPrePath();
    void findOptions();
    void findOptionOns();
    void findArgs();
    void findArgx();
    void createActions();
    void createAction(const QString& key);
    QStringList getActionPaths(const QString& funName);
    QMetaMethod getActionMethod(const QString& funName);

private:
    void checkActionMethod(ICmdAction*);
    void checkOptionMethod(ICmdActionOptionValue*);
    void checkOptionOnMethod(ICmdActionOptionOn*);
    void checkArgsMethod();
    void checkArgxMethod(ICmdActionArgx* argx);
    void checkOptionShortNameComflict();
    void checkHandleMethod(const QMetaMethod& method);

private:
    QStringList getMethodArguments(const QMetaMethod& method);

private:
    void *m_ptr;
    QMap<QString, QString> m_info;
    QVector<QMetaMethod> m_methods;
    QVector<QMetaProperty> m_props;

private:
    QString m_className;
    QStringList m_prePaths;
    ICmdActionArgs* m_args{};
    QList<ICmdActionOptionValue*> m_options;
    QList<ICmdActionOptionOn*> m_optionOns;
    QList<ICmdActionArgx*> m_argxes;
    QList<ICmdAction*> m_actions;
};

$PackageWebCoreEnd
