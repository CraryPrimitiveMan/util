#!/bin/sh
SRC_DIR="`pwd`/src"
cd $SRC_DIR

phpize && ./configure && make clean && make
