TEMPLATE = app
CONFIG += console
CONFIG -= qt

#QMAKE_CXXFLAGS += -DDEBUG

SOURCES += main.cpp \
    c23code.cpp \
    testc23code.cpp \
    robustnesschecker.cpp \
    c23codeccs.cpp \
    c23codeccs2.cpp

HEADERS += \
    abstractcode.h \
    c23code.h \
    testc23code.h \
    robustnesschecker.h \
    util.h \
    c23codeccs.h \
    c23codeccs2.h

