TESTS = check_io check_logtree check_fila_fifo
check_PROGRAMS = check_io check_logtree check_fila_fifo

check_io_SOURCES = check_io.c $(top_builddir)/src/io.h
check_io_CFLAGS = @CHECK_CFLAGS@
check_io_LDADD = $(top_builddir)/src/libio.la @CHECK_LIBS@

check_logtree_SOURCES = check_logtree.c $(top_builddir)/src/logtree.h
check_logtree_CFLAGS = @CHECK_CFLAGS@
check_logtree_LDADD = $(top_builddir)/src/liblogtree.la @CHECK_LIBS@

check_fila_fifo_SOURCES = check_fila_fifo.c $(top_builddir)/src/fila_fifo.h
check_fila_fifo_CFLAGS = @CHECK_CFLAGS@
check_fila_fifo_LDADD = $(top_builddir)/src/libfila_fifo.la @CHECK_LIBS@