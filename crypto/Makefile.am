TESTS=			base64_test
check_PROGRAMS=		${TESTS}
lib_LTLIBRARIES=	libtoolbox_crypto.la

libtoolbox_crypto_la_SOURCES=	base64.cc
libtoolbox_crypto_la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libtoolbox_crypto_la_LIBADD=	${SSL_LIBS} -lglog

base64_test_SOURCES=	base64_test.cc
base64_test_LDADD=	${GTEST_LIBS} ${lib_LTLIBRARIES} ${SSL_LIBS}

includetoolboxdir=	${includedir}/toolbox/crypto
includetoolbox_HEADERS=	base64.h
