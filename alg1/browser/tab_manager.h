#ifndef _TAB_MANAGER_H
#define _TAB_MANAGER_H

typedef struct _browser BROWSER;

BROWSER* new_browser();
int add_tab(BROWSER*, char*, char*);
int move_tab(BROWSER*, char*, int);
void print_tabs(BROWSER*);
void free_browser(BROWSER*);

#endif
