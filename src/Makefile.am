lib_LTLIBRARIES = liblogtree.la libio.la
liblogtree_la_SOURCES = logtree.c logtree.h
libio_la_SOURCES = io.c io.h

bin_PROGRAMS = bank
bank_SOURCES = main.c
bank_LDADD = libio.la liblogtree.la
