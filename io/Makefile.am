lib_LTLIBRARIES=	libtoolbox_io.la

libtoolbox_io_la_SOURCES=	QFileZeroCopyInputStream.cc
libtoolbox_io_la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libtoolbox_io_la_LIBADD=	${QT_LIBS} ${PROTO_LIBS} ${Z_LIBS}

includetoolboxdir=	${includedir}/toolbox/io
includetoolbox_HEADERS=	QFileZeroCopyInputStream.h
