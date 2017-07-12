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
    src/View/imagewidget.cpp \
    src/ViewModel/Commands/newcanvascommand.cpp \
    src/ViewModel/Commands/addellipsecommand.cpp \
    src/Common/DataStructure.cpp \
    src/ViewModel/Commands/redocommand.cpp \
    src/ViewModel/Commands/undocommand.cpp \
    src/View/statemanager.cpp \
    src/View/States/statecommonaction.cpp

HEADERS += \
    src/Common/BaseCommand.h \
    src/Common/Observable.h \
    src/Common/Observer.h \
    src/Common/Params.h \
    src/ViewModel/Commands/AddLineCommand.h \
    src/ViewModel/ViewModel.h \
    src/View/mainwindow.h \
    src/Model/Layouts.h\
    src/Model/Model.h \
    src/Constants.h \
    src/View/imagewidget.h \
    src/Common/DataStructure.h \
    src/ViewModel/Commands/newcanvascommand.h \
    src/ViewModel/Commands/addellipsecommand.h \
    src/ViewModel/Commands/penupdatecommand.h \
    src/ViewModel/Commands/AddRectCommand.h \
    src/ViewModel/Commands/changedselectedcommand.h \
    src/ViewModel/Commands/brushupdatecommand.h \
    src/ViewModel/Commands/newprojectcommand.h \
    src/ViewModel/Commands/saveprojectcommand.h \
    src/ViewModel/Commands/loadprojectcommand.h \
    src/ViewModel/Commands/addpiccommand.h \
    src/ViewModel/Commands/redocommand.h \
    src/ViewModel/Commands/undocommand.h \
    src/ViewModel/Commands/layouttransformcommand.h \
    src/ViewModel/Commands/layouttransformnotifycommand.h \
    src/ViewModel/Commands/deletelayoutcommand.h \
    src/ViewModel/Commands/pixmapfiltercommand.h \
    src/ViewModel/Commands/saveaspicturecommand.h \
    src/View/statemanager.h \
    src/View/States/BaseState.h \
    src/View/States/initstate.h \
    src/ViewModel/Commands/layoutorderchangecommand.h \
    src/View/States/drawlineinitstate.h \
    src/View/States/drawlinestate.h \
    src/View/States/drawellipsestate.h \
    src/View/States/moveinitstate.h \
    src/View/States/movestate.h \
    src/View/States/rotateinitstate.h \
    src/View/States/rotatestate.h \
    src/View/States/scaleinitstate.h \
    src/View/States/scalestate.h \
    src/View/States/drawrectstate.h \
    src/View/States/drawrectinitstate.h \
    src/View/States/statecommonaction.h \
    src/View/States/drawellipseinitstate.h \
    src/View/States/drawellipsestate.h \
    src/View/States/drawlineinitstate.h \
    src/View/States/drawlinestate.h \
    src/View/States/drawrectinitstate.h \
    src/View/States/drawrectstate.h \
    src/View/States/initstate.h \
    src/View/States/moveinitstate.h \
    src/View/States/movestate.h \
    src/View/States/rotateinitstate.h \
    src/View/States/rotatestate.h \
    src/View/States/scaleinitstate.h \
    src/View/States/scalestate.h \
    src/ViewModel/Commands/addtextcommand.h

FORMS += \
    src/View/mainwindow.ui

RESOURCES += \
    langs.qrc \
    imgs.qrc
