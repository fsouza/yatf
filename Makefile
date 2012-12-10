# Copyright 2012 Francisco Souza. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

OBJS = yactf.o

CFLAGS = -I/usr/local/include/ -Wall -Wextra -Werror -pedantic -ansi

yactf.o: yactf.h

yactf.a: $(OBJS)
	ar -crs yactf.a $(OBJS)

clean:
	rm $(OBJS) yactf.a
