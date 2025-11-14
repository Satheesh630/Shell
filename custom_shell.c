#include"header.h"
int main()
{
	printf("===========Simple Linux Shell=========\n");
	help();
	char pwd[PATH_MAX];
	while(1)
	{
		char line[PATH_MAX];
	
		if(getcwd(pwd,sizeof(pwd))) {printf("(%s)$: ",pwd);}else printf("\n$:");
		fflush(stdout);
		if(!fgets(line,PATH_MAX,stdin)) continue;
		if(strspn(line," \n\t") == strlen(line)) continue;
		char *args[8];
		int argc=split_args(line,args,8);	
		//printf("Number of tokens :%d",argc);	
		if(argc==0) continue;
		/*************************************************************************************/
			
		if(strcmp(args[0],"ls")==0){printf("Entered Ls cmd\n");ls_cmd(argc>1?args[1]:NULL);}
		else if(strcmp(args[0],"cd")==0){cd_cmd(argc>1?args[1]:NULL);}
		else if (strcmp(args[0],"pwd")==0)pwd_cmd();
		else if(strcmp(args[0],"exit")==0) break;
		else fprintf(stderr,"Unknown command:%s (try help)\n",args[0]);
	
	
	
	
	}
}
