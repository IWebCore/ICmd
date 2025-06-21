#include "ICmdRequest.h"

$PackageWebCoreBegin

ICmdRequest::ICmdRequest(const QStringList &cmds)
    : m_cmds(cmds)
{
    parseCmd();
    qDebug() << m_executable;
    qDebug() << m_paths;
    qDebug() << m_arguments;
    qDebug() << m_options;
}

void ICmdRequest::parseCmd()
{
    m_executable = m_cmds[0];
    parsePaths();
    parseAguments();
    parseOptions();
}

void ICmdRequest::parsePaths()
{
    for(int i=1; i<m_cmds.length(); i++){
        QString cmd = m_cmds[i];
        if(!cmd.startsWith("-")){
            m_paths.append(cmd);
        }else{
            break;
        }
    }
}

void ICmdRequest::parseAguments()
{
    bool flag{false};
    for(int i=1; i<m_cmds.length(); i++){
        const QString& cmd = m_cmds[i];
        if(flag){
            if(!cmd.startsWith("-")){
                m_arguments.push_back(cmd);
                continue;
            }else {
                flag = false;
            }
        }
        if(cmd == "--"){
            flag = true;
        }
    }
}

void ICmdRequest::parseOptions()
{
    QString option;
    for(int i=1; i<m_cmds.length(); i++){
        const QString& cmd = m_cmds[i];
        if(!option.isEmpty()){
            if(!cmd.startsWith("-")){
                m_options[option].append(cmd);
                continue;
            }else{
                option = "";
            }
        }
        if(cmd != "--" && cmd.startsWith("-")){
            if(cmd.contains("--")){
                option = cmd.mid(2);
            }else{
                option = cmd.mid(1);
            }
        }
    }
}

$PackageWebCoreEnd
