#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "model.h"

int separate_str_with_space(char str[64], char tok[8][64]) {
  char *ptr;
  int n;

  if (str[0] == '\n') {
    return 0;
  }

  ptr = strtok(str, " \n");
  strcpy(tok[0], ptr);

  for (int i = 1; ptr != NULL; i++) {
    ptr = strtok(NULL, " \n");

    if (ptr != NULL) {
      strcpy(tok[i], ptr);
    }
  }

  for (n = 0; tok[n][0] != '\0'; n++) {
    ;
  }

  return n;
}

void get_str(char str[], int length)
{
    fgets(str, length, stdin);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

void make_list(List *list, int increment)
{
    unsigned length = list->length;

    list->length += increment;

    Todo *tmp = (Todo *) realloc(list->todo_list, list->length * sizeof(Todo));

    if (tmp == NULL) {
        free(list->todo_list);
        exit(1);
    }

    list->todo_list = tmp;

    for (unsigned i = length; i < list->length; i++) {
        list->todo_list[i].id = i;
        list->todo_list[i].state = Unregistered;
        strcpy(list->todo_list[i].task, "");
    }
}
