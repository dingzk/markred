dnl $Id$
dnl config.m4 for extension markred

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(markred, for markred support,
dnl Make sure that the comment is aligned:
dnl [  --with-markred             Include markred support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(markred, whether to enable markred support,
dnl Make sure that the comment is aligned:
[  --enable-markred           Enable markred support])

if test "$PHP_MARKRED" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-markred -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/markred.h"  # you most likely want to change this
  dnl if test -r $PHP_MARKRED/$SEARCH_FOR; then # path given as parameter
  dnl   MARKRED_DIR=$PHP_MARKRED
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for markred files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MARKRED_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MARKRED_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the markred distribution])
  dnl fi

  dnl # --with-markred -> add include path
  dnl PHP_ADD_INCLUDE($MARKRED_DIR/include)

  dnl # --with-markred -> check for lib and symbol presence
  dnl LIBNAME=markred # you may want to change this
  dnl LIBSYMBOL=markred # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MARKRED_DIR/$PHP_LIBDIR, MARKRED_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MARKREDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong markred lib version or lib not found])
  dnl ],[
  dnl   -L$MARKRED_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MARKRED_SHARED_LIBADD)

  PHP_NEW_EXTENSION(markred, markred.c src/trie.c src/token.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi
if test -z "$PHP_DEBUG"; then
    AC_ARG_ENABLE(debug,  [ --enable-debug      compile with debugging symbols],[ PHP_DEBUG=$enableval  ],[ PHP_DEBUG=no  ])
fi
