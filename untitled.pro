#-------------------------------------------------
#
# Project created by QtCreator 2023-05-16T14:16:52
#
#-------------------------------------------------

QT       += core gui  multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    role.cpp \
    gameobject.cpp \
    player.cpp \
    enemy.cpp \
    gamedefine.cpp \
    gamecontrol.cpp \
    medicine.cpp \
    elitist.cpp \
    bullet.cpp \
    player_bullet.cpp \
    barrior.cpp \
    tough_barrior.cpp \
    fragile_barrior.cpp \
    elitist_bullet.cpp \
    sword.cpp \
    form.cpp \
    enhance_page.cpp \
    AButton.cpp \
    gameobjectpool.cpp \
    choose_Icon.cpp \
    exp.cpp

HEADERS += \
        widget.h \
    role.h \
    gameobject.h \
    player.h \
    enemy.h \
    gamedefine.h \
    gamecontrol.h \
    medicine.h \
    elitist.h \
    bullet.h \
    player_bullet.h \
    barrior.h \
    tough_barrior.h \
    fragile_barrior.h \
    elitist_bullet.h \
    sword.h \
    form.h \
    enhance_page.h \
    Abutton.h \
    gameobjectpool.h \
    choose_Icon.h \
    exp.h

FORMS += \
        widget.ui \
    form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
