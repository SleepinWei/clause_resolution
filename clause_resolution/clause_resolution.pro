QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clause_transition.cpp \
    clauses_impl.cpp \
    implication.cpp \
    knowledgebase.cpp \
    main.cpp \
    main_.cpp \
    mainwindow.cpp \
    unify.cpp \
    util.cpp

HEADERS += \
    clause.h \
    implication.h \
    info.h \
    knowledgebase.h \
    literal.h \
    mainwindow.h \
    predicate.h \
    unify.h \
    util.h

FORMS += \
    mainwindow.ui

RC_ICONS = idea.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    clause_resolution.pro.user
