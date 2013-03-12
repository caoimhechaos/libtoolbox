TESTS=			QUrlFileWatcher_test
check_PROGRAMS=		${TESTS}
lib_LTLIBRARIES=	libtoolbox_io.la

libtoolbox_io_la_SOURCES=	QFileZeroCopyInputStream.cc QUrlFileWatcher.cc
libtoolbox_io_la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libtoolbox_io_la_LIBADD=	${QT_LIBS} ${PROTO_LIBS} ${Z_LIBS} -lglog

QUrlFileWatcher_test_SOURCES=	QUrlFileWatcher_test.cc
QUrlFileWatcher_test_LDADD=	${GTEST_LIBS} ${lib_LTLIBRARIES} ${QT_LIBS} -lglog

includetoolboxdir=	${includedir}/toolbox/io
includetoolbox_HEADERS=	QFileZeroCopyInputStream.h QUrlFileWatcher.h

CLEANFILES=		QUrlFileWatcher.moc

QUrlFileWatcher.lo: QUrlFileWatcher.moc

.cc.moc:
	${QT_MOC_PATH} $< -o $@
