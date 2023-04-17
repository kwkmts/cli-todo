#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"

#include "command.h"


#define INITIAL_TODO_LENGTH 10

typedef struct Char Char;

typedef struct Char {
    int ch;
    Char *next;
} Char;

int main(void)
{
    List todo_list = {0, NULL};
    make_list(&todo_list, INITIAL_TODO_LENGTH);

    system("clear");
    puts("ヘルプを表示するにはhelpコマンドを入力\n");

    while (1) {
        char argv[8][64] = {};
        unsigned argc;

        list_all(&todo_list);

        printf("\n# ");
        char *s = get_line();
        argc = separate_str_with_space(s, argv);
        if (strcmp(argv[0], "help") == 0) {
            help();
        } else if (strcmp(argv[0], "add") == 0 && argc == 1) {
            add(&todo_list);
        } else if (strcmp(argv[0], "del") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            del(&todo_list, idx);
        } else if (strcmp(argv[0], "edit") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            edit(&todo_list, idx);
        } else if (strcmp(argv[0], "cpl") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            cpl(&todo_list, idx);
        } else if (strcmp(argv[0], "undo") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            undo(&todo_list, idx);
        } else if (strcmp(argv[0], "exit") == 0) {
            break;
        } else if (argc == 0) {
            continue;
        } else {
            puts("サポートされていないコマンドです");
            puts("続けるには任意のキーを押してください...");
            wait_for_keypress(0);
        }

        system("clear");
    }

    free(todo_list.todo_list);

    return 0;
}
