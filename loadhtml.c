#include <alloca.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define LLEN 128

void html_load(char *fname,char **h);

int main(int argc,char *argv[])
{
    DIR *d;
    struct dirent *e;
    char *c_file;
    char *h_file;
    int dlen;
    int cfd,hfd;
    char buf[1024];
    char hname[512];
    char *hbp,*bp,*bp2;
    int i,p;

    if (argc != 2) {
        printf("Please specify directory containing the html files\n");
        return 0;
    }
    d=opendir(argv[1]);
    if (d == NULL) {
        printf("could not open directory %s\n",argv[1]);
        return 0;
    }
    dlen=strlen(argv[1]);

    c_file=alloca(dlen+16);
    strcpy(c_file,argv[1]);
    strcat(c_file,"/html_files.c");
    cfd=creat(c_file,0666);

    h_file=alloca(dlen+16);
    strcpy(h_file,argv[1]);
    strcat(h_file,"/html_files.h");
    hfd=creat(h_file,0666);

    strcpy(buf,"/* created by loadhtml */\n\n");
    write(cfd,buf,strlen(buf));
    write(hfd,buf,strlen(buf));
    sprintf(buf,"#define LLEN %d\n\n",LLEN);
    write(cfd,buf,strlen(buf));
    strcpy(buf,"#include \"html_files.h\"\n\n");
    write(cfd,buf,strlen(buf));
    
    p=0;
    
    while (NULL != (e=readdir(d))){
        dlen=strlen(e->d_name);
        if (e->d_name+dlen-5 == strstr(e->d_name,".html")){
            strcpy(buf,argv[1]);
            strcat(buf,"/");
            strcat(buf,e->d_name);
            html_load(buf,&hbp);
            if (hbp == NULL) continue; //html_load failed
            strcpy(hname,e->d_name);
            bp2=hname+strlen(hname)-5;
            *bp2='_';
            sprintf(buf,"const char %s[LLEN]={",hname);
            write(cfd,buf,strlen(buf));

            sprintf(buf,"extern const char %s[];\n",hname);
            write(hfd,buf,strlen(buf));

            bp=hbp;
            i=0;
            while (*bp != 0) {
                sprintf(buf,"'\\x%X'",(int)*bp);
                if (i == LLEN-1) {
                    strcat(buf,"};\n");
                    write(cfd,buf,strlen(buf));
                    sprintf(buf,"const char %s_%d[LLEN]={",hname,p);
                    write(cfd,buf,strlen(buf));
                    i=0;++p;++bp;
                }
                else {
                    strcat(buf,",");
                    write(cfd,buf,strlen(buf));
                    ++bp;++i;
                }
            }
            while (i < LLEN) {
                strcpy(buf,"'\\x0'");
                if (i == LLEN-1) {
                    strcat(buf,"};\n\n\n");
                    write(cfd,buf,strlen(buf));
                }
                else {
                    strcat(buf,",");
                    write(cfd,buf,strlen(buf));
                }
                ++i;
            }
            free(hbp);
        }
    }
    close(cfd);
    close(hfd);
    return 0;
}

void html_load(char *fname,char **h)
{
	int fd;
	struct stat st;

	fd=open(fname,O_RDONLY);
	if (fd == -1) {
		*h=NULL;
		return;
	}
	if ( 0 != fstat(fd,&st)) {
		abort();
	}
	*h=malloc(st.st_size+1);
	if (st.st_size != read(fd,*h,st.st_size)) {
		free(*h);
		*h=NULL;
		close(fd);
		return;
	}
	close(fd);
	*(*h+st.st_size)='\0';
}
