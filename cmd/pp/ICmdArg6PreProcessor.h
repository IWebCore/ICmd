#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg6Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 6)

#define $CmdArg6(TYPE, NAME)    \
    $CmdArg6Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG6_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg6PreHandle$$$ ## name)

#define PP_CMD_ARG6_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg6PreHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG6_PRE_HANDLE(name), PP_CMD_ARG6_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg6PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG6_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg6PreHandle_(N) $CmdArg6PreHandle_##N
#define $CmdArg6PreHandle_EVAL(N) $CmdArg6PreHandle_(N)
#define $CmdArg6PreHandle(...) PP_EXPAND( $CmdArg6PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define PP_CMD_ARG6_POST_HANDLE(name)         \
    PP_STRING(ICmdArg6PostHandle$$$ ## name)

#define PP_CMD_ARG6_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg6PostHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG6_POST_HANDLE(name), PP_CMD_ARG6_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg6PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG6_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg6PostHandle_(N) $CmdArg6PostHandle_##N
#define $CmdArg6PostHandle_EVAL(N) $CmdArg6PostHandle_(N)
#define $CmdArg6PostHandle(...) PP_EXPAND( $CmdArg6PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $CmdArg6Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 6), #NAME)

#define $CmdArg6Memo(Memo)    \
    Q_CLASSINFO(PP_STRING( ICmdArg6Memo$$$ ), Memo)
