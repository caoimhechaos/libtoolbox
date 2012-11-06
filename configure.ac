#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libtoolbox], [0.1], [caoimhechaos@protonmail.com])
AC_CONFIG_SRCDIR([expvar.cc])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE
LT_INIT

AC_ARG_WITH([qt-includes], [AC_HELP_STRING([--with-qt-includes=DIR],
	    [Path to the QT headers])], [INCLUDES="$INCLUDES -I${withval}"])
AC_ARG_WITH([qt-libs], [AC_HELP_STRING([--with-qt-libs=DIR],
	    [Path to the QT libraries])],
	    LDFLAGS="${LDFLAGS} -L${withval} -L${withval}"])
AC_SUBST(INCLUDES)
AC_SUBST(LDFLAGS)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL
AC_LANG(C++)

LIBRARY_VERSION=`echo $VERSION | $SED -e's/\./:/g'`
AC_SUBST(LIBRARY_VERSION)

OLDCXXFLAGS="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -std=c++11"
AC_MSG_CHECKING([whether $CXX accepts -std=c++11])
AC_LINK_IFELSE([AC_LANG_CALL([], [main])], [AC_MSG_RESULT(yes)],
	[AC_MSG_RESULT(no); CXXFLAGS="$OLDCXXFLAGS"])
unset OLDCXXFLAGS
CXXFLAGS="${CXXFLAGS}"
AC_SUBST(CXXFLAGS)

# Checks for libraries.
QT_LIBS=""
AC_CHECK_LIB([QtCore], [main],
	     [QT_LIBS="$QT_LIBS -lQtCore"])
AC_CHECK_LIB([QtNetwork], [main],
	     [QT_LIBS="$QT_LIBS -lQtNetwork"])
AC_LIBS="$AC_LIBS $QT_LIBS"
AC_SUBST(QT_LIBS)
AC_SUBST(AC_LIBS)

# Checks for header files.
AC_CHECK_HEADERS([QtCore/QMap QtCore/QString])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
