#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "cmd/pp/ICmdArgXPreProcessor.h"

#define $CmdArg9Declare(TYPE, NAME) \
    PP_CMD_ARG_X_DECLARE(TYPE, NAME, 9)

#define $CmdArg9(TYPE, NAME)    \
    $CmdArg9Declare(TYPE, NAME) \
    TYPE NAME {};

#define PP_CMD_ARG9_PRE_HANDLE(name)         \
    PP_STRING(ICmdArg9PreHandle$$$ ## name)

#define PP_CMD_ARG9_PRE_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PreHandle)

#define $CmdArg9PreHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG9_PRE_HANDLE(name), PP_CMD_ARG9_PRE_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg9PreHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG9_PRE_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg9PreHandle_(N) $CmdArg9PreHandle_##N
#define $CmdArg9PreHandle_EVAL(N) $CmdArg9PreHandle_(N)
#define $CmdArg9PreHandle(...) PP_EXPAND( $CmdArg9PreHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define PP_CMD_ARG9_POST_HANDLE(name)         \
    PP_STRING(ICmdArg9PostHandle$$$ ## name)

#define PP_CMD_ARG9_POST_HANDLE_DEFAULT_FUNCTION(name)    \
    PP_STRING(name ## _PostHandle)

#define $CmdArg9PostHandle_1(NAME)   \
    Q_CLASSINFO(PP_CMD_ARG9_POST_HANDLE(name), PP_CMD_ARG9_POST_HANDLE_DEFAULT_FUNCTION( name ) )    \
    Q_INVOKABLE

#define $CmdArg9PostHandle_2(NAME, func)    \
    Q_CLASSINFO(PP_CMD_ARG9_POST_HANDLE(name), #func )    \
    Q_INVOKABLE

#define $CmdArg9PostHandle_(N) $CmdArg9PostHandle_##N
#define $CmdArg9PostHandle_EVAL(N) $CmdArg9PostHandle_(N)
#define $CmdArg9PostHandle(...) PP_EXPAND( $CmdArg9PostHandle_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $CmdArg9Nullable(NAME)  \
    Q_CLASSINFO(PP_CMD_ARG_X_NULLABLE(NAME, 9), #NAME)


#define $CmdArg9Memo(Memo)    \
    Q_CLASSINFO(PP_STRING( ICmdArg9Memo$$$ ), Memo)
