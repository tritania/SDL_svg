#! /bin/sh

touch NEWS README AUTHORS ChangeLog
aclocal \
&& automake --add-missing \
&& autoconf
