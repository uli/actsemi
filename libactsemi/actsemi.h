#include <stdio.h>
#include <stdint.h>

int open(const char *pathname, int flags, ...);
int write(int fd, const void *buf, unsigned int count);
int close(int fd);
int read(int fd, void *buf, unsigned int count);
int remove(const char *pathname);
int stat(const char *pathname, void *buf);

int rename(const char *oldpath, const char *newpath);
int mkdir(const char *pathname, uint32_t mode);

void *malloc(uint32_t size);
void free(void *ptr);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define S_IREAD 0400
#define S_IWRITE 0200
#define S_IEXEC 0100

struct dirent {
  uint8_t _unknown_00[0xe];
  uint8_t d_type;
  uint8_t _unknown_0f;
  char d_name[];
};
#define DT_DIR 0x10

typedef void DIR;
DIR *opendir(const char *name);
struct dirent *readdir(DIR *);
int closedir(DIR *);

//typedef void FILE;
FILE *fopen(const char *path, const char *mode);
int fclose(FILE *);
int fseek(FILE *, long offset, int whence);
long ftell(FILE *);
void setbuf(FILE *stream, char *buf);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
char *fgets(char *s, int size, FILE *stream);

int usleep(int usecs);

void api_install(int id, void **apitbl);
void api_uninstall(int id);

void *dlopen(const char *filename, int flag);
void *dlsym(void *handle, const char *symbol);
int dlclose(void *handle);

typedef void* pthread_t;
typedef uint8_t pthread_attr_t[0x28];
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
int pthread_cancel(pthread_t thread);
void pthread_exit(void *retval);

unsigned int get_count(void);
int clock_gettime(int clk, uint32_t *time);

struct timeval {
  uint32_t tv_sec;
  uint32_t tv_usec;
};
int gettimeofday(struct timeval *tv, void *tz);

#define O_RDONLY 0x0000
#define O_WRONLY 0x0001
#define O_CREAT  0x0200
#define O_TRUNC  0x0400

#define SEEK_END 2

