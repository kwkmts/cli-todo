#ifndef LIB_H
#define LIB_H

#include <stdbool.h>
#include "model.h"

char *get_line();
int separate_str_with_space(char *str, char tok[8][64]);
void get_str(char str[], int length);
void make_list(List *list, int increment);
void enable_raw_mode(void);
void disable_raw_mode(void);
bool keyboard_hit(void);
void wait_for_keypress(char key);


#endif
