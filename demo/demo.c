#include <actsemi.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <dirent.h>

#define VERSION "R1.02"

//#define DEBUG_VERBOSE

int p1CoreLoop(void);
void p1EnqueueKey(void *input);
int p1_control(int cmd, void *data);

/* Table of functions called by the framework to control the "emulator". */
void *p1apitbl[] = {
  p1CoreLoop,
  p1EnqueueKey,
  p1_control
};
const void *p1apitbl_p = p1apitbl;

char t[256];	/* text buffer */
int fd;		/* debug output fd */
FILE *fp;	/* debug output file pointer */

/* Dump the contents of a directory. */
void dumpdir(const char *dir, int recurse, int raw)
{
  DIR *dp = opendir(dir);
  if (!dp) {
    fprintf(fp, "failed to open %s\n", dir);
    return;
  }
  struct dirent *de;
  while ((de = readdir(dp))) {
    if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
      continue;

    if (raw) {
      /* /mnt/sdisk's file system seems to have a different dirent
         structure... */
      fprintf(fp, "%s", dir);
      uint8_t *x = (uint8_t *)de;
      int i;
      for (i = 0; i < 16; i++) {
        fprintf(fp, " %02X", x[i]);
      }
      fprintf(fp, "[%s] \n", x);
    }
    else
      fprintf(fp, "%s/%s %d\n", dir, de->d_name, de->d_type);

    if (recurse && (de->d_type & DT_DIR) && !raw) {
      char rd[256];
      sprintf(rd, "%s/%s", dir, de->d_name);
      dumpdir(rd, recurse++, raw);
    }
  }
  closedir(dp);
}

/* Dump the contents of various file systems. */
void find(void)
{
  dumpdir("/mnt", 0, 0);	/* doesn't work */
  dumpdir("/mnt/disk0", 1, 0);	/* standard internal storage */
  dumpdir("/mnt/sdisk", 1, 1);	/* contains the OS, weird */
  dumpdir("/mnt/diska", 1, 0);	/* contains emulators and user interface */
  dumpdir("/mnt/card", 1, 0);	/* SD card? */
  dumpdir("/mnt/udisk", 1, 0);
  dumpdir("/mnt/sbakdisk", 1, 1);
}

void  __attribute__ ((section (".init"))) _init_proc(void)
{
  /* Do a few tests first before playing game. */

  fd = open("/mnt/disk0/test.txt", O_WRONLY | O_CREAT | O_TRUNC);
#define HELLO_WORLD "Hello, World, version " VERSION "!\n"
  /* Test write(). */
  write(fd, HELLO_WORLD, sizeof(HELLO_WORLD) - 1);
  /* Test sprintf(). */
  sprintf(t, "foo%d\n", 1);
  write(fd, t, strlen(t));

  /* Test stdio. */
  fp = fopen("/mnt/disk0/ftest.txt", "w");
  setbuf(fp, NULL);
  fprintf(fp, "Huhu!\n");
  fprintf(fp, "Huhu%d\n", 1);
  find();
  fclose(fp);

  /* Now we're finally being good citizens and submitting our interface. */
  api_install(7, p1apitbl);
}

void __attribute__ ((section (".fini"))) _term_proc(void)
{
}

/* No idea what this is good for. */
uint32_t general_plugin_info = 0;
uint32_t *get_plugin_info(void)
{
  return &general_plugin_info;
}

/* Version symbol the updater uses to determine if it should update an
   emulator. This demo will usually be run by our own launcher, which
   doesn't care about the version. */
const char *P1_SO_VERSION = VERSION;

struct rect {
  uint32_t w;
  uint32_t h;
};

struct rect screen_size;
uint16_t *screen_fb;
int redraw = 0;

int exit_thread = 0;
pthread_t pt;
/* Demonstration thread. */
void *thread_fun(void *data)
{
  (void)data;
  char t[48];
  int count = 0;
  while (!exit_thread) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    sprintf(t, "thread %d at %d/%d\n", ++count, tv.tv_sec, tv.tv_usec);
    write(fd, t, strlen(t));
    usleep(20000);
  }
  return NULL;
}

/* Worker function called periodically by the framework. */
int p1CoreLoop(void)
{
  static unsigned int last_run = 0;
  /* The framework will incessantly call the API functions in a loop, so
     we need to give up some CPU time for our demo thread. */
  usleep(10000);
  struct timeval tv;
  gettimeofday(&tv, NULL);
  unsigned int elapsed = tv.tv_sec * 1000 + tv.tv_usec / 1000 - last_run;
  if (elapsed < 16) {
    return 0;
  }
  last_run = tv.tv_sec * 1000 + tv.tv_usec / 1000;

  /* Draw a moving horizontal bar. */
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
  (void)input;
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
  (void)data;
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

/* Tell the system what kind of frame buffer we would like to have. */
int get_our_dimensions(struct rect_form *rf)
{
  rf->w = 320;
  rf->h = 240;
  rf->format = 1;
  return 0;
}

/* Called by the framework to change the state of the "emulator". */
int p1_control(int cmd, void *data)
{
  /* All commands should (except command 17 (redraw)) should always return 0.
     If they don't, the framework will assume there has been an error and
     abort. */
  int ret;
#ifdef DEBUG_VERBOSE
  sprintf(t, "cmd %d data 0x%x\n", cmd, (unsigned int)data);
  write(fd, t, strlen(t));
#endif
  
  switch (cmd) {
    case 0:	/* init */
      pthread_create(&pt, NULL, thread_fun, NULL);
      return 0;
    case 1:	/* reset */
      write(fd, "reset!\n", 7);
      return 0;
    case 2:	/* game name */
      sprintf(t, "name %s\n", (char *)data);
      write(fd, t, strlen(t));
      return 0;
    case 3:	/* shutdown */
      exit_thread = 1;
      pthread_join(pt, NULL);
      write(fd, "xshutdown\n", 9);
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
    case 10:	/* suspend */
      sprintf(t, "suspend\n");
      write(fd, t, strlen(t));
      return 0;
    case 13:	/* get our dimensions, format */
      return get_our_dimensions((struct rect_form *)data);
    case 14:	/* set frame buffer */
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
      /* If we return 1 here, the framework will blit the frame buffer
         to the device screen. */
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
