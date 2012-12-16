#include <actsemi.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define VERSION "R1.02"

//#define DEBUG_VERBOSE

int p1CoreLoop(void);
void p1EnqueueKey(void *input);
int p1_control(int cmd, void *data);

void *p1apitbl[] = {
  p1CoreLoop,
  p1EnqueueKey,
  p1_control
};
const void *p1apitbl_p = p1apitbl;

char t[256];	/* text buffer */
int fd;	/* debug output fd */

void  __attribute__ ((section (".init"))) _init_proc(void)
{
  fd = open("/mnt/disk0/test.txt", O_WRONLY | O_CREAT | O_TRUNC);
#define HELLO_WORLD "Hello, World, version " VERSION "!\n"
  write(fd, HELLO_WORLD, sizeof(HELLO_WORLD) - 1);

  api_install(7, p1apitbl);
}

void __attribute__ ((section (".fini"))) _term_proc(void)
{
}

uint32_t general_plugin_info = 0;
uint32_t *get_plugin_info(void)
{
  return &general_plugin_info;
}

const char *P1_SO_VERSION = VERSION;

struct rect {
  uint32_t w;
  uint32_t h;
};

struct rect screen_size;
uint16_t *screen_fb;
int redraw = 0;

int p1CoreLoop(void)
{
  static unsigned int last_run = 0;
  unsigned int elapsed = get_count() - last_run;
  if (elapsed < 16) {
    //if (elapsed < 6)
    //  usleep(5000);
    return 0;
  }
  last_run = get_count();
  static int y = 0;
  static int dir = 1;
#ifdef DEBUG_VERBOSE
  sprintf(t, "loop at %u\n", last_run);
  write(fd, t, strlen(t));
#endif
  memset(screen_fb, 0, 320 * 240 * 2);
  memset(screen_fb + y * 320, 0xff, 20 * 320 * 2);
  y += dir;
  if (y >= 220 || y == 0)
    dir = -dir;
  redraw = 1;
  return 0;
}

void p1EnqueueKey(void *input)
{
#ifdef DEBUG_VERBOSE
  write(fd, "key\n", 4);
#endif
}

struct cmd_22 {
  uint32_t key_code_mode;
  uint32_t key_code[0x10];
  uint32_t key_file_len;
};

int cmd_22(struct cmd_22 *data)
{
  return 0;
}

int max_screen_dimensions(struct rect *r)
{
  sprintf(t, "screen size %d/%d\n", (int)r->w, (int)r->h);
  write(fd, t, strlen(t));
  screen_size = *r;
  return 0;
}

struct rect_form {
  uint32_t w;
  uint32_t h;
  uint32_t format;
};

int get_our_dimensions(struct rect_form *rf)
{
  rf->w = 320;
  rf->h = 240;
  rf->format = 1;
  return 0;
}

int p1_control(int cmd, void *data)
{
  int ret;
#ifdef DEBUG_VERBOSE
  sprintf(t, "cmd %d data 0x%x\n", cmd, (unsigned int)data);
  write(fd, t, strlen(t));
#endif
  
  switch (cmd) {
    case 0:	/* init */
      return 0;
    case 1:	/* reset */
      write(fd, "reset!\n", 7);
      return 0;
    case 2:	/* game name? */
      sprintf(t, "name %s\n", (char *)data);
      write(fd, t, strlen(t));
      return 0;
    case 3:
      write(fd, "shutdown\n", 9);
      close(fd);
      return 0;
    case 4:
      sprintf(t, "another name %s\n", (char *)data);
      write(fd, t, strlen(t));
      return 0;
    case 7:	/* sound enable */
      sprintf(t, "sound enable %d\n", *((int *)data));
      write(fd, t, strlen(t));
      return 0;
    case 13:	/* get our dimensions, format */
      return get_our_dimensions((struct rect_form *)data);
    case 14:
#ifdef DEBUG_VERBOSE
      sprintf(t, "framebuffer addr 0x%x\n", *((unsigned int *)data));
      write(fd, t, strlen(t));
#endif
      screen_fb = *((uint16_t **)data);
      return 0;
    case 15:
      return max_screen_dimensions((struct rect*)data);
    case 16:	/* screen mode */
      sprintf(t, "screen mode %d\n", *((int *)data));
      write(fd, t, strlen(t));
      return 0;
    case 17:	/* get redraw flag */
#ifdef DEBUG_VERBOSE
      sprintf(t, "redraw?\n");
      write(fd, t, strlen(t));
#endif
      ret = redraw;
      redraw = 0;
      return ret;
    case 18:	/* input mode */
      sprintf(t, "input mode %d\n", *((int *)data));
      write(fd, t, strlen(t));
      return 0;
    case 22:
      return cmd_22((struct cmd_22 *)data);
    default:
      sprintf(t, "unknown command %d, data 0x%x\n", cmd, (unsigned int)data);
      write(fd, t, strlen(t));
      return 0;
  }
}

asm(
".section .dlsym,\"a\"\n"
".word P1_SO_VERSION\n"
".word _dlstr_P1_SO_VERSION\n"
".word get_plugin_info\n"
".word _dlstr_get_plugin_info\n"
".word p1apitbl\n"
".word _dlstr_api_table\n"
".section .dlstr,\"a\"\n"
"_dlstr_P1_SO_VERSION:\n"
".string \"P1_SO_VERSION\\0\"\n"
"_dlstr_get_plugin_info:\n"
".string \"get_plugin_info\\0\"\n"
"_dlstr_api_table:\n"
".string \"api_table\\0\"\n"
);
