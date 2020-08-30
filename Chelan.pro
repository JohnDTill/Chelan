#TODO
# Erase static methods
# Get rid of interpreter visitor
# Figure out typing rules
# Add control flow

QT += core

TARGET = Chelan
TEMPLATE = app

INCLUDEPATH += ../Neb/include \

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        compiler.cpp \
        expr.cpp \
        immutableassign.cpp \
        interpreter.cpp \
        main.cpp \
        matrix.cpp \
        print.cpp \
        rational.cpp \
        read.cpp \
        realvariable.cpp \
        pi.cpp \
        disjunction.cpp \
        conjunction.cpp \
        negation.cpp \
        boolean.cpp \
        scalaraddition.cpp \
        scalarmultiplication.cpp \
        scalarpower.cpp \
        stmt.cpp \
        undefined.cpp \
        equality.cpp \
        less.cpp \
        conditionalvalue.cpp \
        untypedaddition.cpp

HEADERS += \
        compiler.h \
        expr.h \
        exprtype.h \
        immutableassign.h \
        interpreter.h \
        matrix.h \
        print.h \
        rational.h \
        read.h \
        realvariable.h \
        pi.h \
        chelan.h \
        disjunction.h \
        conjunction.h \
        negation.h \
        boolean.h \
        scalaraddition.h \
        scalarmultiplication.h \
        scalarpower.h \
        stmt.h \
        stmttype.h \
        undefined.h \
        equality.h \
        less.h \
        conditionalvalue.h \
        untypedaddition.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/../Neb/lib/ -lNeb

INCLUDEPATH += $$PWD/../Neb
DEPENDPATH += $$PWD/../Neb

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../Neb/lib/Neb.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../Neb/lib/libNeb.a

# copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    # replace slashes in destination path for Windows
    win32:dir ~= s,/,\\,g

    for(file, files) {
        # replace slashes in source path for Windows
        win32:file ~= s,/,\\,g

        QMAKE_PRE_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }

    export(QMAKE_PRE_LINK)
}

unix:!macx: {
    LIBS += -lgmpxx -lgmp
}else:{
    INCLUDEPATH += $$PWD/..

    !contains(QMAKE_TARGET.arch, x86_64) {
        ## Windows x86 (32bit) specific build here
        CONFIG(debug, debug|release) {
            INCLUDEPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Debug
            DEPENDPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Debug
            PRE_TARGETDEPS += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Debug/mpir.lib
            LIBS += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Debug/mpir.lib
            copyToDestDir($$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Debug/mpir.dll, $$OUT_PWD/debug)
        } else {
            INCLUDEPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Release
            DEPENDPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Release
            PRE_TARGETDEPS += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Release/mpir.lib
            LIBS += $$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Release/mpir.lib
            copyToDestDir($$PWD/../mpir/build.vc15/dll_mpir_gc/Win32/Release/mpir.dll, $$OUT_PWD/release)
        }
    } else {
        ## Windows x64 (64bit) specific build
        CONFIG(debug, debug|release) {
            INCLUDEPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Debug
            DEPENDPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Debug
            PRE_TARGETDEPS += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Debug/mpir.lib
            LIBS += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Debug/mpir.lib
            copyToDestDir($$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Debug/mpir.dll, $$OUT_PWD/debug)
        } else {
            INCLUDEPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Release
            DEPENDPATH += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Release
            PRE_TARGETDEPS += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Release/mpir.lib
            LIBS += $$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Release/mpir.lib
            copyToDestDir($$PWD/../mpir/build.vc15/dll_mpir_gc/x64/Release/mpir.dll, $$OUT_PWD/release)
        }
    }
}
