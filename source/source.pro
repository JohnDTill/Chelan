#TODO
# How are errors handled?
# How are functions called?
#
# Real issues with combining S-exprs, matrices, and state

TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11
CONFIG += staticlib
TARGET = Chelan

CONFIG(debug, debug|release) {
    DESTDIR = $$shell_path($$_PRO_FILE_PWD_)/../lib/debug
} else {
    DESTDIR = $$shell_path($$_PRO_FILE_PWD_)/../lib/release
}

SOURCES += \
        expr.cpp \
        expr/absolutevalue.cpp \
        expr/boolean.cpp \
        expr/call.cpp \
        expr/conditionalvalue.cpp \
        expr/conjunction.cpp \
        expr/disjunction.cpp \
        expr/equality.cpp \
        expr/function.cpp \
        expr/inverse.cpp \
        expr/less.cpp \
        expr/matrixaddition.cpp \
        expr/matrixenumeration.cpp \
        expr/matrixmultiplication.cpp \
        expr/matrixnumeric.cpp \
        expr/negation.cpp \
        expr/pi.cpp \
        expr/rational.cpp \
        expr/readglobal.cpp \
        expr/readlocal.cpp \
        expr/readlocalelement.cpp \
        expr/realvariable.cpp \
        expr/scalaraddition.cpp \
        expr/scalarmultiplication.cpp \
        expr/scalarpower.cpp \
        expr/transpose.cpp \
        expr/undefined.cpp \
        runtime.cpp \
        stmt.cpp \
        stmt/assign.cpp \
        stmt/assigncolumn.cpp \
        stmt/assignelement.cpp \
        stmt/block.cpp \
        stmt/declareassign.cpp \
        stmt/if.cpp \
        stmt/print.cpp \
        stmt/return.cpp \
        stmt/while.cpp

HEADERS += \
        chelan.h \
        expr.h \
        expr/absolutevalue.h \
        expr/call.h \
        expr/function.h \
        expr/inverse.h \
        expr/readglobal.h \
        expr/readlocal.h \
        expr/readlocalelement.h \
        expr/transpose.h \
        exprtype.h \
        expr/boolean.h \
        expr/conditionalvalue.h \
        expr/conjunction.h \
        expr/disjunction.h \
        expr/equality.h \
        expr/less.h \
        expr/matrixaddition.h \
        expr/matrixenumeration.h \
        expr/matrixmultiplication.h \
        expr/matrixnumeric.h \
        expr/negation.h \
        expr/pi.h \
        expr/rational.h \
        expr/realvariable.h \
        expr/scalaraddition.h \
        expr/scalarmultiplication.h \
        expr/scalarpower.h \
        expr/undefined.h \
        runtime.h \
        stmt.h \
        stmt/assign.h \
        stmt/assigncolumn.h \
        stmt/assignelement.h \
        stmt/block.h \
        stmt/declareassign.h \
        stmt/if.h \
        stmt/print.h \
        stmt/return.h \
        stmt/while.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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

unix:!macx:{
    LIBS += -lgmpxx -lgmp
}else:{
    INCLUDEPATH += $$PWD/..

    !contains(QMAKE_TARGET.arch, x86_64) {
        ## Windows x86 (32bit) specific build here
        CONFIG(debug, debug|release) {
            INCLUDEPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Debug
            DEPENDPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Debug
            PRE_TARGETDEPS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Debug/mpir.lib
            LIBS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Debug/mpir.lib
            copyToDestDir($$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Debug/mpir.dll, $$OUT_PWD/debug)
        } else {
            INCLUDEPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Release
            DEPENDPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Release
            PRE_TARGETDEPS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Release/mpir.lib
            LIBS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Release/mpir.lib
            copyToDestDir($$PWD/../../mpir/build.vc15/dll_mpir_gc/Win32/Release/mpir.dll, $$OUT_PWD/release)
        }
    } else {
        ## Windows x64 (64bit) specific build
        CONFIG(debug, debug|release) {
            INCLUDEPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Debug
            DEPENDPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Debug
            PRE_TARGETDEPS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Debug/mpir.lib
            LIBS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Debug/mpir.lib
            copyToDestDir($$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Debug/mpir.dll, $$OUT_PWD/debug)
        } else {
            INCLUDEPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Release
            DEPENDPATH += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Release
            PRE_TARGETDEPS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Release/mpir.lib
            LIBS += $$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Release/mpir.lib
            copyToDestDir($$PWD/../../mpir/build.vc15/dll_mpir_gc/x64/Release/mpir.dll, $$OUT_PWD/release)
        }
    }
}

copyToDestDir($$PWD/"expr/absolutevalue.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/boolean.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/call.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/conditionalvalue.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/conjunction.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/disjunction.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/equality.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/function.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/inverse.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/less.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixaddition.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixenumeration.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixmultiplication.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixnumeric.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/negation.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/pi.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/rational.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/readglobal.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/readlocal.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/readlocalelement.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/realvariable.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/scalaraddition.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/scalarmultiplication.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/scalarpower.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/transpose.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/undefined.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"stmt/assign.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/assigncolumn.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/assignelement.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/block.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/declareassign.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/if.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/print.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/return.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"stmt/while.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"chelan.h", $$PWD/../include)
copyToDestDir($$PWD/"expr.h", $$PWD/../include)
copyToDestDir($$PWD/"exprtype.h", $$PWD/../include)
copyToDestDir($$PWD/"runtime.h", $$PWD/../include)
copyToDestDir($$PWD/"stmt.h", $$PWD/../include)
