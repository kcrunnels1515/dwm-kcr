# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}
	cd dwmblocks && $(MAKE)

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz config.h
	cd dwmblocks && $(MAKE) clean

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h dwm.desktop layouts.c selfrestart.c\
		${SRC} dwm.png dwmblocks transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

<<<<<<< HEAD
install: all
=======
install: all 
>>>>>>> dev
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	cp -f dwm.desktop ${DESTDIR}/usr/share/xsessions
	chmod 644 ${DESTDIR}/usr/share/xsessions/dwm.desktop
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	cd dwmblocks && $(MAKE) install
	mkdir -p ${DESTDIR}${PREFIX}/share/dwm
	cp -f misc/* ${DESTDIR}${PREFIX}/share/dwm
	chmod 755 ${DESTDIR}${PREFIX}/share/dwm/*

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all options clean dist install uninstall
