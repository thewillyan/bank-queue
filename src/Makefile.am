lib_LTLIBRARIES = libfila_fifo.la liblogtree.la libio.la
libfila_fifo_la_SOURCES = fila_fifo.c fila_fifo.h
liblogtree_la_SOURCES = logtree.c logtree.h
libio_la_SOURCES = io.c io.h

bin_PROGRAMS = bank
bank_SOURCES = main.c
bank_LDADD = libio.la liblogtree.la libfila_fifo.la
