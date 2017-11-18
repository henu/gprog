TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/network.cpp \
    src/networkstate.cpp \
    src/nodes/state.cpp

HEADERS += \
    src/types.hpp \
    src/json.hpp \
    src/network.hpp \
    src/nodes/node.hpp \
    src/nodes/constant.hpp \
    src/value.hpp \
    src/sharedptr.hpp \
    src/refcounted.hpp \
    src/nodes/stdout.hpp \
    src/networkstate.hpp \
    src/nodes/state.hpp \
    src/nodes/delay.hpp \
    src/nodes/conditional_forward.hpp \
    src/utils.hpp \
    src/nodes/is_value.hpp \
    src/nodes/conditional_constant.hpp \
    src/nodes/not.hpp

