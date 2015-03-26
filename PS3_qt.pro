TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    BMPImage.h \
	color.h \
	scene.h \
	vector3.h \
    triangle.h \
    circle.h \
    pointlight.h \
    directionlight.h

SOURCES += \
    main.cpp \
    BMPImage.cpp \
	color.cpp \
	scene.cpp \
	vector3.cpp \
    triangle.cpp \
    circle.cpp \
    pointlight.cpp \
    directionlight.cpp


