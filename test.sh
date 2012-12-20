#!/bin/sh

# Copyright 2012 Francisco Souza. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

CFLAGS="-I$PWD -Wall -Wextra -Werror -pedantic -std=c99"
LDFLAGS="-L$PWD"
status=0

make yatf.o > /dev/null
for c_file in `ls tests/test_*.c`
do
	expected=`grep '^// Output:' $c_file | cut -d ':' -f2,3,4,5 | sed 's/^ //'`
	e_file=${c_file%.*}
	o_file=${e_file}.o
	$CC $CFLAGS -o $o_file -c $c_file
	if [ $? != 0 ]
	then
		echo "FAIL: $c_file"
		echo "      Failed to compile."
		status=1
		continue
	fi
	$CC $CFLAGS $LDFLAGS -o $e_file $o_file yatf.o
	if [ $? != 0 ]
	then
		echo "FAIL: $c_file"
		echo "      Failed to link."
		status=1
		rm $o_file
		continue
	fi
	output=`./$e_file | grep -a '^Ran'`
	rm $e_file $o_file
	if [ "$expected" != "$output" ]
	then
		echo "FAIL: $c_file."
		echo "      Expected output: \"${expected}\""
		echo "      Got output: \"${output}\""
		status=1
	fi
done
make clean > /dev/null
if [ $status = 0 ]
then
	echo "SUCCESS"
fi
exit $status
