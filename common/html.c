#include "demo.h"
#include <alloca.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void do_ath64(unsigned char *src, int len,unsigned char *out, int *out_len);
void do_hta64(unsigned char *src, int len,unsigned char *out, int *out_len);
void in_chr(char *bp) ;

#define osc_start2 "\033]98;"
#define gui_start "12351,0,0,0,0,9,1,"
#define osc_end2 "*\033\\"

#define bsize 4096 // 4096 set to 128 to test realloc routine works ok
char *buf=0;
int dlen=0;
int buf_len=0;

void html_init()
{
	if (buf_len != 0) {
		free((void *)buf);
	}
	buf=malloc(bsize);
	buf_len=bsize;
	strcpy(buf,gui_start);;
	dlen=strlen(gui_start);
}
void html_out ()
{
    unsigned char *bp2;
    int lenx;

	if (dlen ==0) {
		return;
	}
	bp2=(unsigned char *)buf+dlen;
	if (dlen+3 > buf_len) { //about to overflow buffer
		buf_len=buf_len+bsize;
		buf=realloc(buf,buf_len);
		bp2=(unsigned char *)buf+dlen;
	}
	*bp2=0;++dlen;++bp2;
	*bp2=0;++dlen;

    out_str(osc_start2); // start of operating system command 98

    bp2=alloca(dlen * 4/3 +16);
    do_hta64((unsigned char *)buf,dlen,bp2,&lenx);
	free((void *)buf);
	buf = 0;dlen=0;buf_len=0;
    while (lenx > 4000) {
        out_block((char *)bp2,4000);
        bp2=bp2+4000;lenx=lenx-4000;
    }
	out_block((char *)bp2,lenx);
    out_str(osc_end2); // "*" + end of operating system command 98
    out_flush();
}

void html_in()
{
	char *bp;

	if (buf_len !=0 ) {
		free((void *)buf);
		buf=0;dlen=0;buf_len=0;
	}

	buf=malloc(bsize);
	buf_len=bsize;;dlen=0;
	
	bp=buf;
	while (1) {
		in_chr(bp);
		if (*bp == '*') break;
		++bp;
		++dlen;
		if (dlen == buf_len) { //about to overflow buffer
			buf_len=buf_len+bsize;
			buf=realloc(buf,buf_len);
			bp=buf+dlen;
		}
	}
	do_ath64((unsigned char *) buf,dlen,(unsigned char *)buf, &dlen);
	if (buf[dlen-1] != 0 || buf[dlen-2] != 0) {
		abort();
	}
}

void html_load_file(char *fname,char **h,int *len)
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
	*h=malloc(st.st_size+16);
	if (st.st_size != read(fd,*h,st.st_size)) {
		free(*h);
		*h=NULL;
		close(fd);
		return;
	}
	close(fd);
	*len=st.st_size;
}

void html_load(char *fname,char **h)
{
	int len;

	html_load_file(fname,h,&len);
	if (*h != NULL) {
		*(*h+len)='\0';
	}
}

void html_load_base64(char *fname,char **h)
{
	int len,lenx;
	char *bp;

	*h=NULL;
	html_load_file(fname,&bp,&len);
	if (bp == NULL) return;
    *h=malloc(len * 4/3 +16);
    do_hta64((unsigned char *)bp,len,(unsigned char *)*h,&lenx);
	*(*h+lenx)='\0';
	free(bp);
}

void html_replace(char **h,char *strcur, char *strnew)
{
    char *in,*out,*p;
    int len;
    
    in=*h;
    p=strstr(in,strcur);
    if (p == 0) return;
    len=p-in;
    out=malloc(strlen(in)+strlen(strnew)+16); // more than needed
    memcpy(out,in,len);
    strcpy(out+len,strnew);
    strcat(out,p+strlen(strcur));
    free(in);
    *h=out;
}

void in_chr(char *bp) 
{
	int a;

	a=read(0,bp,1);
	if (a != 1) abort();
}

void set_value(char *key,char *value)
{
	char *bp;
	int len;

	len =strlen(key);
	if (dlen+len+1 > buf_len) {
		buf_len=buf_len+len+bsize;
		buf=realloc(buf,buf_len);
	}
	bp=buf+dlen;
	strcpy(bp,key);
	dlen=dlen+len+1;

	len =strlen(value);
	if (dlen+len+1 > buf_len) {
		buf_len=buf_len+len+bsize;
		buf=realloc(buf,buf_len);
	}
	bp=buf+dlen;
	strcpy(bp,value);
	dlen=dlen+len+1;
}

void get_value(char *key,char **value)
{
	char *bp;

	if (*key == 0) {
		*value=key;
		return;
	}

	bp=buf;
	while (strcmp(key,bp) != 0) {
		if (*bp == 0) {
			*value=bp;
			return;
		}
		bp=bp+strlen(bp)+1;
		bp=bp+strlen(bp)+1;
	}
	*value=bp+strlen(bp)+1;
}

static const unsigned char base64_table[64] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void do_hta64(unsigned char *src, int len,unsigned char *out, int *out_len)
{
	unsigned char *pos;
	const unsigned char *end, *in;
	int olen;

	olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
	if (olen < len) {
		*out_len = 0;
		return;
	}

	end = src + len;
	in = src;
	pos = out;
	while (end - in >= 3) {
		*pos++ = base64_table[in[0] >> 2];
		*pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
		*pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
		*pos++ = base64_table[in[2] & 0x3f];
		in += 3;
	}

    if (end - in) {
		*pos++ = base64_table[in[0] >> 2];
		if (end - in == 1) {
			*pos++ = base64_table[(in[0] & 0x03) << 4];
			*pos++ = '=';
		}
		else {
			*pos++ = base64_table[((in[0] & 0x03) << 4) |
				(in[1] >> 4)];
			*pos++ = base64_table[(in[1] & 0x0f) << 2];
		}
		*pos++ = '=';
	}

	if (out_len)
		*out_len = pos - out;
	return;
}


void do_ath64(unsigned char *src, int len,unsigned char *out, int *out_len)
{
	unsigned char dtable[256], *pos, block[4], tmp;
	int i, count;
	int pad = 0;

	memset(dtable, 0x80, 256);
	for (i = 0; i < 64; i++)
		dtable[base64_table[i]] = (unsigned char)i;
	dtable['='] = 0;

	count = 0;
	for (i = 0; i < len; i++) {
		if (dtable[src[i]] != 0x80)
			count++;
	}

	if (count == 0 || count % 4) {
		*out_len = 0;
		return;
	}

	pos = out;
	count = 0;
	for (i = 0; i < len; i++) {
		tmp = dtable[src[i]];
		if (tmp == 0x80) {
			*out_len = 0;
			return;
		}

		if (src[i] == '=')
			pad++;
		block[count] = tmp;
		count++;
		if (count == 4) {
			*pos++ = (block[0] << 2) | (block[1] >> 4);
			*pos++ = (block[1] << 4) | (block[2] >> 2);
			*pos++ = (block[2] << 6) | block[3];
			count = 0;
			if (pad) {
				if (pad == 1)
					pos--;
				else if (pad == 2)
					pos -= 2;
				else {
					/* Invalid padding */
					*out_len = 0;
					return;
				}
				break;
			}
		}
	}

	*out_len = pos - out;
	return;
}
