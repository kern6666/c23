TEMPLATE = app
CONFIG += console
CONFIG -= qt

#QMAKE_CXXFLAGS += -DDEBUG

SOURCES += src/main.cpp \
    src/c23code.cpp \
    tests/testc23code.cpp \
    src/robustnesschecker.cpp \
    src/c23codeccs.cpp \
    src/c23codeccs2.cpp \
    src/c23codeccs3.cpp \
    src/c23codeccs4.cpp



INCLUDEPATH += src

HEADERS += \
    src/abstractcode.h \
    src/c23code.h \
    tests/testc23code.h \
    src/robustnesschecker.h \
    src/util.h \
    src/c23codeccs.h \
    src/c23codeccs2.h \
    src/c23codeccs3.h \
    src/c23codeccs4.h

