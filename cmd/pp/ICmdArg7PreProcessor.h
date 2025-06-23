#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg7Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 7)

#define $CmdArg7(TYPE, NAME)    \
    $CmdArg7Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG7_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg7PreHandle$$$ ## name)

#define PP_CMD_ARG7_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg7PreHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG7_PRE_HANDLE(name), PP_CMD_ARG7_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg7PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG7_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg7PreHandle_(N) $CmdArg7PreHandle_##N
#define $CmdArg7PreHandle_EVAL(N) $CmdArg7PreHandle_(N)
#define $CmdArg7PreHandle(...) PP_EXPAND( $CmdArg7PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define PP_CMD_ARG7_POST_HANDLE(name)         \
    PP_STRING(ICmdArg7PostHandle$$$ ## name)

#define PP_CMD_ARG7_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg7PostHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG7_POST_HANDLE(name), PP_CMD_ARG7_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg7PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG7_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg7PostHandle_(N) $CmdArg7PostHandle_##N
#define $CmdArg7PostHandle_EVAL(N) $CmdArg7PostHandle_(N)
#define $CmdArg7PostHandle(...) PP_EXPAND( $CmdArg7PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $CmdArg7Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 7), #NAME)

#define $CmdArg7Memo(Memo)    \
    Q_CLASSINFO(PP_STRING( ICmdArg7Memo$$$ ), Memo)
