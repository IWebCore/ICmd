#include "ICmdWare.h"
#include "cmd/ICmdManage.h"
#include "cmd/ICmdException.h"
#include "cmd/action/ICmdAction.h"
#include "cmd/action/ICmdActionArgs.h"
#include "cmd/action/ICmdActionArgx.h"
#include "cmd/action/ICmdActionOptionValue.h"
#include "cmd/action/ICmdActionOptionOn.h"

$PackageWebCoreBegin

void ICmdWare::parseAction(void *ptr, const QString& clsName, const QMap<QString, QString> &infos, const QVector<QMetaMethod> &methods, const QVector<QMetaProperty>& props)
{
    m_ptr = ptr;
    m_className = clsName;
    m_info = infos;
    m_methods = methods;
    m_props = props;

    try{
        findPrePath();
        findOptions();
        findOptionOns();
        findArgs();
        findArgx();
        createActions();
    } catch(ICmdException e){
        qDebug() << e.getCause();
        throw e;
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
    QString position = QString(" [Class]: ").append(m_className);

    QStringList optionNames;
    for(const QString& key : m_info.keys()){
        if(key.startsWith("ICmdOptionArgument$$$")){
            auto name = m_info[key];
            optionNames.append(name);
        }
    }

    for(auto name : optionNames){
        // prop, name
        auto option = new ICmdActionOptionValue;
        option->m_name = name;

        for(const QMetaProperty& prop : m_props){
            if(prop.name() == name){
                option->m_prop = prop;
            }
        }

        //method
        QString methodName = "$set_value_" + name;
        for(const QMetaMethod& method : m_methods){
            if(method.name() == methodName){
                option->m_method = method;
                break;
            }
        }
        if(!option->m_method.isValid()){
            throw ICmdException("Cmd Option must have its $set_value_xxx method. " + QString(" [Option Name]: ").append(name)  + position);
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
                throw ICmdException("Option PreHandle function is defined, but function not found. "
                                    + QString(" [Option Name]: ").append(name).append(" [Defined Function]: ").append(name)  + position);
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
                throw ICmdException("Option PostHandle function is defined, but function not found. "
                                    + QString(" [Option Name]: ").append(name).append(" [Defined Function]: ").append(name)  + position);
            }
        }
        checkOptionMethod(option);
        m_options.append(option);
    }
    checkOptionShortNameComflict();
}

void ICmdWare::findOptionOns()
{
    QString position = QString(" [Class]: ").append(m_className);
    QMap<QString, QString> map;
    for(auto key : m_info.keys()){
        if(key.startsWith("ICmdOptionOn$$$")){
            map[key.mid(QString("ICmdOptionOn$$$").length())] = m_info[key];
        }
    }

    for(auto option : map.keys()){
        auto name = map[option];
        auto optionOn = new ICmdActionOptionOn();
        optionOn->m_name = option;

        for(const QMetaProperty& prop : m_props){
            if(prop.name() == name){
                optionOn->m_property = prop;
            }
        }

        // required
        QString requiredString = "ICmdOptionOnRequired$$$" + name;
        optionOn->m_isRequired = m_info.contains(requiredString);

        // pre
        QString optionPre = "ICmdOptionOnPreHandle$$$" + name;
        if(m_info.contains(optionPre)){
            auto name = m_info[optionPre];
            for(const QMetaMethod&method : m_methods){
                if(method.name() == name){
                    optionOn->m_preMethod = method;
                    break;
                }
            }
            if(!optionOn->m_preMethod.isValid()){
                throw ICmdException("OptionON PreHandle function is defined, but function not found. "
                                    + QString(" [OptionOn Name]: ").append(name).append(" [Defined Function]: ").append(name)  + position);
            }
        }

        // post
        QString optionPost = "ICmdOptionOnPostHandle$$$" + name;
        if(m_info.contains(optionPost)){
            auto name = m_info[optionPost];
            for(const QMetaMethod&method : m_methods){
                if(method.name() == name){
                    optionOn->m_postMethod = method;
                    break;
                }
            }
            if(!optionOn->m_postMethod.isValid()){
                throw ICmdException("OptionON PostHandle function is defined, but function not found. "
                                    + QString(" [Option Name]: ").append(name).append(" [Defined Function]: ").append(name)  + position);
            }
        }
        checkOptionOnMethod(optionOn);
        m_optionOns.append(optionOn);
    }
}

void ICmdWare::findArgs()
{
    QStringList names;
    for(const QString& key : m_info.keys()){
        if(key.startsWith("ICmdArgsArgument$$$")){
            names.append(m_info[key]);
        }
    }
    if(names.length() == 0){
        return;
    }
    if(names.length() > 1){
        throw ICmdException("$CmdArgs must be only at most one. " + QString(" [Class]: ").append(m_className));
    }

    QString name = names.first();
    QString position = QString(" [Class]: ").append(m_className).append(" [Args Name]: ").append(name);

    // prop, name
    m_args = new ICmdActionArgs;
    m_args->m_name = name;
    for(const QMetaProperty& prop : m_props){
        if(prop.name() == name){
            m_args->m_prop = prop;
        }
    }

    //method
    QString methodName = "$set_value_" + name;
    for(const QMetaMethod& method : m_methods){
        if(method.name() == methodName){
            m_args->m_method = method;
            break;
        }
    }

    // required
    QString nullableString = "ICmdArgsNullable$$$" + name;
    m_args->m_nullable = m_info.contains(nullableString);

    // pre
    QString optionPre = "ICmdArgsPreHandle$$$" + name;
    if(m_info.contains(optionPre)){
        auto name = m_info[optionPre];
        for(const QMetaMethod&method : m_methods){
            if(method.name() == name){
                m_args->m_preMethod = method;
                break;
            }
        }
        if(!m_args->m_preMethod.isValid()){
            throw ICmdException("option prehandle is define, but function not valid. " + position);
        }
    }

    // post
    QString optionPost = "ICmdArgsPostHandle$$$" + name;
    if(m_info.contains(optionPost)){
        auto name = m_info[optionPost];
        for(const QMetaMethod&method : m_methods){
            if(method.name() == name){
                m_args->m_postMethod = method;
                break;
            }
        }
        if(!m_args->m_postMethod.isValid()){
            throw ICmdException("option posthandle is define, but function not valid. " + position);
        }
    }
    checkArgsMethod();
}

void ICmdWare::findArgx()
{
    QString position = QString(" [Class]: ").append(m_className);
    QMap<int, QString> map;
    for(const QString& key : m_info.keys()){
        if(key.startsWith("ICmdArgXArgument$$$")){
            auto index = key.split("$$$")[1].toInt();
            auto name = m_info[key];
            if(map.contains(index)){
                throw ICmdException("argx index conflict. " + QString(" [index]: ").append(QString::number(index)) + position);
            }
            if(map.values().contains(name)){
                throw ICmdException("argx name duplicated. " + QString(" [name]: ").append(name) + position);
            }
            map[index] = m_info[key];
        }
    }

    for(auto index: map.keys()){
        auto name = map[index];

        auto argx = new ICmdActionArgx;
        argx->m_index = index;
        argx->m_name = name;

        auto methodName = "$set_value_" + name;
        for(const QMetaMethod& method : m_methods){
            if(method.name() == methodName){
                argx->m_method = method;
            }
        }

        // pre
        QString optionPre = "ICmdArg" + QString::number(argx->m_index) + "PreHandle$$$" + name;
        if(m_info.contains(optionPre)){
            auto funNamename = m_info[optionPre];
            for(const QMetaMethod&method : m_methods){
                if(method.name() == funNamename){
                    argx->m_preMethod = method;
                    break;
                }
            }
            if(!argx->m_preMethod.isValid()){
                throw ICmdException("argx PreHandle function is define, but function not valid"
                                    + QString(" [name]: ").append(name)
                                    + QString(" [index]: ").append(QString::number(index))
                                    + QString(" [PreHandle function]: ").append(funNamename)
                                    + position);
            }
        }

        // post
        QString optionPost = "ICmdArg" + QString::number(argx->m_index) + "PostHandle$$$" + name;
        if(m_info.contains(optionPost)){
            auto funName = m_info[optionPost];
            for(const QMetaMethod&method : m_methods){
                if(method.name() == funName){
                    argx->m_postMethod = method;
                    break;
                }
            }
            if(!argx->m_postMethod.isValid()){
                throw ICmdException("argx PostHandle function is define, but function not valid"
                                    + QString(" [name]: ").append(name)
                                    + QString(" [index]: ").append(QString::number(index))
                                    + QString(" [PostHandle function]: ").append(funName)
                                    + position);
            }
        }

        QString nullableStr = "ICmdArgXNullable$$$" + name + "$$$" + QString::number(argx->m_index);
        argx->m_nullable = m_info.contains(nullableStr);

        checkArgxMethod(argx);
        this->m_argxes.append(argx);
    }
}

void ICmdWare::createActions()
{
    const QString prefix = "IAsCmdMethodMapping$$$";
    for(const auto& key : m_info.keys()){
        if(key.startsWith(prefix)){
            createAction(key);
        }
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
    action->m_args = m_args;
    action->m_argxes = m_argxes;

    checkActionMethod(action);
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
    return {};
}

void ICmdWare::checkActionMethod(ICmdAction *action)
{
    QString position = QString(" [Mapping Path]: ").append(action->m_paths.join("/"))
            .append(" [FunctionName]: ").append(action->m_method.name())
            .append(" [Class]: ").append(m_className);

    if(!action->m_method.isValid()){
        throw ICmdException("action mapping method is not valid. " + position);
    }

    if(action->m_method.returnType() != QMetaType::Void){
        throw ICmdException("action mapping method return type must be void. " + position);
    }

    auto argTypes = getMethodArguments(action->m_method);
    if(argTypes.length() > 1){
        throw ICmdException("action mapping method arguments count should be one or zero. " + position);
    }
    if(argTypes.length() == 1){
        if(argTypes.first() != "ICmdRequest" || argTypes.first() != "ICmdRequest&" ){
            throw ICmdException("action mapping method arguments type can only be ICmdRequest. " + position);
        }
    }

    if(action->m_paths.isEmpty()){
        throw ICmdException("action mapping path can not be none. " + position);
    }

    for(const QString& path : action->m_paths){
        if(path.trimmed().isEmpty()){
            throw ICmdException("action mapping path can not be empty. " + position);
        }
    }
}

void ICmdWare::checkOptionMethod(ICmdActionOptionValue *option)
{
    QString position = QString(" [Class]: ").append(m_className).append(" [Option Name]: ").append(option->m_name);
    if(!option->m_method.isValid()){
        throw ICmdException("Option $set_value_xxx method is not valid. " + position);
    }
}

void ICmdWare::checkOptionOnMethod(ICmdActionOptionOn *optionOn)
{
    QString position = QString(" [Class]: ").append(m_className).append(" [OptionOn Name]: ").append(optionOn->m_name);
    if(!optionOn->m_property.isValid()){
        throw ICmdException("OptionOn property is not valid. "
                            + position);
    }

    bool existOption{false};
    QString name = optionOn->m_name;
    for(auto option : m_options){
        if(option->m_name == name){
            existOption = true;
            optionOn->m_shortName = option->m_shortName;
            break;
        }
    }
    if(!existOption){
        throw ICmdException("OptionOn value do not rely on any Option, the Option do not exist. "
                            + position);
    }
    if(optionOn->m_postMethod.isValid()){
        checkHandleMethod(optionOn->m_postMethod);
    }
    if(optionOn->m_preMethod.isValid()){
        checkHandleMethod(optionOn->m_preMethod);
    }
}

void ICmdWare::checkArgsMethod()
{
    if(m_args == nullptr){
        return;
    }
    QString position = QString(" [Class]: ").append(m_className).append(" [Args Name]: ").append(m_args->m_name);

    if(!m_args->m_prop.isValid()){
        throw ICmdException("Action Args property is not exist. " + position);
    }

    if(!m_args->m_method.isValid()){
        throw ICmdException("Action Args $set_value_xxx method not valid. " + position);
    }

    if(m_args->m_postMethod.isValid()){
        checkHandleMethod(m_args->m_postMethod);
    }
    if(m_args->m_preMethod.isValid()){
        checkHandleMethod(m_args->m_preMethod);
    }
}

void ICmdWare::checkArgxMethod(ICmdActionArgx *argx)
{
    QString position = QString(" [Class]: ").append(m_className)
            .append(" [argx name]: ").append(argx->m_name)
            .append(" [argx index]: ").append(QString::number(argx->m_index));
    if(!argx->m_method.isValid()){
        throw ICmdException("argx $set_value_xxx method is not valid. " + position);
    }

    if(argx->m_postMethod.isValid()){
        checkHandleMethod(argx->m_postMethod);
    }
    if(argx->m_preMethod.isValid()){
        checkHandleMethod(argx->m_preMethod);
    }
}

void ICmdWare::checkOptionShortNameComflict()
{
    QString position = QString(" [Class]: ").append(m_className);
    QStringList names;
    for(auto option : m_options){
        if(!option->m_shortName.isEmpty()){
            if(names.contains(option->m_shortName)){
                throw ICmdException("Options shortname conflicted. " + QString(" [short name]: ").append(option->m_shortName) + position);
            }
            names.append(option->m_shortName);
        }
    }
}

void ICmdWare::checkHandleMethod(const QMetaMethod &method)
{
    QString position = QString(" [Class]: ").append(m_className);
    if(method.returnType() != QMetaType::Void){
        throw ICmdException("PreHandle or PostHandle function return type must be void" + QString(" [Function Name]: ").append(method.methodSignature()) + position);
    }

    if(method.parameterCount()> 1){
        throw ICmdException("PreHandle or PostHandle function argument count must be one or zero" + QString(" [Function Name]: ").append(method.methodSignature()) + position);
    }

    if(method.parameterCount() == 1){
        auto names = getMethodArguments(method);
        if(names.first() != "ICmdRequest" || names.first() != "ICmdRequest&" ){
            throw ICmdException("PreHandle or PostHandle function arguments type can only be ICmdRequest. " + position);
        }
        throw ICmdException("PreHandle or PostHandle function argument type can only be ICmdRequest." + QString(" [Function Name]: ").append(method.methodSignature()) + position);
    }
}

QStringList ICmdWare::getMethodArguments(const QMetaMethod &method)
{
    QStringList names;
    for(auto name : method.parameterTypes()){
        names.append(name);
    }
    return names;
}

$PackageWebCoreEnd
