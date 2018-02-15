#-------------------------------------------------
#
# Project created by QtCreator 2018-02-07T20:51:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pictogram
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


SOURCES += \
        main.cpp \
        pictogram.cpp \
    ../Histure/histure.cpp \
    ../ToFunction/tofunction.cpp

HEADERS += \
        pictogram.h \
    ../Histure/histure.h \
    ../ToFunction/tofunction.h

FORMS += \
    form.ui
INCLUDEPATH += C:\Users\smert\Documents\opencv-3.4.0\opencv-3.4.0\build\install\include

LIBS += ..\opencvdll\libopencv_core340.dll
LIBS += ..\opencvdll\libopencv_highgui340.dll
LIBS += ..\opencvdll\libopencv_imgcodecs340.dll
LIBS += ..\opencvdll\libopencv_imgproc340.dll
LIBS += ..\opencvdll\libopencv_features2d340.dll
LIBS += ..\opencvdll\libopencv_calib3d340.dll
