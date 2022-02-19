#include <alloca.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define LLEN 16

unsigned int getfile(const char *fname,char **h);
void write_array(const char *name,char *bp,int cfd,unsigned int len);

int main(int argc,char *argv[])
{
    DIR *d;
    struct dirent *e;
    char *s_file;
    char *h_file;
    int dlen;
    int sfd,hfd;
    char fnames[2018];
    char buf[1024];
    char hname[512];
    char *hbp,*bp,*bpn;
    int i;
    unsigned int len;

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

    s_file=alloca(dlen+16);
    strcpy(s_file,argv[1]);
    strcat(s_file,"/html_files.s");
    unlink(s_file);
    h_file=alloca(dlen+16);
    strcpy(h_file,argv[1]);
    strcat(h_file,"/html_files.h");
    unlink(h_file);

    bp=fnames;
    while (NULL != (e=readdir(d))){
        if (e->d_name[0] == '.') continue;
        if (strchr(e->d_name,'.') == 0) continue; //count on . extension
        i=strlen(e->d_name);
        if (bp + i > &fnames[2000]) {
            printf("Too many files ???\n");
            abort();
        }
        strcpy(bp,e->d_name);
        bp=bp+i+1;
    }
    *bp='\0';

    sfd=creat(s_file,0666);
    hfd=creat(h_file,0666);

    strcpy(buf,"/* created by loadhtml */\n\n");
    write(sfd,buf,strlen(buf));
    write(hfd,buf,strlen(buf));
    strcpy(buf,"#ifdef __cplusplus\n");
    write(hfd,buf,strlen(buf));
    strcpy(buf,"#extern \"C\" {\n");
    write(hfd,buf,strlen(buf));
    strcpy(buf,"#endif\n");
    write(hfd,buf,strlen(buf));

    
    bpn=fnames;
    while (*bpn != '\0'){
        i=strlen(bpn);
        strcpy(hname,bpn);
        bp=strchr(hname,'.');
        *bp='_';

        strcpy(buf,"\t.globl\t");
        strcat(buf,hname);
        strcat(buf,"_len\n");
        write(sfd,buf,strlen(buf));

        strcpy(buf,"\t.globl\t");
        strcat(buf,hname);
        strcat(buf,"_start\n");
        write(sfd,buf,strlen(buf));

        strcpy(buf,"extern unsigned int ");
        strcat(buf,hname);
        strcat(buf,"_len;\n");
        write(hfd,buf,strlen(buf));

        strcpy(buf,"extern char ");
        strcat(buf,hname);
        strcat(buf,"_start;\n");
        write(hfd,buf,strlen(buf));

        bpn=bpn+i+1;
    }
    strcpy(buf,"#ifdef __cplusplus\n");
    write(hfd,buf,strlen(buf));
    strcpy(buf,"}\n");
    write(hfd,buf,strlen(buf));
    strcpy(buf,"#endif\n");
    write(hfd,buf,strlen(buf));
    strcpy(buf,"\t.data\n\n");
    write(sfd,buf,strlen(buf));
    close(hfd);

    bpn=fnames;
    while (*bpn != '\0'){
        strcpy(hname,argv[1]);
        strcat(hname,"/");
        strcat(hname,bpn);
        i=strlen(bpn);
        len=getfile(hname,&hbp);
        if (hbp == NULL) {
            printf("Could not load %s\n",bpn);
            abort(); //image load failed
        }
        strcpy(buf,"\t.align 4\n");
        write(sfd,buf,strlen(buf));
        strcpy(hname,bpn);
        bp=strchr(hname,'.');
        *bp='_';
        strcpy(buf,hname);
        strcat(buf,"_len:\n");
        write(sfd,buf,strlen(buf));
        sprintf(buf,"\t.long\t%u\n\n",len);
        write(sfd,buf,strlen(buf));

        strcat(hname,"_start");
        write_array(hname,hbp,sfd,len);
        free(hbp);
        bpn=bpn+i+1;
    }
    close(sfd);

    return 0;
}

void write_array(const char *name,char *bpx,int cfd,unsigned int len)
{
    int i;
    char buf[1024];
    unsigned char *bp;

    bp=(unsigned char *)bpx;

    strcpy(buf,"\t.align 1\n");
    write(cfd,buf,strlen(buf));
    sprintf(buf,"%s:\n",name);
    write(cfd,buf,strlen(buf));

    i=0;
    strcpy(buf,"\t.byte\t");
    write(cfd,buf,strlen(buf));
    while (len != 0) {
        sprintf(buf,"%u",(unsigned int)*bp);
        if (i == LLEN-1) {
            strcat(buf,"\n");
            write(cfd,buf,strlen(buf));
            strcpy(buf,"\t.byte\t");
            write(cfd,buf,strlen(buf));
            i=0;++bp;--len;
        }
        else {
            strcat(buf,",");
            write(cfd,buf,strlen(buf));
            ++bp;++i;--len;
        }
    }
    while (i < LLEN) {
        strcpy(buf,"0");
        if (i == LLEN-1) {
            strcat(buf,"\n\n\n");
            write(cfd,buf,strlen(buf));
        }
        else {
            strcat(buf,",");
            write(cfd,buf,strlen(buf));
        }
        ++i;
    }
}


unsigned int getfile(const char *fname,char **h)
{
	int fdx;
	struct stat stx;

    *h=NULL;

    fdx=open(fname,O_RDONLY);
	if (fdx == -1) {
		return 0;
	}
    if ( 0 != fstat(fdx,&stx)) {
    	return 0;
    }
    *h=(char *)malloc(stx.st_size+1);
    if (stx.st_size != read(fdx,*h,stx.st_size)) {
    	free((void *)*h);
        *h=NULL;
    	close(fdx);
    	return 0;
    }

    close(fdx);
    *(*h+stx.st_size)='\0';
    return stx.st_size;
}