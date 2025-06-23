#pragma once

#include "core/util/IPreProcessorUtil.h"

#define PP_CMD_OPTION_ON(NAME)  \
    PP_STRING( ICmdOptionOn$$$ ## NAME)

#define PP_CMD_OPTION_ON_FIELD( NAME) \
    PP_STRING( NAME ## _ON)

#define $CmdOptionOn_1(Opt) \
    Q_CLASSINFO( PP_CMD_OPTION_ON(Opt), PP_CMD_OPTION_ON_FIELD(Opt))    \
    Q_PROPERTY(bool Opt ## _ON MEMBER Opt ## _ON)   \
    bool  Opt ## _ON {false};

#define $CmdOptionOn_2(Opt, Name)   \
    Q_CLASSINFO( PP_CMD_OPTION_ON(Opt), #Name)    \
    Q_PROPERTY(bool Name MEMBER Name)   \
    bool Name {false};


#define $CmdOptionOn_(N) $CmdOptionOn_##N
#define $CmdOptionOn_EVAL(N) $CmdOptionOn_(N)
#define $CmdOptionOn(...) PP_EXPAND( $CmdOptionOn_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


// option pre handle
#define PP_CMD_PRE_OPTION_ON(name)         \
    PP_STRING(ICmdOptionOnPreHandle$$$ ## name)

#define PP_CMD_PRE_OPTION_ON_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdOptionOnPreHandle_1(name) \
    Q_CLASSINFO(PP_CMD_PRE_OPTION_ON(name), PP_CMD_PRE_OPTION_ON_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $$CmdOptionOnPreHandle_2(name, func)  \
    Q_CLASSINFO(PP_CMD_PRE_OPTION_ON(name), func )    \
    Q_INVOKABLE

#define $CmdOptionOnPreHandle_(N) $CmdOptionOnPreHandle_##N
#define $CmdOptionOnPreHandle_EVAL(N) $CmdOptionOnPreHandle_(N)
#define $CmdOptionOnPreHandle(...) PP_EXPAND( $CmdOptionOnPreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// option post handle
#define PP_CMD_POST_OPTION_ON(name)         \
    PP_STRING(ICmdOptionOnPostHandle$$$ ## name)

#define PP_CMD_POST_OPTION_ON_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdOptionOnPostHandle_1(name) \
    Q_CLASSINFO(PP_CMD_POST_OPTION_ON(name), PP_CMD_POST_OPTION_ON_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdOptionOnPostHandle_2(name, func) \
    Q_CLASSINFO(PP_CMD_POST_OPTION_ON(name), func)    \
    Q_INVOKABLE

#define $CmdOptionOnPostHandle_(N) $CmdOptionOnPostHandle_##N
#define $CmdOptionOnPostHandle_EVAL(N) $CmdOptionOnPostHandle_(N)
#define $CmdOptionOnPostHandle(...) PP_EXPAND( $CmdOptionOnPostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// optionOn required
#define PP_CMD_OPTION_ON_REQUIRED(name)    \
    PP_STRING(ICmdOptionOnRequired$$$ ## name)

#define $CmdOptionOnRequired(name)    \
    Q_CLASSINFO(PP_CMD_OPTION_ON_REQUIRED(name), #name)
