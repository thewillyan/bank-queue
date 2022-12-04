# Librarys
lib_LTLIBRARIES = libcliente.la liblogtree.la libio.la libfila_fifo.la liboutput.la libescalonador.la 

libcliente_la_SOURCES = cliente.h

liblogtree_la_SOURCES = logtree.c logtree.h
liblogtree_la_LIBADD = libcliente.la

libio_la_SOURCES = io.c io.h
libio_la_LIBADD = libcliente.la

libfila_fifo_la_SOURCES = fila_fifo.c fila_fifo.h

libescalonador_la_SOURCES = escalonador.c escalonador.h
libescalonador_la_LIBADD = libio.la libfila_fifo.la liboutput.la liblogtree.la 

liboutput_la_SOURCES = output.c output.h
liboutput_la_LIBADD = libcliente.la liblogtree.la

# Program
bin_PROGRAMS = bank
bank_SOURCES = main.c
bank_LDADD = libcliente.la liblogtree.la libio.la libfila_fifo.la liboutput.la libescalonador.la 