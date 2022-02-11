#ifndef _htmlh
#define _htmlh

void sm32_out(char *bp);
void html_load(char *fname,char **h);
void html_load_base64(char *fname,char **h);
void html_init();
void html_out ();
void html_in();
void html_replace(char **,char *,char *);
void set_value(char *key,char *value);
void get_value(char *key,char **value);


#endif /* _demoh */
