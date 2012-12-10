#!/bin/sh

CFLAGS="-I$PWD $CFLAGS"
LDFLAGS="-L$PWD $LDFLAGS"
status=0

make yatf.o > /dev/null
for c_file in `ls tests/test_*.c`
do
	expected=`grep '^/\* Output:' $c_file | cut -d ':' -f2,3 | sed 's/^ //' | sed 's, \*/$,,'`
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
