#include "ICmdWare.h"
#include "cmd/ICmdAction.h"
#include "cmd/ICmdActionOption.h"
#include "cmd/ICmdManage.h"

$PackageWebCoreBegin

void ICmdWare::parseAction(void *ptr, const QMap<QString, QString> &infos, const QVector<QMetaMethod> &methods, const QVector<QMetaProperty>& props)
{
    m_ptr = ptr;
    m_info = infos;
    m_methods = methods;
    m_props = props;

    findPrePath();
    findOptions();
    const QString prefix = "IAsCmdMethodMapping$$$";
    for(const auto& key : infos.keys()){
        if(key.startsWith(prefix)){
            createAction(key);
        }
    }
}

void ICmdWare::findPrePath()
{
    QMap<int, QString> pathMap;
    const QString prefix = "IAsCmdClassMapping$$$";
    for(const auto& key : m_info.keys()){
        if(key.startsWith(prefix)){
            pathMap[key.mid(prefix.length()).toInt()] = m_info[key];
        }
    }
    for(int i=1; i<=pathMap.size(); i++){
        m_prePaths.append(pathMap[i]);
    }
    if(m_prePaths.length() == 1){
        QString path = m_prePaths.first();
        if(path.trimmed().isEmpty() || path == "/"){
            m_prePaths.clear();
        }
    }
}

void ICmdWare::findOptions()
{
    for(const QMetaProperty& prop : m_props){
        auto option = new ICmdActionOption;
        option->m_prop = prop;
        QString name = prop.name();
        option->m_name = name;

        //method
        QString methodName = "$set_value_" + name;
        for(const QMetaMethod& method : m_methods){
            if(method.name() == methodName){
                option->m_method = method;
                break;
            }
        }
        if(!option->m_method.isValid()){
            qFatal("method is not valid");
        }

        // required
        QString requiredString = "ICmdOptionRequired$$$" + name;
        option->m_isRequired = m_info.contains(requiredString);

        // short name
        QString optionShortName = "ICmdOptionShortName$$$" + name;
        if(m_info.contains(optionShortName)){
            option->m_shortName = m_info[optionShortName];
        }

        // pre
        QString optionPre = "ICmdOptionPreHandle$$$" + name;
        if(m_info.contains(optionPre)){
            auto name = m_info[optionPre];
            for(const QMetaMethod&method : m_methods){
                if(method.name() == name){
                    option->m_preMethod = method;
                    break;
                }
            }
            if(!option->m_preMethod.isValid()){
                qFatal("option prehandle is define, but function not valid");
            }
        }

        // post
        QString optionPost = "ICmdOptionPostHandle$$$" + name;
        if(m_info.contains(optionPost)){
            auto name = m_info[optionPost];
            for(const QMetaMethod&method : m_methods){
                if(method.name() == name){
                    option->m_postMethod = method;
                    break;
                }
            }
            if(!option->m_postMethod.isValid()){
                qFatal("option posthandle is define, but function not valid");
            }
        }

        m_options.append(option);
    }
}

void ICmdWare::createAction(const QString &key)
{
    auto funName = m_info[key];
    auto action = new ICmdAction;
    action->m_ptr = m_ptr;
    action->m_paths = getActionPaths(funName);
    action->m_method = getActionMethod(funName);
    action->m_callable = (static_cast<IGadgetUnit*>(m_ptr))->staticMetaCallFunction();
    action->m_options = m_options;

    ICmdManage::instance().registAction(action);
}

QStringList ICmdWare::getActionPaths(const QString &funName)
{
    QString prefix = QString("IAsCmdMethodArgMapping$$$").append(funName).append("$$$");
    QMap<int, QString> paths;
    for(const auto& key : m_info.keys()){
        if(key.startsWith(prefix)){
            paths[key.mid(prefix.length()).toInt()] = m_info[key];
        }
    }
    QStringList ret = m_prePaths;
    for(int i=1; i<=paths.size(); i++){
        ret.append(paths[i]);
    }

    return ret;
}

QMetaMethod ICmdWare::getActionMethod(const QString &funName)
{
    for(const QMetaMethod& method : m_methods){
        if(method.name() == funName){
            return method;
        }
    }
    qFatal("method not found");
    return {};
}

$PackageWebCoreEnd
