#pragma once

#include "core/util/IPreProcessorUtil.h"

#define PP_CMD_OPTION_ARGUMENT(NAME)    \
    PP_STRING( ICmdOptionArgument$$$ ## NAME)

#define PP_CMD_OPTION_SHORT_NAME_MAPPING(NAME)    \
    PP_STRING(ICmdOptionShortName$$$ ## NAME)

// $CmdOption
#define $CmdOptionDeclare_2(TYPE, NAME)                                                 \
    Q_CLASSINFO(PP_CMD_OPTION_ARGUMENT(NAME), #NAME)                                    \
    Q_PROPERTY(TYPE NAME MEMBER NAME)                                                   \
    Q_INVOKABLE void $set_value_ ## NAME (const QStringList& raws)  {                   \
        detail::setValue< TYPE >( NAME, raws);                                          \
    }

#define $CmdOptionDeclare_3(TYPE, NAME, SHORT_NAME)                     \
    Q_CLASSINFO(PP_CMD_OPTION_SHORT_NAME_MAPPING( NAME ), #SHORT_NAME)      \
    $CmdOptionDeclare_2(TYPE, NAME)

#define $CmdOptionDeclare_(N) $CmdOptionDeclare_##N
#define $CmdOptionDeclare_EVAL(N) $CmdOptionDeclare_(N)
#define $CmdOptionDeclare(...) PP_EXPAND( $CmdOptionDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $CmdOption_2(TYPE, NAME)                                        \
    $CmdOptionDeclare_2(TYPE, NAME)                                     \
    TYPE NAME {};

#define $CmdOption_3(TYPE, NAME, SHORT_NAME)                            \
    $CmdOptionDeclare_3(TYPE, NAME, SHORT_NAME)                         \
    TYPE NAME {};

#define $CmdOption_(N) $CmdOption_##N
#define $CmdOption_EVAL(N) $CmdOption_(N)
#define $CmdOption(...) PP_EXPAND( $CmdOption_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// option pre handle
#define PP_CMD_PRE_OPTION(name)         \
    PP_STRING(ICmdOptionPreHandle$$$ ## name)

#define PP_CMD_PRE_OPTION_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdOptionPreHandle_1(name) \
    Q_CLASSINFO(PP_CMD_PRE_OPTION(name), PP_CMD_PRE_OPTION_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $$CmdOptionPreHandle_2(name, func)  \
    Q_CLASSINFO(PP_CMD_PRE_OPTION(name), func )    \
    Q_INVOKABLE

#define $CmdOptionPreHandle_(N) $CmdOptionPreHandle_##N
#define $CmdOptionPreHandle_EVAL(N) $CmdOptionPreHandle_(N)
#define $CmdOptionPreHandle(...) PP_EXPAND( $CmdOptionPreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


// option post handle
#define PP_CMD_POST_OPTION(name)         \
    PP_STRING(ICmdOptionPostHandle$$$ ## name)

#define PP_CMD_POST_OPTION_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdOptionPostHandle_1(name) \
    Q_CLASSINFO(PP_CMD_POST_OPTION(name), PP_CMD_POST_OPTION_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdOptionPostHandle_2(name, func) \
    Q_CLASSINFO(PP_CMD_POST_OPTION(name), func)    \
    Q_INVOKABLE

#define $CmdOptionPostHandle_(N) $CmdOptionPostHandle_##N
#define $CmdOptionPostHandle_EVAL(N) $CmdOptionPostHandle_(N)
#define $CmdOptionPostHandle(...) PP_EXPAND( $CmdOptionPostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// option required
#define PP_CMD_OPTION_REQUIRED(name)    \
    PP_STRING(ICmdOptionRequired$$$ ## name)

#define $CmdOptionRequired(name)    \
    Q_CLASSINFO(PP_CMD_OPTION_REQUIRED(name), #name)
