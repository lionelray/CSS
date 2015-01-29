#-------------------------------------------------
#
# Project created by QtCreator 2014-08-19T14:30:09
# Copyright (c) 2014
# All rights reserved.
# 当前版本 1.2
# 作者：刘龙�?
# 完成日期�?2014�?9�?2�?
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CSS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login/login.cpp \
    login/loginserver.cpp \
    login/logindao.cpp \
    db.cpp \
    createitem/createitem.cpp \
    student/delstu.cpp \
    student/searchstu.cpp \
    student/addstu.cpp \
    guest/changepwd.cpp \
    guest/addgst.cpp \
    guest/guestdao.cpp \
    student/studao.cpp \
    createitem/createitemdao.cpp \
    sign/searchsigndao.cpp \
    sign/signdetail.cpp \
    sign/signdao.cpp \
    sign/stusign.cpp \
    excelengine.cpp

HEADERS  += mainwindow.h \
    login/login.h \
    login/loginserver.h \
    login/logindao.h \
    db.h \
    createitem/createitem.h \
    student/delstu.h \
    student/searchstu.h \
    student/addstu.h \
    guest/changepwd.h \
    guest/addgst.h \
    guest/guestdao.h \
    student/studao.h \
    createitem/createitemdao.h \
    sign/searchsigndao.h \
    sign/signdetail.h \
    sign/signdao.h \
    sign/stusign.h \
    excelengine.h

FORMS    += mainwindow.ui \
    login/login.ui \
    createitem/createitem.ui \
    student/addstu.ui \
    guest/changepwd.ui \
    guest/addgst.ui \
    sign/signdetail.ui \
    sign/stusign.ui

RESOURCES += \
    image/image.qrc
