# See LICENSE file for copyright and license details.

include config.mk

all: options dwmstatus

options:
	@echo ${NAME} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

config.h: config.def.h
	@echo "cp config.def.h -> config.h"
	cp config.def.h config.h

dwmstatus.o: dwmstatus.c config.h
	${CC} ${CFLAGS} -c dwmstatus.c

dwmstatus: dwmstatus.o
	${CC} ${CFLAGS} $@.o dwmstatus.o -o $@ ${LIBS}

install:
	cp -f dwmstatus ${PREFIX}/bin/dwmstatus

clean:
	rm -f *.o dwmstatus config.h