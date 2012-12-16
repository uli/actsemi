#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define VERSION "R1.01"

int open(const char *pathname, int flags, ...);
int write(int fd, const void *buf, unsigned int count);
int close(int fd);
int read(int fd, void *buf, unsigned int count);
int remove(const char *pathname);
int stat(const char *pathname, void *buf);

#define O_RDONLY 0
#define O_WRONLY 1
#define O_CREAT 0x200

/* File to be installed in place of PS1 emulator */
#define SRC_FILE "/mnt/disk0/new_libp1.so"
/* Secondary PS1 emulator binary; used if libp1+.so is not there. */
#define DEST_FILE "/mnt/diska/libp1.so"
/* Primary PS1 emulator binary. */
#define DEST_FILE_PLUS "/mnt/diska/libp1+.so"
/* Backup of secondary binary created before installing. */
#define BACKUP_FILE "/mnt/disk0/backup_libp1.so"
/* Backup of primary binary created before installing. */
#define BACKUP_FILE_PLUS "/mnt/disk0/backup_libp1+.so"

void copy_file(const char *src, const char *dst)
{
    char buf[4096];
    int out_fd = open(dst, O_WRONLY | O_CREAT);
    if (out_fd < 0)
      return;
    int in_fd = open(src, O_RDONLY);
    if (in_fd < 0)
      return;
    for (;;) {
      int bytes = read(in_fd, buf, 4096);
      if (bytes <= 0)
        break;
      write(out_fd, buf, bytes);
    }
    close(out_fd);
    close(in_fd);
}

void  __attribute__ ((section (".init"))) _init_proc(void)
{
  /* Make backups of existing internal files. */
  uint8_t st[0x40];
  if (stat(BACKUP_FILE, st) < 0 && stat(DEST_FILE, st) == 0) {
    copy_file(DEST_FILE, BACKUP_FILE);
  }
  if (stat(BACKUP_FILE_PLUS, st) < 0 && stat(DEST_FILE_PLUS, st) == 0) {
    copy_file(DEST_FILE_PLUS, BACKUP_FILE_PLUS);
  }
  
  /* Check if we have a new binary to be installed. */
  if (stat(SRC_FILE, st) < 0)
    return;

  /* Replace primary binary with installee. */
  remove(DEST_FILE_PLUS);
  copy_file(SRC_FILE, DEST_FILE_PLUS);

  /* Remove update files. */
  remove(SRC_FILE);
}

void __attribute__ ((section (".fini"))) _term_proc(void)
{
}

uint32_t general_plugin_info = 0;
uint32_t *get_plugin_info(void)
{
  return &general_plugin_info;
}

char *P1_SO_VERSION = VERSION;

#define SYSCALL(name, no) \
  asm(".global " #name "\n" \
      #name ":\n" \
      "li $v1, " #no "\n" \
      "syscall 0\n");

SYSCALL(open,   0x60000)
SYSCALL(close,  0x60001)
SYSCALL(read,   0x60002)
SYSCALL(write,  0x60003)
SYSCALL(remove, 0x60007)
SYSCALL(stat,   0x60012)

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
