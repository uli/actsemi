int open(const char *pathname, int flags, ...);
int write(int fd, const void *buf, unsigned int count);
int close(int fd);
int read(int fd, void *buf, unsigned int count);
int remove(const char *pathname);
int stat(const char *pathname, void *buf);

int usleep(int usecs);

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

#define SEEK_END 2

