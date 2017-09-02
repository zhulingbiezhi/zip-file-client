TEMPLATE =  lib
CONFIG   += plugin
QT       += widgets core gui network

#DEFINES += USE_WEBKIT
#DEFINES += USE_WEBENGINE
DEFINES += USE_CEF

QMAKE_LFLAGS_RELEASE += /SAFESEH:NO /DEBUG
QMAKE_LFLAGS_DEBUG += /SAFESEH:NO

DESTDIR = ../../players/



UI_DIR  = temp/ui
MOC_DIR = temp/moc
RCC_DIR = temp/rcc

INCLUDEPATH += ../../../fileOperator/include ../../include ../../../common/include ./src

LIBS += -L../../../fileOperator/lib

win32:CONFIG(release, debug|release) {
	TARGET = html5Player
	OBJECTS_DIR = temp/release
    LIBS += -lfileOperator
	LIBS += ./lib/release_x86/QCefView.lib
}
else:win32:CONFIG(debug, debug|release) {
	OBJECTS_DIR = temp/debug
	TARGET = html5Playerd
    LIBS += -lfileOperatord
	LIBS += ./lib/debug_x86/QCefView.lib
}

SOURCES += src/TWebViewRender.cpp \
           src/TPlayerManager.cpp \
           src/THtml5Player.cpp \
		   src/TWebView.cpp \
		   src/TTcpTransfer.cpp \
		   src/TZipServer.cpp \
		   src/TContextMenu.cpp \
	   
HEADERS += ../../include/playitem.h \
           src/TWebViewRender.h \
           src/TPlayerManager.h \
           src/THtml5Player.h \
		   src/TWebView.h \
		   src/TTcpTransfer.h \
		   src/TZipServer.h \
		   src/TContextMenu.h \
		   
contains(DEFINES,USE_WEBKIT){
		QT += webkitwidgets
	
		SOURCES += src/webkit/TWebKitView.cpp \				   
				   src/webkit/TWebMediaPlugin.cpp \
				   
		HEADERS += src/webkit/TWebKitView.h \				  
				   src/webkit/TWebMediaPlugin.h \
				   
		INCLUDEPATH += src/webkit
	}
	
contains(DEFINES,USE_WEBENGINE){
		QT += webenginewidgets
		
		SOURCES += src/webengine/TWebEngineView.cpp \
				   src/webengine/TWebEnginePage.cpp \
				   
		HEADERS += src/webengine/TWebEngineView.h \
				   src/webengine/TWebEnginePage.h \
				   
		INCLUDEPATH += src/webengine
	}				

contains(DEFINES,USE_CEF){	
		SOURCES += src/cefview/TCefView.cpp \	
				   src/cefview/TCefHandle.cpp \
				   

		HEADERS += src/cefview/TCefView.h \	
				   src/cefview/TCefHandle.h \
				   
		INCLUDEPATH += src/cefview ./inc
	}