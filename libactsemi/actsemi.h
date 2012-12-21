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

typedef void* ao_handle_t;

ao_handle_t mmm_ao_open(void);

typedef struct {
    int channels;
    int rate;
} mmm_ao_params_t;

#define MMM_AO_SET_PARAMS		0x4d414f01 /* 1 mmm_ao_params_t* arg */
#define MMM_AO_PLAY			0x4d414f02 /* 1 scalar arg (0) */
#define MMM_AO_STOP			0x4d414f03 /* 1 scalar arg (0) */
#define MMM_AO_SET_EQ			0x4d414f28 /* canonical, 1 unknown pointer arg */
#define MMM_AO_SET_VPS			0x4d414f29 /* canonical, 1 scalar arg (8 or -8) */
#define MMM_AO_SET_SPECTRUM		0x4d414f2f /* canonical, 1 scalar arg (0 or 1) */
#define MMM_AO_SWITCH_FADE		0x4d414f30 /* canonical, 1 scalar arg (0 or 1) */
#define MMM_AO_SET_BUFFER_SIZE		0x4d414f32 /* guess, 1 scalar arg (0x800) */
#define MMM_AO_SET_FRAMES		0x4d414f33 /* guess, 1 scalar arg (4) */
#define MMM_AO_SET_MUTE			0x4d414f34 /* 1 scalar arg */
#define MMM_AO_GET_SPECTRUM		0x4d414f41 /* canonical, 1 unknown pointer arg */
#define MMM_AO_GET_BYTES_BUFFERED	0x4d414f45 /* 1 scalar pointer arg */

int mmm_ao_cmd(ao_handle_t handle, uint32_t cmd, void *data);

typedef struct {
    void *buf_left;
    void *buf_right;		/* ignored if 1 channel */
    uint8_t unused_08[0x10];
    uint32_t channels;
    uint32_t buf_size;		/* 0x800; buffers are 0x2000 each... */
    uint32_t unknown_20;	/* 0 or 8 */
    uint32_t unused_24;
} mmm_ao_data_t;

int mmm_ao_data(ao_handle_t handle, mmm_ao_data_t *data);
void mmm_ao_close(ao_handle_t handle);
