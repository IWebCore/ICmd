#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg5Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 5)

#define $CmdArg5(TYPE, NAME)    \
    $CmdArg5Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG5_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg5PreHandle$$$ ## name)

#define PP_CMD_ARG5_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg5PreHandle_5(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG5_PRE_HANDLE(name), PP_CMD_ARG5_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg5PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG5_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg5PreHandle_(N) $CmdArg5PreHandle_##N
#define $CmdArg5PreHandle_EVAL(N) $CmdArg5PreHandle_(N)
#define $CmdArg5PreHandle(...) PP_EXPAND( $CmdArg5PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define PP_CMD_ARG5_POST_HANDLE(name)         \
    PP_STRING(ICmdArg5PostHandle$$$ ## name)

#define PP_CMD_ARG5_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg5PostHandle_5(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG5_POST_HANDLE(name), PP_CMD_ARG5_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg5PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG5_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg5PostHandle_(N) $CmdArg5PostHandle_##N
#define $CmdArg5PostHandle_EVAL(N) $CmdArg5PostHandle_(N)
#define $CmdArg5PostHandle(...) PP_EXPAND( $CmdArg5PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $CmdArg5Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 5), #NAME)
