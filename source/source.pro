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
#DEFINES += YAWYSIWYGEE_TEST
CONFIG += c++11
CONFIG += staticlib
TARGET = Chelan

CONFIG(debug, debug|release) {
    DESTDIR = $$shell_path($$_PRO_FILE_PWD_)/../lib/debug
} else {
    DESTDIR = $$shell_path($$_PRO_FILE_PWD_)/../lib/release
}

SOURCES += \
        boolean.cpp \
        conditionalvalue.cpp \
        conjunction.cpp \
        disjunction.cpp \
        equality.cpp \
        expr.cpp \
        less.cpp \
        matrixaddition.cpp \
        matrixenumeration.cpp \
        matrixmultiplication.cpp \
        matrixnumeric.cpp \
        negation.cpp \
        pi.cpp \
        rational.cpp \
        read.cpp \
        realvariable.cpp \
        scalaraddition.cpp \
        scalarmultiplication.cpp \
        scalarpower.cpp \
        undefined.cpp

HEADERS += \
        boolean.h \
        chelan.h \
        conditionalvalue.h \
        conjunction.h \
        disjunction.h \
        equality.h \
        expr.h \
        exprtype.h \
        less.h \
        matrixaddition.h \
        matrixenumeration.h \
        matrixmultiplication.h \
        matrixnumeric.h \
        negation.h \
        pi.h \
        rational.h \
        read.h \
        realvariable.h \
        scalaraddition.h \
        scalarmultiplication.h \
        scalarpower.h \
        undefined.h

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

copyToDestDir($$PWD/"boolean.h", $$PWD/../include)
copyToDestDir($$PWD/"chelan.h", $$PWD/../include)
copyToDestDir($$PWD/"conditionalvalue.h", $$PWD/../include)
copyToDestDir($$PWD/"conjunction.h", $$PWD/../include)
copyToDestDir($$PWD/"disjunction.h", $$PWD/../include)
copyToDestDir($$PWD/"equality.h", $$PWD/../include)
copyToDestDir($$PWD/"expr.h", $$PWD/../include)
copyToDestDir($$PWD/"exprtype.h", $$PWD/../include)
copyToDestDir($$PWD/"less.h", $$PWD/../include)
copyToDestDir($$PWD/"matrixaddition.h", $$PWD/../include)
copyToDestDir($$PWD/"matrixenumeration.h", $$PWD/../include)
copyToDestDir($$PWD/"matrixmultiplication.h", $$PWD/../include)
copyToDestDir($$PWD/"matrixnumeric.h", $$PWD/../include)
copyToDestDir($$PWD/"negation.h", $$PWD/../include)
copyToDestDir($$PWD/"pi.h", $$PWD/../include)
copyToDestDir($$PWD/"rational.h", $$PWD/../include)
copyToDestDir($$PWD/"read.h", $$PWD/../include)
copyToDestDir($$PWD/"realvariable.h", $$PWD/../include)
copyToDestDir($$PWD/"scalaraddition.h", $$PWD/../include)
copyToDestDir($$PWD/"scalarmultiplication.h", $$PWD/../include)
copyToDestDir($$PWD/"scalarpower.h", $$PWD/../include)
copyToDestDir($$PWD/"undefined.h", $$PWD/../include)

copyToDestDir($$PWD/"undefined.h", $$PWD/../include)
