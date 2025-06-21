#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/IGadgetUnit.h"

$PackageWebCoreBegin

class ICmdActionOption;
class ICmdWare : public IGadgetUnit
{
public:
    ICmdWare() = default;

protected:
    void parseAction(void* ptr, const QMap<QString, QString>& info, const QVector<QMetaMethod>& methods, const QVector<QMetaProperty>& props);

private:
    void findPrePath();
    void findOptions();
    void createAction(const QString& key);
    QStringList getActionPaths(const QString& funName);
    QMetaMethod getActionMethod(const QString& funName);

private:
    void *m_ptr;
    QMap<QString, QString> m_info;
    QVector<QMetaMethod> m_methods;
    QVector<QMetaProperty> m_props;

private:
    QStringList m_prePaths;
    QList<ICmdActionOption*> m_options;
};

$PackageWebCoreEnd
