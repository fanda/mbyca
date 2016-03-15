
TEMPLATE = app

TARGET = mbyca
CONFIG += qt \
    thread \
    debug
DEPENDPATH += .
INCLUDEPATH += include/
INCLUDEPATH += stk/include/
LIBS += stk/src/libstk.a \
    -lasound
MOC_DIR = tmp/moc
UI_HEADERS_DIR = include/ui
UI_SOURCES_DIR = src/ui
OBJECTS_DIR = tmp/obj
HEADERS += include/Instruments.h \
    include/CA/Cell.h \
    include/CA/Lattice2D.h \
    include/CA/CellularAutomaton2D.h \
    include/CA/CyclicAutomaton.h \
    include/CA/LifeTypeAutomaton.h \
    include/GridGraphicsView.h \
    include/LifeGraphicsView.h \
    include/CommonGraphicsView.h \
    include/Musify.h \
    include/GlitchMusify.h \
    include/TransMusify.h \
    include/GlitchWindow.h \
    include/TransWindow.h \
    include/GlitchMask.h \
    include/Window.h \
    include/MainWindow.h \
    include/SizeDialog.h \
    include/ConfigDialog.h
SOURCES += src/main.cpp \
    src/GridGraphicsView.cpp \
    src/LifeGraphicsView.cpp \
    src/CommonGraphicsView.cpp \
    src/Musify.cpp \
    src/MainWindow.cpp \
    src/GlitchMask.cpp \
    src/TransWindow.cpp \
    src/GlitchWindow.cpp
FORMS += uis/TransWindow.ui \
    uis/GlitchWindow.ui \
    uis/MainWindow.ui \
    uis/SizeDialog.ui \
    uis/ConfigDialog.ui
