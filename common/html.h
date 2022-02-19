#ifndef _htmlh
#define _htmlh

#ifdef __cplusplus
extern "C"{
#endif 

void sm32_out(char *bp);
void html_load(char *fname,char **h);
void html_load_base64(char *fname,char **h);
void do_hta64(unsigned char *src, int len,unsigned char *out, int *out_len);
void html_init();
void html_out ();
void html_in();
void html_replace(char **,char *,char *);
void set_value(char *key,char *value);
void get_value(char *key,char **value);

#ifdef __cplusplus
}
#endif

#endif /* _demoh */
