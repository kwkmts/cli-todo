#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"
#include "command.h"

#define INITIAL_TODO_LENGTH 10

int main(void)
{
    List todo_list = {0, NULL};
    make_list(&todo_list, INITIAL_TODO_LENGTH);

    puts("ヘルプを表示するにはhelpコマンドを入力");

    while (1) {
        char s[64] = {};
        char argv[8][64] = {};
        unsigned argc;

        printf("# ");
        fgets(s, 64, stdin);

        argc = separate_str_with_space(s, argv);

        if (strcmp(argv[0], "help") == 0) {
            help();
        } else if (strcmp(argv[0], "list") == 0 && argc == 1) {
            list(&todo_list);
        } else if (strcmp(argv[0], "list") == 0 && argc == 2 && strcmp(argv[1], "-a") == 0) {
            list_all(&todo_list);
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
        }

        puts("");
    }

    free(todo_list.todo_list);

    return 0;
}
