TESTS=			qsingleton_test expvar_test scopedptr_test
check_PROGRAMS=		${TESTS}

lib_LTLIBRARIES=	libtoolbox.la

libtoolbox_la_SOURCES=	expvar.cc refcountedobject.cc
libtoolbox_la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libtoolbox_la_LIBADD=	${QT_LIBS} ${Z_LIBS}

includetoolboxdir=	${includedir}/toolbox
includetoolbox_HEADERS=	expvar.h qsingleton.h refcountedobject.h scopedptr.h

${TESTS}:	LDADD="${GTEST_LIBS} ${lib_LTLIBRARIES} ${QT_LIBS} ${Z_LIBS}"

SUBDIRS=		crypto io
