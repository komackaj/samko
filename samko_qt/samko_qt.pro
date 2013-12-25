#-------------------------------------------------
#
# Project created by QtCreator 2013-12-08T09:30:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = samko_qt
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    bussinessdelegate.cpp \
    forms/calib2ddialog.cpp \
    widgets/qmeasureview.cpp \
    qtuifactory.cpp \
    forms/tools/ellipsetargetrefinerdialog.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    bussinessdelegate.h \
    forms/calib2ddialog.h \
    widgets/qmeasureview.h \
    qtuifactory.h \
    forms/tools/ellipsetargetrefinerdialog.h \
    utils.h

FORMS    += mainwindow.ui \
    forms/calib2ddialog.ui \
    forms/tools/ellipsetargetrefinerdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/bin/release/ -lsamko
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/bin/debug/ -lsamko
else:unix: LIBS += -L$$PWD/../build/bin/ -lsamko

INCLUDEPATH += $$PWD/../libsamko/include
DEPENDPATH += $$PWD/../libsamko/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/bin/release/samko.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/bin/debug/samko.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build/bin/libsamko.a

win32:INCLUDEPATH += $$OPENCV_INCDIR
else:unix: INCLUDEPATH += /usr/local/include

win32:DEPENDPATH += $$OPENCV_INCDIR
else:unix: DEPENDPATH += /usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$OPENCV_LIBDIR/release/ -lopencv_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OPENCV_LIBDIR/debug/ -lopencv_core
else:unix: LIBS += -L/usr/local/lib/ -lopencv_core

win32:CONFIG(release, debug|release): LIBS += -L$$OPENCV_LIBDIR/release/ -lopencv_imgproc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OPENCV_LIBDIR/debug/ -lopencv_imgproc
else:unix: LIBS += -L/usr/local/lib/ -lopencv_imgproc

win32:CONFIG(release, debug|release): LIBS += -L$$OPENCV_LIBDIR/release/ -lopencv_calib3d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OPENCV_LIBDIR/debug/ -lopencv_calib3d
else:unix: LIBS += -L/usr/local/lib/ -lopencv_calib3d

win32:CONFIG(release, debug|release): LIBS += -L$$OPENCV_LIBDIR/release/ -lopencv_features2d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OPENCV_LIBDIR/debug/ -lopencv_features2d
else:unix: LIBS += -L/usr/local/lib/ -lopencv_features2d

win32:CONFIG(release, debug|release): LIBS += -L$$OPENCV_LIBDIR/release/ -lopencv_highgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OPENCV_LIBDIR/debug/ -lopencv_highgui
else:unix: LIBS += -L/usr/local/lib/ -lopencv_highgui
