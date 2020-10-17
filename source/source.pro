#TODO
# I think with static analysis added, Chelan becomes much more like earlier prototypes,
# where not everything inherited from the same base. You have numeric expressions,
# boolean expressions, matrix expressions, etc...
#
# You also have your pick of procedural or OO style. Well, there is an output log for
# print statements, and also the ability to report runtime errors.
#
# What if the compiler emitted all possible checks for errors, and the AST eliminated many of those
# checks by partial evaluation? Is that preferable to the AST doing the checks?
# That could make translation from the AST hard.
#
# I kind of like the idea of expressions having an inheritance hierarchy, and statements being procedural.
# If you want S-expressions, you might as well have a hierarchy. Then using procedural for the statements
# will be a nice delineation
#
# You can put the statements in a separate module!
#
# Got to use code gen in the CAS
#
# With at least coarsely typed expressions, you can have much more meaningful methods

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
        expr/boolean.cpp \
        expr/conditionalvalue.cpp \
        expr/conjunction.cpp \
        expr/disjunction.cpp \
        expr/equality.cpp \
        expr/less.cpp \
        expr/matrixaddition.cpp \
        expr/matrixenumeration.cpp \
        expr/matrixmultiplication.cpp \
        expr/matrixnumeric.cpp \
        expr/negation.cpp \
        expr/pi.cpp \
        expr/rational.cpp \
        expr/read.cpp \
        expr/realvariable.cpp \
        expr/scalaraddition.cpp \
        expr/scalarmultiplication.cpp \
        expr/scalarpower.cpp \
        expr/undefined.cpp \
        stmt.cpp \
        stmt/print.cpp

HEADERS += \
        chelan.h \
        expr.h \
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
        expr/read.h \
        expr/realvariable.h \
        expr/scalaraddition.h \
        expr/scalarmultiplication.h \
        expr/scalarpower.h \
        expr/undefined.h \
        stmt.h \
        stmt/print.h

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

copyToDestDir($$PWD/"expr/boolean.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/conditionalvalue.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/conjunction.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/disjunction.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/equality.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/less.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixaddition.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixenumeration.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixmultiplication.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/matrixnumeric.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/negation.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/pi.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/rational.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/read.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/realvariable.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/scalaraddition.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/scalarmultiplication.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/scalarpower.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"expr/undefined.h", $$PWD/../include/expr)
copyToDestDir($$PWD/"stmt/print.h", $$PWD/../include/stmt)
copyToDestDir($$PWD/"chelan.h", $$PWD/../include)
copyToDestDir($$PWD/"expr.h", $$PWD/../include)
copyToDestDir($$PWD/"exprtype.h", $$PWD/../include)
copyToDestDir($$PWD/"stmt.h", $$PWD/../include)
