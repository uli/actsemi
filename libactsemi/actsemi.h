#include <stdio.h>
#include <stdint.h>

void *kmalloc(uint32_t size);
void kfree(void *ptr);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define S_IREAD 0400
#define S_IWRITE 0200
#define S_IEXEC 0100

void api_install(int id, void **apitbl);
void api_uninstall(int id);

void *dlopen(const char *filename, int flag);
void *dlsym(void *handle, const char *symbol);
int dlclose(void *handle);

unsigned int get_count(void);
int clock_gettime(int clk, uint32_t *time);

#define EMU_KEY_START 3
#define EMU_KEY_SELECT 4
#define EMU_KEY_LEFT 5
#define EMU_KEY_RIGHT 6
#define EMU_KEY_UP 7
#define EMU_KEY_DOWN 8
#define EMU_KEY_L 9
#define EMU_KEY_R 10
#define EMU_KEY_SQUARE 17
#define EMU_KEY_CROSS 18
#define EMU_KEY_CIRCLE 19
#define EMU_KEY_TRIANGLE 20

typedef struct {
    uint8_t p1[0x16];
    uint8_t p2[0x16];
} emu_keys_t;
