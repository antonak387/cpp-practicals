QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arc.cpp \
    circle.cpp \
    color.cpp \
    d_table.cpp \
    ellipse.cpp \
    m_brush.cpp \
    m_pen.cpp \
    main.cpp \
    mainwindow.cpp \
    my_widget.cpp \
    pixel.cpp \
    polygon.cpp \
    polyline.cpp \
    rectangle.cpp \
    tochka.cpp \
    line.cpp

HEADERS += \
    arc.h \
    circle.h \
    color.h \
    d_table.h \
    ellipse.h \
    m_brush.h \
    m_pen.h \
    mainwindow.h \
    my_widget.h \
    pixel.h \
    polygon.h \
    polyline.h \
    rectangle.h \
    tochka.h \
    line.h

FORMS += \
    d_table.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
