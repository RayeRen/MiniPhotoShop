#-------------------------------------------------
#
# Project created by QtCreator 2017-07-07T10:35:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniPhotoShop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/Model/Model.cpp \
    src/ViewModel/Commands/AddLineCommand.cpp \
    src/ViewModel/ViewModel.cpp \
    src/View/mainwindow.cpp\
    src/main.cpp \

HEADERS += \
    src/Common/BaseCommand.h \
    src/Common/Observable.h \
    src/Common/Observer.h \
    src/Common/Params.h \
    src/ViewModel/Commands/AddLineCommand.h \
    src/ViewModel/ViewModel.h \
    src/View/mainwindow.h \
    src/Model/DataStructure.h \
    src/Model/Layouts.h\
    src/Model/Model.h \
    src/Constants.h \

FORMS += \
    src/View/mainwindow.ui
