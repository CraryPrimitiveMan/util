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
		echo -e "\n\ndiff file:"
		sh -xc "cat $fail"
		name=$(ls $fail | cut -d. -f1)
		echo -e "\n\nexp file:"
		sh -xc "cat $name.exp"
		echo -e "\n\nout file:"
		sh -xc "cat $name.out"
		echo -e "\n\nphp file:"
		sh -xc "cat $name.php"
	done
	exit 1
else
	exit 0
fi
