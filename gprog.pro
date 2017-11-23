TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS_DEBUG += -g -Werror
QMAKE_CXXFLAGS_DEBUG +=  -g -Werror
QMAKE_LFLAGS_DEBUG += -g -Werror

QMAKE_CFLAGS_RELEASE += -DNDEBUG -O3 -s
QMAKE_CXXFLAGS_RELEASE += -DNDEBUG -O3 -s
QMAKE_LFLAGS_RELEASE += -DNDEBUG -O3 -s

SOURCES += \
    src/main.cpp \
    src/network.cpp \
    src/networkstate.cpp \
    src/nodes/state.cpp \
    src/nodefactory.cpp

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
    src/nodes/not.hpp \
    src/nodes/splitter.hpp \
    src/nodes/stdin.hpp \
    src/nodes/and.hpp \
    src/nodes/or.hpp \
    src/nodes/xor.hpp \
    src/nodefactory.hpp \
    src/nodes/capturer.hpp

