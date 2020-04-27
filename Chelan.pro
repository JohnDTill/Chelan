QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chelan
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        node.cpp \
        addition.cpp \
    rational.cpp \
    realvariable.cpp \
    pi.cpp \
    multiplication.cpp \
    power.cpp \
    disjunction.cpp \
    conjunction.cpp \
    negation.cpp \
    boolean.cpp \
    undefined.cpp \
    equality.cpp \
    less.cpp \
    conditionalvalue.cpp

HEADERS += \
        node.h \
        addition.h \
    rational.h \
    realvariable.h \
    nodetype.h \
    pi.h \
    chelan.h \
    multiplication.h \
    power.h \
    disjunction.h \
    conjunction.h \
    negation.h \
    boolean.h \
    undefined.h \
    equality.h \
    less.h \
    conditionalvalue.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -lgmpxx -lgmp
