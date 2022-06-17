#ifndef COMMAND_H
#define COMMAND_H

#include "model.h"

void help(void);
void list(const List *todo_list);
void list_all(const List *todo_list);
void add(List *todo_list);
void del(List *todo_list, int index);
void edit(List *todo_list, int index);
void cpl(List *todo_list, int index);
void undo(List *todo_list, int index);

#endif
