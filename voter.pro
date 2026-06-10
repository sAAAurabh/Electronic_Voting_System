QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    candidate.cpp \
    candidate_home.cpp \
    candidate_login_window.cpp \
    candidate_register_window.cpp \
    main.cpp \
    voter.cpp \
    voter_login_window.cpp \
    voter_register_window.cpp \
    widget.cpp

HEADERS += \
    admin.h \
    candidate.h \
    candidate_home.h \
    candidate_login_window.h \
    candidate_register_window.h \
    picosh.h \
    voter.h \
    voter_login_window.h \
    voter_register_window.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    candidate \
    manifesto \
    voter
