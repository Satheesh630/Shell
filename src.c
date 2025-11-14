#include"header.h"

void pwd_cmd(void)
{
	char path[PATH_MAX];
	if(getcwd(path,PATH_MAX)==0) {print_error("getcwd"); return;}
	printf("%s\n",path);
}
void cd_cmd(char *path)
{
	const char *targetdir=path && *path ? path:getenv("HOME");
	if(!targetdir) targetdir="/";
	if(chdir(targetdir)==-1) {print_error("chdir"); }	
}
void print_error(const char *msg) {
    fprintf(stderr, "Error: %s: %s\n", msg, strerror(errno));
}
int split_args(char *line,char **args,int c)
{
	int n=0;
	char *token=strtok(line," \n\t");
	while(token && n<c-1)
	{
		args[n++]=token;
		token=strtok(NULL," \t\n");
	}
	args[n]=NULL;
	return n;
}
void read_mode(mode_t m,char *buf)
{
	snprintf(buf, 11, "%c%c%c%c%c%c%c%c%c%c",
             S_ISDIR(m)?'d':S_ISLNK(m)?'l':'-',
             (m&S_IRUSR)?'r':'-', (m&S_IWUSR)?'w':'-', (m&S_IXUSR)?'x':'-',
             (m&S_IRGRP)?'r':'-', (m&S_IWGRP)?'w':'-', (m&S_IXGRP)?'x':'-',
             (m&S_IROTH)?'r':'-', (m&S_IWOTH)?'w':'-', (m&S_IXOTH)?'x':'-');
}
void list_one(char *name,char *dir)
{
	char path[PATH_MAX];
	snprintf(path,sizeof(path),"%s/%s",dir,name);
	struct stat st;
	//printf("Dir name %s  \n",path);
	if(lstat(path,&st)==-1){print_error("lstat"); return;}
	char mode[11];
	read_mode(st.st_mode,mode);
	char timebuf[64];
	 struct tm *tm = localtime(&st.st_mtime);
	   strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", tm);
	  const char *type = S_ISDIR(st.st_mode)?"[DIR]": S_ISLNK(st.st_mode)?"[LNK]":"     ";
	    printf("%s %8ld %s %-5s %s\n", mode, (long)st.st_size, timebuf, type, name);
	
	

}
void ls_cmd(char *args)
{
	char path[PATH_MAX];
	if(args && *args){
		if(args[0]=='/'){
			snprintf(path,sizeof(path),"%s",args);
		}else
		{
			char cwd[PATH_MAX];
			getcwd(cwd,sizeof(cwd));
			snprintf(path,sizeof(path),"%s/%s",cwd,args);
		}	
	}else getcwd(path,sizeof(path));
	DIR *d=opendir(path);
	if(!d){print_error("opendir");return;}
	struct dirent *de;
	while((de=readdir(d)))
	{
		if(strcmp(de->d_name,".")==0 || strcmp(de->d_name,"..")==0) continue;
		list_one(de->d_name,path);
	}
	closedir(d);
}
void help(void) {	//Implement these commands basic commands for just now 
    puts("\nCommands:\n"
         "  ls [dir]           - list directory\n"
         "  cd [dir]           - change directory (default: $HOME)\n"
         "  pwd                - print working directory\n"
         "  open <file>        - open with default app (xdg-open)\n"
         "  view <file>        - view text file in less\n"
         "  rm <file>          - delete file\n"
         "  mkdir <name>       - create directory\n"
         "  rmdir <name>       - remove empty directory\n"
         "  cp <src> <dst>     - copy file (files only)\n"
         "  mv <src> <dst>     - move/rename\n"
         "  stat <path>        - file information\n"
         "  help               - show this help\n"
         "  exit               - quit\n");
}


