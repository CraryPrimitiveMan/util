#!/bin/bash
SRC_DIR="`pwd`/src"
TEST_DIR="$SRC_DIR/tests/"

cd $SRC_DIR

make test

for file in `find $TEST_DIR -name "*.diff" 2>/dev/null`
do
	grep "\-\-XFAIL--" ${file/%diff/phpt} >/dev/null 2>&1
	if [ $? -gt 0 ]
	then
		FAILS[${#FAILS[@]}]="$file"
	fi
done

if [ ${#FAILS[@]} -gt 0 ]
then
	for fail in "${FAILS[@]}"
	do
		sh -xc "cat $fail"
	done
	exit 1
else
	exit 0
fi
