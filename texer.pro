#-------------------------------------------------
#
# Project created by QtCreator 2019-01-21T13:22:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = texer
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
        mainwindow.cpp \
    paintwidget.cpp \
    textwidget.cpp \
    Tex2img.cpp \
    latexcode.cpp \
    selectionwidget.cpp

HEADERS += \
        mainwindow.h \
    paintwidget.h \
    textwidget.h \
    Tex2img.h \
    latexcode.h \
    selectionwidget.h \
    aero.h

FORMS += \
        mainwindow.ui

CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

PYTHON_FILES.files += \
    Recognize.py \
    Tex2Img.py \
    Tex2Img_offline.py
PYTHON_FILES.path = $$DESTDIR

CONFIG_FILES.files += \
    latex.api \
    RF_model_0.m \
    RF_model_1.m \
    NN_model_0.m \
    NN_model_1.m
CONFIG_FILES.path = $$OUT_PWD

INSTALLS += PYTHON_FILES CONFIG_FILES

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/QScintilla/Qt4Qt5/release/ -lqscintilla2_qt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/QScintilla/Qt4Qt5/debug/ -lqscintilla2_qt5
else:unix: LIBS += -L$$PWD/lib/QScintilla/Qt4Qt5/ -lqscintilla2_qt5

INCLUDEPATH += $$PWD/lib/QScintilla/Qt4Qt5/
DEPENDPATH += $$PWD/lib/QScintilla/Qt4Qt5/
LIBS += -lqscintilla2_qt5

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Users/mxy/AppData/Local/Programs/Python/Python36-32/libs/ -lpython36
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Users/mxy/AppData/Local/Programs/Python/Python36-32/libs/ -lpython36d
else:unix: LIBS += -L$$PWD/../../Users/mxy/AppData/Local/Programs/Python/Python36-32/libs/ -lpython36

PYTHONPATH = $$(HOME)/AppData/Local/Programs/Python/Python36-32/
INCLUDEPATH += $$PYTHONPATH/include
DEPENDPATH += $$PYTHONPATH/include
