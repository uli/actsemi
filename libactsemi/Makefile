include ../config.mk
OBJS = actsemi.o
all: libactsemi.a

libactsemi.a: $(OBJS)
	$(AR) r $@ $<

clean:
	rm -f libactsemi.a $(OBJS)
