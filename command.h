#ifndef COMMAND_H
#define COMMAND_H

#include "model.h"

void help(void);
void list(void);
void list_all(void);
void add(void);
void del(int index);
void edit(int index);
void cpl(int index);
void undo(int index);

#endif
