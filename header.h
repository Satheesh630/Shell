#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <libgen.h>
#include <time.h>
#include<sys/wait.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
#define BUFSZ 65536
void pwd_cmd(void);
void cd_cmd(char *);
void read_mode(mode_t m,char *buf);
void list_one(char *name,char *dir);
void print_error(const char *msg);
void help(void);
int split_args(char *,char **,int);
void ls_cmd(char *);
