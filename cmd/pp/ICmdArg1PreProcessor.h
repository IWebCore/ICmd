#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg1Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 1)

#define $CmdArg1(TYPE, NAME)    \
    $CmdArg1Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG1_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg1PreHandle$$$ ## name)

#define PP_CMD_ARG1_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg1PreHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG1_PRE_HANDLE(name), PP_CMD_ARG1_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg1PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG1_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg1PreHandle_(N) $CmdArg1PreHandle_##N
#define $CmdArg1PreHandle_EVAL(N) $CmdArg1PreHandle_(N)
#define $CmdArg1PreHandle(...) PP_EXPAND( $CmdArg1PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define PP_CMD_ARG1_POST_HANDLE(name)         \
    PP_STRING(ICmdArg1PostHandle$$$ ## name)

#define PP_CMD_ARG1_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg1PostHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG1_POST_HANDLE(name), PP_CMD_ARG1_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg1PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG1_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg1PostHandle_(N) $CmdArg1PostHandle_##N
#define $CmdArg1PostHandle_EVAL(N) $CmdArg1PostHandle_(N)
#define $CmdArg1PostHandle(...) PP_EXPAND( $CmdArg1PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $CmdArg1Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 1), #NAME)
