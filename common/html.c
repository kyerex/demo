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

#define osc_start "\033]99;"
#define osc_end "\033\\"
#define osc_long_start2 "\033]98;*%08u," // add * and len if greater than 5000
#define osc_start2 "\033]98;"
#define gui_start "12351,0,0,0,0,9,1,"
#define osc_end2 "*\033\\"

#define bsize 4096 // 4096 set to 128 to test realloc routine works ok
char *buf=0;
int dlen=0;
int buf_len=0;

void sm32_out (char *bp)
{
    out_str(osc_start); // start of operating system command 99
    out_str(bp); // sm32 mnemonic
    out_str(osc_end); // end of operating system command 99
    out_flush();
}


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
	char sbuf[32];

	if (dlen ==0) {
		return;
	}
	out_flush();
	bp2=(unsigned char *)buf+dlen;
	if (dlen+3 > buf_len) { //about to overflow buffer
		buf_len=buf_len+bsize;
		buf=realloc(buf,buf_len);
		bp2=(unsigned char *)buf+dlen;
	}
	*bp2=0;++dlen;++bp2;
	*bp2=0;++dlen;


    bp2=alloca(dlen * 4/3 +16);
    do_hta64((unsigned char *)buf,dlen,bp2,&lenx);
	free((void *)buf);
	buf = 0;dlen=0;buf_len=0;
	if (lenx > 5000) {
    	sprintf(sbuf,osc_long_start2,lenx); // start of operating system command 98+*+len
	}
	else {
		strcpy(sbuf,osc_start2);
	}
	out_str(sbuf);
	out_flush();
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

/*

#define BASE64_ENCODE_OUT_SIZE(s) ((unsigned int)((((s) + 2) / 3) * 4 + 1))
#define BASE64_DECODE_OUT_SIZE(s) ((unsigned int)(((s) / 4) * 3))


 * out is null-terminated encode string.
 * return values is out length, exclusive terminating `\0'

unsigned int
base64_encode(const unsigned char *in, unsigned int inlen, char *out);


 * return values is out length

unsigned int
base64_decode(const char *in, unsigned int inlen, unsigned char *out);

*/

/* This is a public domain base64 implementation written by WEI Zhicheng. */


#define BASE64_PAD '='
#define BASE64DE_FIRST '+'
#define BASE64DE_LAST 'z'

/* BASE 64 encode table */
static const char base64en[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/',
};

/* ASCII order for BASE 64 decode, 255 in unused character */
static const unsigned char base64de[] = {
	/* nul, soh, stx, etx, eot, enq, ack, bel, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/*  bs,  ht,  nl,  vt,  np,  cr,  so,  si, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/* dle, dc1, dc2, dc3, dc4, nak, syn, etb, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/* can,  em, sub, esc,  fs,  gs,  rs,  us, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/*  sp, '!', '"', '#', '$', '%', '&', ''', */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/* '(', ')', '*', '+', ',', '-', '.', '/', */
	   255, 255, 255,  62, 255, 255, 255,  63,

	/* '0', '1', '2', '3', '4', '5', '6', '7', */
	    52,  53,  54,  55,  56,  57,  58,  59,

	/* '8', '9', ':', ';', '<', '=', '>', '?', */
	    60,  61, 255, 255, 255, 255, 255, 255,

	/* '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', */
	   255,   0,   1,  2,   3,   4,   5,    6,

	/* 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', */
	     7,   8,   9,  10,  11,  12,  13,  14,

	/* 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', */
	    15,  16,  17,  18,  19,  20,  21,  22,

	/* 'X', 'Y', 'Z', '[', '\', ']', '^', '_', */
	    23,  24,  25, 255, 255, 255, 255, 255,

	/* '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', */
	   255,  26,  27,  28,  29,  30,  31,  32,

	/* 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', */
	    33,  34,  35,  36,  37,  38,  39,  40,

	/* 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', */
	    41,  42,  43,  44,  45,  46,  47,  48,

	/* 'x', 'y', 'z', '{', '|', '}', '~', del, */
	    49,  50,  51, 255, 255, 255, 255, 255
};

//unsigned int
//base64_encode(const unsigned char *in, unsigned int inlen, char *out)
void do_hta64(unsigned char *in, int inlen,unsigned char *out, int *out_len)
{
	int s;
	unsigned int i;
	unsigned int j;
	unsigned char c;
	unsigned char l;

	s = 0;
	l = 0;
	for (i = j = 0; i < inlen; i++) {
		c = in[i];

		switch (s) {
		case 0:
			s = 1;
			out[j++] = base64en[(c >> 2) & 0x3F];
			break;
		case 1:
			s = 2;
			out[j++] = base64en[((l & 0x3) << 4) | ((c >> 4) & 0xF)];
			break;
		case 2:
			s = 0;
			out[j++] = base64en[((l & 0xF) << 2) | ((c >> 6) & 0x3)];
			out[j++] = base64en[c & 0x3F];
			break;
		}
		l = c;
	}

	switch (s) {
	case 1:
		out[j++] = base64en[(l & 0x3) << 4];
		out[j++] = BASE64_PAD;
		out[j++] = BASE64_PAD;
		break;
	case 2:
		out[j++] = base64en[(l & 0xF) << 2];
		out[j++] = BASE64_PAD;
		break;
	}

	out[j] = 0;
	*out_len=j;
	return;
}

void do_ath64(unsigned char *in, int inlen,unsigned char *out, int *out_len)
//unsigned int
//base64_decode(const char *in, unsigned int inlen, unsigned char *out)
{
	unsigned int i;
	unsigned int j;
	unsigned char c;

	if (inlen & 0x3) {
		*out_len=0;
		return;
	}

	for (i = j = 0; i < inlen; i++) {
		if (in[i] == BASE64_PAD) {
			break;
		}
		if (in[i] < BASE64DE_FIRST || in[i] > BASE64DE_LAST) {
			*out_len=0;
			return;
		}

		c = base64de[(unsigned char)in[i]];
		if (c == 255) {
			*out_len=0;
			return;
		}

		switch (i & 0x3) {
		case 0:
			out[j] = (c << 2) & 0xFF;
			break;
		case 1:
			out[j++] |= (c >> 4) & 0x3;
			out[j] = (c & 0xF) << 4; 
			break;
		case 2:
			out[j++] |= (c >> 2) & 0xF;
			out[j] = (c & 0x3) << 6;
			break;
		case 3:
			out[j++] |= c;
			break;
		}
	}
    *out_len=j;
	return;
}
