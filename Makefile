CC=gcc
CFLAGS=-ansi -pedantic -Wall -Iinclude

ODIR=bin
OTESTS=$(ODIR)/tests
OEXAMPLES=$(ODIR)/examples

OUTPUTLIB=$(ODIR)/libht.a
OUTPUTTESTS=$(OTESTS)/ll_test $(OTESTS)/ht_test
OUTPUTEXAMPLES=$(OEXAMPLES)/example1

all: lib tests examples

lib: $(OUTPUTLIB)
tests: $(OUTPUTTESTS)
examples: $(OUTPUTEXAMPLES)

$(ODIR)/%.o: src/%.c
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUTLIB): $(ODIR)/ht.o $(ODIR)/ll.o
	ar rcs $@ $(ODIR)/*.o

$(OTESTS)/%.o: tests/%.c
	mkdir -p $(OTESTS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OTESTS)/%: $(OTESTS)/%.o $(OUTPUTLIB)
	$(CC) -L$(ODIR) -lht -o $@ $^

$(OEXAMPLES)/%.o: examples/%.c
	mkdir -p $(OEXAMPLES)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OEXAMPLES)/%: $(OEXAMPLES)/%.o $(OUTPUTLIB)
	$(CC) -L$(ODIR) -lht -o $@ $^

clean:
	rm -f $(ODIR)/*.o $(OTESTS)/*.o $(OEXAMPLES)/*.o $(OUTPUTLIB) $(OUTPUTTESTS) $(OUTPUTEXAMPLES)
