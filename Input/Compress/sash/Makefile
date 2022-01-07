#
# Makefile for sash
#

CFLAGS = -O3
LDFLAGS = -static -s

BINDIR = /bin
MANDIR = /usr/man/man1


OBJS = sash.o cmds.o cmd_dd.o cmd_ed.o cmd_grep.o cmd_ls.o cmd_tar.o utils.o


sash:	$(OBJS)
	cc $(LDFLAGS) -o sash $(OBJS)

clean:
	rm -f $(OBJS) sash

install: sash
	cp sash $(BINDIR)/sash
	cp sash.1 $(MANDIR)/sash.1

$(OBJS):	sash.h
