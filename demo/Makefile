include ../config.mk
TARGET = demo.elf

CFLAGS += -O2 -I$(BASELIBC)/include
LIBS = -L$(BASELIBC) -lc
OBJS = demo.o

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
