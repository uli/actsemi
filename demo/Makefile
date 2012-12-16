include ../config.mk
TARGET = demo.elf

CFLAGS += -O2 -I$(BASELIBC)/include -I$(LIBACTSEMI)
LIBS = -L$(BASELIBC) -lc -L$(LIBACTSEMI) -lactsemi
OBJS = demo.o

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
