#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg8Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 8)

#define $CmdArg8(TYPE, NAME)    \
    $CmdArg8Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG8_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg8PreHandle$$$ ## name)

#define PP_CMD_ARG8_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg8PreHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG8_PRE_HANDLE(name), PP_CMD_ARG8_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg8PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG8_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg8PreHandle_(N) $CmdArg8PreHandle_##N
#define $CmdArg8PreHandle_EVAL(N) $CmdArg8PreHandle_(N)
#define $CmdArg8PreHandle(...) PP_EXPAND( $CmdArg8PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// $CmdArgsPostHandle
#define PP_CMD_ARG8_POST_HANDLE(name)         \
    PP_STRING(ICmdArg8PostHandle$$$ ## name)

#define PP_CMD_ARG8_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg8PostHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG8_POST_HANDLE(name), PP_CMD_ARG8_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg8PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG8_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg8PostHandle_(N) $CmdArg8PostHandle_##N
#define $CmdArg8PostHandle_EVAL(N) $CmdArg8PostHandle_(N)
#define $CmdArg8PostHandle(...) PP_EXPAND( $CmdArg8PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $CmdArg8Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 8), #NAME)
