include ../config.mk
TARGET = installer.elf

CFLAGS += -O2 -I$(BASELIBC)/include
LIBS = -L$(BASELIBC) -lc
OBJS = installer.o

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
