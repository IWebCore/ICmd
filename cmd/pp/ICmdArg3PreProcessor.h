#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg3Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 3)

#define $CmdArg3(TYPE, NAME)    \
    $CmdArg3Declare(TYPE, NAME) \
    TYPE NAME {};


#define PP_CMD_ARG3_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg3PreHandle$$$ ## name)

#define PP_CMD_ARG3_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg3PreHandle_3(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG3_PRE_HANDLE(name), PP_CMD_ARG3_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg3PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG3_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg3PreHandle_(N) $CmdArg3PreHandle_##N
#define $CmdArg3PreHandle_EVAL(N) $CmdArg3PreHandle_(N)
#define $CmdArg3PreHandle(...) PP_EXPAND( $CmdArg3PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define PP_CMD_ARG3_POST_HANDLE(name)         \
    PP_STRING(ICmdArg3PostHandle$$$ ## name)

#define PP_CMD_ARG3_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg3PostHandle_3(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG3_POST_HANDLE(name), PP_CMD_ARG3_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg3PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG3_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg3PostHandle_(N) $CmdArg3PostHandle_##N
#define $CmdArg3PostHandle_EVAL(N) $CmdArg3PostHandle_(N)
#define $CmdArg3PostHandle(...) PP_EXPAND( $CmdArg3PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $CmdArg3Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 3), #NAME)
