#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"
#include "command.h"

int main(void)
{
    system("clear");
    puts("ヘルプを表示するにはhelpコマンドを入力\n");

    while (1) {
        char argv[8][64] = {};
        unsigned argc;

        list_all();

        printf("\n# ");
        char *s = get_line();
        argc = separate_str_with_space(s, argv);
        if (strcmp(argv[0], "help") == 0) {
            help();
        } else if (strcmp(argv[0], "add") == 0 && argc == 1) {
            add();
        } else if (strcmp(argv[0], "del") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            del(idx);
        } else if (strcmp(argv[0], "edit") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            edit(idx);
        } else if (strcmp(argv[0], "cpl") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            cpl(idx);
        } else if (strcmp(argv[0], "undo") == 0 && argc == 2) {
            int idx = atoi(argv[1]);
            undo(idx);
        } else if (strcmp(argv[0], "exit") == 0) {
            break;
        } else if (argc == 0) {
            system("clear");
            continue;
        } else {
            puts("サポートされていないコマンドです");
            puts("続けるには任意のキーを押してください...");
            wait_for_keypress(0);
        }

        system("clear");
    }

    return 0;
}
