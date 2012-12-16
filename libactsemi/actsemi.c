#define SYSCALL(name, no) \
  asm(".global " #name "\n" \
      #name ":\n" \
      "li $v1, " #no "\n" \
      "syscall 0\n");

SYSCALL(open,   0x60000)
SYSCALL(close,  0x60001)
SYSCALL(read,   0x60002)
SYSCALL(write,  0x60003)
SYSCALL(lseek,  0x60004)
SYSCALL(remove, 0x60007)
SYSCALL(stat,   0x60012)

SYSCALL(api_install,   0x10028)
SYSCALL(api_uninstall, 0x10029)

SYSCALL(dlopen,  0x1006c)
SYSCALL(dlclose, 0x1006d)
SYSCALL(dlsym,   0x1006e)

SYSCALL(get_count, 0x10038)

SYSCALL(malloc, 0x1003a)
SYSCALL(free,   0x1003b)

SYSCALL(usleep, 0x70084)
