#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define VERSION "R1.02"

//#define DEBUG
//#define DEBUG_VERBOSE

int open(const char *pathname, int flags, ...);
int write(int fd, const void *buf, unsigned int count);
int close(int fd);
int read(int fd, void *buf, unsigned int count);

void api_install(int id, void **apitbl);
void api_uninstall(int id);

void *dlopen(const char *filename, int flag);
void *dlsym(void *handle, const char *symbol);
int dlclose(void *handle);

unsigned int get_count(void);

#define O_RDONLY 0x0000
#define O_WRONLY 0x0001
#define O_CREAT  0x0200
#define O_TRUNC  0x0400

int launcher_core_loop(void);
void launcher_enqueue_key(void *input);
int launcher_control(int cmd, void *data);

void *p1apitbl[] = {
  launcher_core_loop,
  launcher_enqueue_key,
  launcher_control
};

void *launchee = 0;

struct api_table_s {
  int (*loop)(void);
  void (*enqueue_key)(void *input);
  int (*control)(int cmd, void *data);
};
struct api_table_s *launchee_api_table = 0;

char t[256];	/* text buffer */
int fd;	/* debug output fd */

void  __attribute__ ((section (".init"))) _init_proc(void)
{
#ifdef DEBUG
  fd = open("/mnt/disk0/launcher.txt", O_WRONLY | O_CREAT | O_TRUNC);
#define HELLO_WORLD "Hello, World, version " VERSION "!\n"
  write(fd, HELLO_WORLD, sizeof(HELLO_WORLD) - 1);
#endif

  api_install(7, p1apitbl);
}

void __attribute__ ((section (".fini"))) _term_proc(void)
{
#ifdef DEBUG
  write(fd, "fini\n", 5);
  close(fd);
#endif
  if (launchee)
    dlclose(launchee);
}

uint32_t general_plugin_info = 0;
uint32_t *get_plugin_info(void)
{
  return &general_plugin_info;
}

char *P1_SO_VERSION = VERSION;

int launcher_core_loop(void)
{
  return 0;
}

void launcher_enqueue_key(void *input)
{
  (void)input;
}

struct cmd_22 {
  uint32_t key_code_mode;
  uint32_t key_code[0x10];
  uint32_t key_file_len;
};
struct cmd_22 cmd_22_save;

int launcher_control(int cmd, void *data)
{
  int lfd;
  uint8_t hdr[4];

#if defined(DEBUG) && defined(DEBUG_VERBOSE)
  sprintf(t, "cmd %d data 0x%x\n", cmd, (unsigned int)data);
  write(fd, t, strlen(t));
#endif
  
  switch (cmd) {
    case 0:	/* init */
      return 0;
    case 2:	/* game name */
#ifdef DEBUG
      sprintf(t, "name %s\n", (char *)data);
      write(fd, t, strlen(t));
#endif
      lfd = open((char *)data, O_RDONLY);
      if (lfd < 0)
        return 1;
      if (read(lfd, hdr, 4) != 4)
        return 1;
      close(lfd);
      if (hdr[0] != 0x7f || hdr[1] != 'E' || hdr[2] != 'L' ||
        hdr[3] != 'F') {
        api_uninstall(7);
        launchee = dlopen("/mnt/disk0/real_libp1.so", 2);
        if (!launchee) {
          api_install(7, p1apitbl);
#ifdef DEBUG
          write(fd, "failed to load real_libp1.so\n", 29);
#endif
          return 1;
        }
        write(fd, "real libps1 loaded\n", 19);
        launchee_api_table = (void *)0x5148511c;
      }
      else {
        api_uninstall(7);
        launchee = dlopen((char *)data, 2);
        if (!launchee) {
          api_install(7, p1apitbl);
#ifdef DEBUG
          write(fd, "no launchee\n", 12);
#endif
          return 1;
        }
        launchee_api_table = dlsym(launchee, "api_table");
        if (!launchee_api_table) {
          api_install(7, p1apitbl);
#ifdef DEBUG
          write(fd, "no API table\n", 13);
#endif
          return 1;
        }
#ifdef DEBUG
        sprintf(t, "API symbol at 0x%x\n", (unsigned int)launchee_api_table);
        write(fd, t, strlen(t));
        sprintf(t, "API funs at 0x%x/0x%x/0x%x\n", (unsigned int)launchee_api_table->loop,
                (unsigned int)launchee_api_table->enqueue_key,
                (unsigned int)launchee_api_table->control);
        write(fd, t, strlen(t));
#endif
      }
      /* commands that have been sent to us already must be relayed to
         the launchee */
      launchee_api_table->control(0, 0);
      launchee_api_table->control(22, &cmd_22_save);
      launchee_api_table->control(2, data);
#ifdef DEBUG
      write(fd, "cmds relayed\n", 13);
#endif
      return 0;
    case 3:
#ifdef DEBUG
      write(fd, "shutdown\n", 9);
#endif
      return 0;
    case 22:
      cmd_22_save = *((struct cmd_22 *)data);
      return 0;
    default:
#ifdef DEBUG
      sprintf(t, "unknown command %d, data 0x%x\n", cmd, (unsigned int)data);
      write(fd, t, strlen(t));
#endif
      return 0;
  }
}

#define SYSCALL(name, no) \
  asm(".global " #name "\n" \
      #name ":\n" \
      "li $v1, " #no "\n" \
      "syscall 0\n");

asm(
".section .dlsym,\"a\"\n"
".word P1_SO_VERSION\n"
".word _dlstr_P1_SO_VERSION\n"
".word get_plugin_info\n"
".word _dlstr_get_plugin_info\n"
".section .dlstr,\"a\"\n"
"_dlstr_P1_SO_VERSION:\n"
".string \"P1_SO_VERSION\\0\"\n"
"_dlstr_get_plugin_info:\n"
".string \"get_plugin_info\\0\"\n"
);
