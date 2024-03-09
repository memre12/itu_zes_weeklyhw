QT       += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Menu.cpp \
    appetizers.cpp \
    desserts.cpp \
    drinks.cpp \
    main.cpp \
    main_courses.cpp \
    mainwindow.cpp \
    menu_rec.cpp \
    menu_titles.cpp \
    overall_calc.cpp \
    readjson.cpp \
    salads.cpp \
    secondpage.cpp \
    show_chosen_menu.cpp \
    starter.cpp

HEADERS += \
    Menu.h \
    appetizers.h \
    desserts.h \
    drinks.h \
    main_courses.h \
    mainwindow.h \
    menu_rec.h \
    menu_titles.h \
    overall_calc.h \
    readjson.h \
    salads.h \
    secondpage.h \
    show_chosen_menu.h \
    starter.h

FORMS += \
    appetizers.ui \
    desserts.ui \
    drinks.ui \
    main_courses.ui \
    mainwindow.ui \
    menu_rec.ui \
    menu_titles.ui \
    salads.ui \
    secondpage.ui \
    show_chosen_menu.ui \
    starter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../gae.png \
    ../../git_repo/itu_zes_weeklyhw/weeklyhw4/menu.json

RESOURCES += \
    ../../ads.qrc \
    ../../asda.qrc \
    ../../pp.qrc \
    ../aaaa.qrc
