include ../config.mk
CFLAGS += -I$(BASELIBC)/include
OBJS = actsemi.o
all: libactsemi.a

libactsemi.a: $(OBJS)
	$(AR) r $@ $<

clean:
	rm -f libactsemi.a $(OBJS)
