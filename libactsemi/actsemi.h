#include <stdio.h>
#include <stdint.h>


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


