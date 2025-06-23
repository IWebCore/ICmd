#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg2Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 2)

#define $CmdArg2(TYPE, NAME)    \
    $CmdArg2Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG2_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg2PreHandle$$$ ## name)

#define PP_CMD_ARG2_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg2PreHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG2_PRE_HANDLE(name), PP_CMD_ARG2_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg2PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG2_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg2PreHandle_(N) $CmdArg2PreHandle_##N
#define $CmdArg2PreHandle_EVAL(N) $CmdArg2PreHandle_(N)
#define $CmdArg2PreHandle(...) PP_EXPAND( $CmdArg2PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define PP_CMD_ARG2_POST_HANDLE(name)         \
    PP_STRING(ICmdArg2PostHandle$$$ ## name)

#define PP_CMD_ARG2_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg2PostHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG2_POST_HANDLE(name), PP_CMD_ARG2_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg2PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG2_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg2PostHandle_(N) $CmdArg2PostHandle_##N
#define $CmdArg2PostHandle_EVAL(N) $CmdArg2PostHandle_(N)
#define $CmdArg2PostHandle(...) PP_EXPAND( $CmdArg2PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $CmdArg2Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 2), #NAME)

#define $CmdArg2Memo(Memo)    \
    Q_CLASSINFO(PP_STRING( ICmdArg2Memo$$$ ), Memo)
