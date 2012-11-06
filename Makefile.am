TESTS=			qsingleton_test expvar_test
check_PROGRAMS=		${TESTS}

lib_LTLIBRARIES=	libtoolbox.la

libtoolbox_la_SOURCES=	expvar.cc
libtoolbox_la_LDFLAGS=	-version-info ${LIBRARY_VERSION}

includetoolboxdir=	${includedir}/toolbox
includetoolbox_HEADERS=	expvar.h qsingleton.h

qsingleton_test_SOURCES=qsingleton_test.cc
qsingleton_test_LDADD=	${GTEST_LIBS} ${lib_LTLIBRARIES} ${QT_LIBS}

expvar_test_SOURCES=	expvar_test.cc
expvar_test_LDADD=	${GTEST_LIBS} ${lib_LTLIBRARIES} ${QT_LIBS}
