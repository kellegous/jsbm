#!/bin/sh

if [ ! -d v8 ]; then
  svn co http://v8.googlecode.com/svn/trunk v8
  cd v8
  scons mode=release library=static snapshot=on
fi
