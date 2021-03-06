#############################################################################
# Makefile for building: mbyca
# Generated by qmake (2.01a) (Qt 4.6.2) on: st 5 18 08:33:06 2011
# Project:  mbyca.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile mbyca.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -Iinclude -Istk/include -Itmp/moc -Iinclude/ui
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib stk/src/libstk.a -lasound -lpthread -lQtGui -lQtCore 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = tmp/obj/

####### Files

SOURCES       = src/main.cpp \
		src/GridGraphicsView.cpp \
		src/LifeGraphicsView.cpp \
		src/CommonGraphicsView.cpp \
		src/Musify.cpp \
		src/MainWindow.cpp \
		src/GlitchMask.cpp \
		src/TransWindow.cpp \
		src/GlitchWindow.cpp tmp/moc/moc_CellularAutomaton2D.cpp \
		tmp/moc/moc_CyclicAutomaton.cpp \
		tmp/moc/moc_LifeTypeAutomaton.cpp \
		tmp/moc/moc_GridGraphicsView.cpp \
		tmp/moc/moc_LifeGraphicsView.cpp \
		tmp/moc/moc_CommonGraphicsView.cpp \
		tmp/moc/moc_Musify.cpp \
		tmp/moc/moc_GlitchMusify.cpp \
		tmp/moc/moc_TransMusify.cpp \
		tmp/moc/moc_GlitchWindow.cpp \
		tmp/moc/moc_TransWindow.cpp \
		tmp/moc/moc_GlitchMask.cpp \
		tmp/moc/moc_Window.cpp \
		tmp/moc/moc_MainWindow.cpp \
		tmp/moc/moc_SizeDialog.cpp \
		tmp/moc/moc_ConfigDialog.cpp
OBJECTS       = tmp/obj/main.o \
		tmp/obj/GridGraphicsView.o \
		tmp/obj/LifeGraphicsView.o \
		tmp/obj/CommonGraphicsView.o \
		tmp/obj/Musify.o \
		tmp/obj/MainWindow.o \
		tmp/obj/GlitchMask.o \
		tmp/obj/TransWindow.o \
		tmp/obj/GlitchWindow.o \
		tmp/obj/moc_CellularAutomaton2D.o \
		tmp/obj/moc_CyclicAutomaton.o \
		tmp/obj/moc_LifeTypeAutomaton.o \
		tmp/obj/moc_GridGraphicsView.o \
		tmp/obj/moc_LifeGraphicsView.o \
		tmp/obj/moc_CommonGraphicsView.o \
		tmp/obj/moc_Musify.o \
		tmp/obj/moc_GlitchMusify.o \
		tmp/obj/moc_TransMusify.o \
		tmp/obj/moc_GlitchWindow.o \
		tmp/obj/moc_TransWindow.o \
		tmp/obj/moc_GlitchMask.o \
		tmp/obj/moc_Window.o \
		tmp/obj/moc_MainWindow.o \
		tmp/obj/moc_SizeDialog.o \
		tmp/obj/moc_ConfigDialog.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		mbyca.pro
QMAKE_TARGET  = mbyca
DESTDIR       = 
TARGET        = mbyca

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): include/ui/ui_TransWindow.h include/ui/ui_GlitchWindow.h include/ui/ui_MainWindow.h include/ui/ui_SizeDialog.h include/ui/ui_ConfigDialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: mbyca.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile mbyca.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile mbyca.pro

dist: 
	@$(CHK_DIR_EXISTS) tmp/obj/mbyca1.0.0 || $(MKDIR) tmp/obj/mbyca1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) tmp/obj/mbyca1.0.0/ && $(COPY_FILE) --parents include/Instruments.h include/CA/Cell.h include/CA/Lattice2D.h include/CA/CellularAutomaton2D.h include/CA/CyclicAutomaton.h include/CA/LifeTypeAutomaton.h include/GridGraphicsView.h include/LifeGraphicsView.h include/CommonGraphicsView.h include/Musify.h include/GlitchMusify.h include/TransMusify.h include/GlitchWindow.h include/TransWindow.h include/GlitchMask.h include/Window.h include/MainWindow.h include/SizeDialog.h include/ConfigDialog.h tmp/obj/mbyca1.0.0/ && $(COPY_FILE) --parents src/main.cpp src/GridGraphicsView.cpp src/LifeGraphicsView.cpp src/CommonGraphicsView.cpp src/Musify.cpp src/MainWindow.cpp src/GlitchMask.cpp src/TransWindow.cpp src/GlitchWindow.cpp tmp/obj/mbyca1.0.0/ && $(COPY_FILE) --parents uis/TransWindow.ui uis/GlitchWindow.ui uis/MainWindow.ui uis/SizeDialog.ui uis/ConfigDialog.ui tmp/obj/mbyca1.0.0/ && (cd `dirname tmp/obj/mbyca1.0.0` && $(TAR) mbyca1.0.0.tar mbyca1.0.0 && $(COMPRESS) mbyca1.0.0.tar) && $(MOVE) `dirname tmp/obj/mbyca1.0.0`/mbyca1.0.0.tar.gz . && $(DEL_FILE) -r tmp/obj/mbyca1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: tmp/moc/moc_CellularAutomaton2D.cpp tmp/moc/moc_CyclicAutomaton.cpp tmp/moc/moc_LifeTypeAutomaton.cpp tmp/moc/moc_GridGraphicsView.cpp tmp/moc/moc_LifeGraphicsView.cpp tmp/moc/moc_CommonGraphicsView.cpp tmp/moc/moc_Musify.cpp tmp/moc/moc_GlitchMusify.cpp tmp/moc/moc_TransMusify.cpp tmp/moc/moc_GlitchWindow.cpp tmp/moc/moc_TransWindow.cpp tmp/moc/moc_GlitchMask.cpp tmp/moc/moc_Window.cpp tmp/moc/moc_MainWindow.cpp tmp/moc/moc_SizeDialog.cpp tmp/moc/moc_ConfigDialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) tmp/moc/moc_CellularAutomaton2D.cpp tmp/moc/moc_CyclicAutomaton.cpp tmp/moc/moc_LifeTypeAutomaton.cpp tmp/moc/moc_GridGraphicsView.cpp tmp/moc/moc_LifeGraphicsView.cpp tmp/moc/moc_CommonGraphicsView.cpp tmp/moc/moc_Musify.cpp tmp/moc/moc_GlitchMusify.cpp tmp/moc/moc_TransMusify.cpp tmp/moc/moc_GlitchWindow.cpp tmp/moc/moc_TransWindow.cpp tmp/moc/moc_GlitchMask.cpp tmp/moc/moc_Window.cpp tmp/moc/moc_MainWindow.cpp tmp/moc/moc_SizeDialog.cpp tmp/moc/moc_ConfigDialog.cpp
tmp/moc/moc_CellularAutomaton2D.cpp: include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/CA/CellularAutomaton2D.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/CA/CellularAutomaton2D.h -o tmp/moc/moc_CellularAutomaton2D.cpp

tmp/moc/moc_CyclicAutomaton.cpp: include/CA/CellularAutomaton2D.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/CA/CyclicAutomaton.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/CA/CyclicAutomaton.h -o tmp/moc/moc_CyclicAutomaton.cpp

tmp/moc/moc_LifeTypeAutomaton.cpp: include/CA/CellularAutomaton2D.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/CA/LifeTypeAutomaton.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/CA/LifeTypeAutomaton.h -o tmp/moc/moc_LifeTypeAutomaton.cpp

tmp/moc/moc_GridGraphicsView.cpp: include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/GridGraphicsView.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/GridGraphicsView.h -o tmp/moc/moc_GridGraphicsView.cpp

tmp/moc/moc_LifeGraphicsView.cpp: include/GridGraphicsView.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/LifeGraphicsView.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/LifeGraphicsView.h -o tmp/moc/moc_LifeGraphicsView.cpp

tmp/moc/moc_CommonGraphicsView.cpp: include/GridGraphicsView.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/CommonGraphicsView.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/CommonGraphicsView.h -o tmp/moc/moc_CommonGraphicsView.cpp

tmp/moc/moc_Musify.cpp: include/Instruments.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/Musify.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/Musify.h -o tmp/moc/moc_Musify.cpp

tmp/moc/moc_GlitchMusify.cpp: include/Musify.h \
		include/Instruments.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/GlitchMask.h \
		include/GlitchMusify.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/GlitchMusify.h -o tmp/moc/moc_GlitchMusify.cpp

tmp/moc/moc_TransMusify.cpp: include/Musify.h \
		include/Instruments.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/TransMusify.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/TransMusify.h -o tmp/moc/moc_TransMusify.cpp

tmp/moc/moc_GlitchWindow.cpp: include/Window.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/ui/ui_GlitchWindow.h \
		include/LifeGraphicsView.h \
		include/GridGraphicsView.h \
		include/GlitchMusify.h \
		include/Musify.h \
		include/Instruments.h \
		include/GlitchMask.h \
		include/CA/LifeTypeAutomaton.h \
		include/CA/CellularAutomaton2D.h \
		include/GlitchWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/GlitchWindow.h -o tmp/moc/moc_GlitchWindow.cpp

tmp/moc/moc_TransWindow.cpp: include/Window.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/ui/ui_TransWindow.h \
		src/CommonGraphicsView.h \
		include/TransMusify.h \
		include/Musify.h \
		include/Instruments.h \
		include/CA/LifeTypeAutomaton.h \
		include/CA/CellularAutomaton2D.h \
		include/CA/CyclicAutomaton.h \
		include/TransWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/TransWindow.h -o tmp/moc/moc_TransWindow.cpp

tmp/moc/moc_GlitchMask.cpp: include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/GlitchMask.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/GlitchMask.h -o tmp/moc/moc_GlitchMask.cpp

tmp/moc/moc_Window.cpp: include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/Window.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/Window.h -o tmp/moc/moc_Window.cpp

tmp/moc/moc_MainWindow.cpp: include/ui/ui_MainWindow.h \
		include/SizeDialog.h \
		include/ui/ui_SizeDialog.h \
		include/ConfigDialog.h \
		include/Window.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/CA/CellularAutomaton2D.h \
		include/ui/ui_ConfigDialog.h \
		include/GlitchWindow.h \
		include/ui/ui_GlitchWindow.h \
		include/LifeGraphicsView.h \
		include/GridGraphicsView.h \
		include/GlitchMusify.h \
		include/Musify.h \
		include/Instruments.h \
		include/GlitchMask.h \
		include/CA/LifeTypeAutomaton.h \
		include/TransWindow.h \
		include/ui/ui_TransWindow.h \
		src/CommonGraphicsView.h \
		include/TransMusify.h \
		include/CA/CyclicAutomaton.h \
		include/MainWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/MainWindow.h -o tmp/moc/moc_MainWindow.cpp

tmp/moc/moc_SizeDialog.cpp: include/ui/ui_SizeDialog.h \
		include/SizeDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/SizeDialog.h -o tmp/moc/moc_SizeDialog.cpp

tmp/moc/moc_ConfigDialog.cpp: include/Window.h \
		include/CA/Lattice2D.h \
		include/CA/Cell.h \
		include/CA/CellularAutomaton2D.h \
		include/ui/ui_ConfigDialog.h \
		include/ConfigDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) include/ConfigDialog.h -o tmp/moc/moc_ConfigDialog.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: include/ui/ui_TransWindow.h include/ui/ui_GlitchWindow.h include/ui/ui_MainWindow.h include/ui/ui_SizeDialog.h include/ui/ui_ConfigDialog.h
compiler_uic_clean:
	-$(DEL_FILE) include/ui/ui_TransWindow.h include/ui/ui_GlitchWindow.h include/ui/ui_MainWindow.h include/ui/ui_SizeDialog.h include/ui/ui_ConfigDialog.h
include/ui/ui_TransWindow.h: uis/TransWindow.ui
	/usr/bin/uic-qt4 uis/TransWindow.ui -o include/ui/ui_TransWindow.h

include/ui/ui_GlitchWindow.h: uis/GlitchWindow.ui
	/usr/bin/uic-qt4 uis/GlitchWindow.ui -o include/ui/ui_GlitchWindow.h

include/ui/ui_MainWindow.h: uis/MainWindow.ui
	/usr/bin/uic-qt4 uis/MainWindow.ui -o include/ui/ui_MainWindow.h

include/ui/ui_SizeDialog.h: uis/SizeDialog.ui
	/usr/bin/uic-qt4 uis/SizeDialog.ui -o include/ui/ui_SizeDialog.h

include/ui/ui_ConfigDialog.h: uis/ConfigDialog.ui
	/usr/bin/uic-qt4 uis/ConfigDialog.ui -o include/ui/ui_ConfigDialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

tmp/obj/main.o: src/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/main.o src/main.cpp

tmp/obj/GridGraphicsView.o: src/GridGraphicsView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/GridGraphicsView.o src/GridGraphicsView.cpp

tmp/obj/LifeGraphicsView.o: src/LifeGraphicsView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/LifeGraphicsView.o src/LifeGraphicsView.cpp

tmp/obj/CommonGraphicsView.o: src/CommonGraphicsView.cpp src/CommonGraphicsView.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/CommonGraphicsView.o src/CommonGraphicsView.cpp

tmp/obj/Musify.o: src/Musify.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/Musify.o src/Musify.cpp

tmp/obj/MainWindow.o: src/MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/MainWindow.o src/MainWindow.cpp

tmp/obj/GlitchMask.o: src/GlitchMask.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/GlitchMask.o src/GlitchMask.cpp

tmp/obj/TransWindow.o: src/TransWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/TransWindow.o src/TransWindow.cpp

tmp/obj/GlitchWindow.o: src/GlitchWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/GlitchWindow.o src/GlitchWindow.cpp

tmp/obj/moc_CellularAutomaton2D.o: tmp/moc/moc_CellularAutomaton2D.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_CellularAutomaton2D.o tmp/moc/moc_CellularAutomaton2D.cpp

tmp/obj/moc_CyclicAutomaton.o: tmp/moc/moc_CyclicAutomaton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_CyclicAutomaton.o tmp/moc/moc_CyclicAutomaton.cpp

tmp/obj/moc_LifeTypeAutomaton.o: tmp/moc/moc_LifeTypeAutomaton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_LifeTypeAutomaton.o tmp/moc/moc_LifeTypeAutomaton.cpp

tmp/obj/moc_GridGraphicsView.o: tmp/moc/moc_GridGraphicsView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_GridGraphicsView.o tmp/moc/moc_GridGraphicsView.cpp

tmp/obj/moc_LifeGraphicsView.o: tmp/moc/moc_LifeGraphicsView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_LifeGraphicsView.o tmp/moc/moc_LifeGraphicsView.cpp

tmp/obj/moc_CommonGraphicsView.o: tmp/moc/moc_CommonGraphicsView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_CommonGraphicsView.o tmp/moc/moc_CommonGraphicsView.cpp

tmp/obj/moc_Musify.o: tmp/moc/moc_Musify.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_Musify.o tmp/moc/moc_Musify.cpp

tmp/obj/moc_GlitchMusify.o: tmp/moc/moc_GlitchMusify.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_GlitchMusify.o tmp/moc/moc_GlitchMusify.cpp

tmp/obj/moc_TransMusify.o: tmp/moc/moc_TransMusify.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_TransMusify.o tmp/moc/moc_TransMusify.cpp

tmp/obj/moc_GlitchWindow.o: tmp/moc/moc_GlitchWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_GlitchWindow.o tmp/moc/moc_GlitchWindow.cpp

tmp/obj/moc_TransWindow.o: tmp/moc/moc_TransWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_TransWindow.o tmp/moc/moc_TransWindow.cpp

tmp/obj/moc_GlitchMask.o: tmp/moc/moc_GlitchMask.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_GlitchMask.o tmp/moc/moc_GlitchMask.cpp

tmp/obj/moc_Window.o: tmp/moc/moc_Window.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_Window.o tmp/moc/moc_Window.cpp

tmp/obj/moc_MainWindow.o: tmp/moc/moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_MainWindow.o tmp/moc/moc_MainWindow.cpp

tmp/obj/moc_SizeDialog.o: tmp/moc/moc_SizeDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_SizeDialog.o tmp/moc/moc_SizeDialog.cpp

tmp/obj/moc_ConfigDialog.o: tmp/moc/moc_ConfigDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/obj/moc_ConfigDialog.o tmp/moc/moc_ConfigDialog.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

