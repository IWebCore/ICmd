#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ICmdRequest
{
public:
    ICmdRequest(const QStringList& cmds);

private:
    void parseCmd();
    void parsePaths();
    void parseAguments();
    void parseOptions();

public:
    QStringList m_cmds;
    QString m_executable;
    QStringList m_paths;
    QStringList m_arguments;
    QMap<QString, QStringList> m_options;
};

$PackageWebCoreEnd
