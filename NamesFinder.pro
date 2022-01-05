QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/ask_for_name_dialog.cpp \
    sources/dictionaries.cpp \
    sources/dictionary_dialog.cpp \
    sources/letter_group_widget.cpp \
    sources/main.cpp \
    sources/main_window.cpp \
    sources/name_converter.cpp \
    sources/names_list.cpp \
    sources/result_file.cpp \
    sources/scoped_elapsed_timer.cpp \
    sources/search_worker.cpp \
    sources/thread.cpp \
    sources/thread_worker.cpp

HEADERS += \
    sources/ask_for_name_dialog.hpp \
    sources/dictionaries.hpp \
    sources/dictionary_dialog.h \
    sources/group_type.h \
    sources/letter_group_widget.h \
    sources/main_window.h \
    sources/name_converter.h \
    sources/names_list.h \
    sources/result_file.h \
    sources/scoped_elapsed_timer.h \
    sources/search_worker.h \
    sources/thread.h \
    sources/thread_worker.h

FORMS += \
    resources/ask_for_name_dialog.ui \
    resources/dictionary_dialog.ui \
    resources/letter_group_widget.ui \
    resources/main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:RC_ICONS += icon.ico
