# Copyright 2012 Francisco Souza. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

OBJS = yatf.o

CFLAGS = -I/usr/local/include/ -Wall -Wextra -Werror -pedantic -ansi

yatf.o: yatf.h

libyatf.a: $(OBJS)
	ar -crs libyatf.a $(OBJS)

clean:
	rm -f $(OBJS) libyatf.a
