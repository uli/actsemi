include ../config.mk
TARGET = launcher.elf

CFLAGS += -O2 -I$(BASELIBC)/include
LIBS = -L$(BASELIBC) -lc
OBJS = launcher.o

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
