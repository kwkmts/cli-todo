#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "lib.h"
#include "model.h"

Todo *todo_list;

typedef struct Char Char;

typedef struct Char {
    int ch;
    Char *next;
} Char;

char *get_line()
{
    Char head;
    size_t len = 0;
    Char *var = &head;
    while (1) {
        int cur = getchar();
        Char *c = calloc(1, sizeof(Char));
        if (c == NULL) {
            return NULL;
        }
        c->ch = cur;
        var->next = c;
        len++;
        var = var->next;
        if (cur == '\n') {
            break;
        }
    }

    char *str = malloc(len * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    var = head.next;
    for (int i = 0; i != len; i++) {
        str[i] = (char) var->ch;
        var = var->next;
    }

    return str;
}

int separate_str_with_space(char *str, char tok[8][64])
{
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
    }

    return n;
}

void get_str(char *str, int length)
{
    fgets(str, length, stdin);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

Todo *new_todo(char *task)
{
    static int id = 1;
    Todo *todo = calloc(1, sizeof(Todo));
    todo->id = id++;
    todo->task = task;
    todo->next = todo_list;
    if (todo_list) {
        todo_list->prev = todo;
    }
    todo_list = todo;
    return todo;
}

Todo *find_todo(int id)
{
    for (Todo *todo = todo_list; todo; todo = todo->next) {
        if (todo->id == id) {
            return todo;
        }
    }
    return NULL;
}

void delete_todo(Todo *todo)
{
    if (todo->prev) {
        todo->prev->next = todo->next;
    } else {
        todo_list = todo->next;
    }

    if (todo->next) {
        todo->next->prev = todo->prev;
    } else {
        todo->prev->next = NULL;
    }
}

void enable_raw_mode(void)
{
    struct termios attr;
    tcgetattr(0, &attr);
    attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &attr);
}

void disable_raw_mode(void)
{
    struct termios attr;
    tcgetattr(0, &attr);
    attr.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &attr);
}

bool keyboard_hit(void)
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

void wait_for_keypress(char key)
{
    enable_raw_mode();
    while (1) {
        if (keyboard_hit()) {
            int c = getchar();
            if (c == key || !key) {
                break;
            }
        }
    }

    disable_raw_mode();
}
