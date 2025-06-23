#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg4Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 4)

#define $CmdArg4(TYPE, NAME)    \
    $CmdArg4Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG4_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg4PreHandle$$$ ## name)

#define PP_CMD_ARG4_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg4PreHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG4_PRE_HANDLE(name), PP_CMD_ARG4_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg4PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG4_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg4PreHandle_(N) $CmdArg4PreHandle_##N
#define $CmdArg4PreHandle_EVAL(N) $CmdArg4PreHandle_(N)
#define $CmdArg4PreHandle(...) PP_EXPAND( $CmdArg4PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define PP_CMD_ARG4_POST_HANDLE(name)         \
    PP_STRING(ICmdArg4PostHandle$$$ ## name)

#define PP_CMD_ARG4_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg4PostHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG4_POST_HANDLE(name), PP_CMD_ARG4_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg4PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG4_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg4PostHandle_(N) $CmdArg4PostHandle_##N
#define $CmdArg4PostHandle_EVAL(N) $CmdArg4PostHandle_(N)
#define $CmdArg4PostHandle(...) PP_EXPAND( $CmdArg4PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $CmdArg4Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 4), #NAME)
