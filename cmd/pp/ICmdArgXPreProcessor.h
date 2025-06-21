#pragma once

#include "core/util/IPreProcessorUtil.h"

// $CmdArgX
#define PP_CMD_ARG_X_MAPPING(NAME, INDEX) \
    PP_STRING( ICmdArgXMapping$$$ ## INDEX ## $$$ ## NAME)

#define PP_CMD_ARG_X_DECLARE(TYPE, NAME, INDEX)  \
    Q_CLASSINFO( PP_CMD_ARG_X_MAPPING(NAME, INDEX), #NAME)  \
    Q_PROPERTY(TYPE NAME MEMBER NAME)           \
    Q_INVOKABLE void $set_value_ ## NAME (const QStringList& raws){ \
        detail::setValue< TYPE > (NAME, raws);      \
    }

#define PP_CMD_ARG_X_NULLABLE(NAME, INDEX)  \
    PP_STRING( ICmdArgXNullable$$$ ## NAME ## $$$ # INDEX )
