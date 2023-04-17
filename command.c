#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "model.h"
#include "lib.h"

#define TASK_LENGTH 64

char state_str[][10] = {"Undone", "Completed"};

void help(void)
{
    system("clear");

    puts("\n------------------------------------------------");
    puts("help         ヘルプを表示");
    puts("add          ToDoを新規作成(\\cでキャンセル)");
    puts("del <id>     ToDoを削除");
    puts("edit <id>    ToDoを編集(\\cでキャンセル)");
    puts("cpl <id>     ToDoを完了済みにする");
    puts("undo <id>    ToDoを未完了に戻す");
    puts("exit         アプリを終了");
    puts("------------------------------------------------");

    printf("\nヘルプを終了するにはqを押してください\n:");
    wait_for_keypress('q');
}

void list(const List *todo_list)
{
    Todo *list = todo_list->todo_list;

    puts("|=----+-----------+-------------------------------------------------------------------=|");
    puts("|  id | done?     | TASK                                                               |");
    for (int i = 0; i < todo_list->length; i++) {
        if (list[i].state == Undone) {
            puts("|=----+-----------+-------------------------------------------------------------------=|");
            printf("| %3d | %-9s | %-67s|\n", list[i].id, state_str[list[i].state], list[i].task);
        }
    }
    puts("|=----+-----------+-------------------------------------------------------------------=|");
}

void list_all(const List *todo_list)
{
    Todo *list = todo_list->todo_list;

    puts("|=----+-----------+-------------------------------------------------------------------=|");
    puts("|  id | done?     | TASK                                                               |");
    for (int i = 0; i < todo_list->length; i++) {
        if (list[i].state != Unregistered) {
            puts("|=----+-----------+-------------------------------------------------------------------=|");
            printf("| %3d | %-9s | %-67s|\n", list[i].id, state_str[list[i].state], list[i].task);
        }
    }
    puts("|=----+-----------+-------------------------------------------------------------------=|");
}

void add(List *todo_list)
{
    Todo *list = todo_list->todo_list;
    char task[TASK_LENGTH] = "";
    int i;

    while (strcmp(task, "") == 0) {
        printf("タスクを入力: ");
        get_str(task, TASK_LENGTH);
    }

    if (strcmp(task, "\\c") == 0) {
        return;
    }

    for (i = 0; i < todo_list->length; i++) {
        if (list[i].state == Unregistered) {
            list[i].state = Undone;
            strncpy(list[i].task, task, 32);
            return;
        }
    }

    make_list(todo_list, 10);

    list = todo_list->todo_list;
    list[i].state = Undone;
    strncpy(list[i].task, task, 32);
}

void del(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        return;
    }

    Todo *todo = &todo_list->todo_list[index];
    todo->state = Unregistered;
    strcpy(todo->task, "");
}

void edit(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        return;
    }

    Todo *todo = &todo_list->todo_list[index];
    char task[TASK_LENGTH];
    char new_task[TASK_LENGTH] = "";

    strcpy(task, todo->task);

    printf("現在のタスク: %s\n", todo->task);
    while (strcmp(new_task, "") == 0) {
        printf("タスクを入力: ");
        get_str(new_task, TASK_LENGTH);
    }

    if (strcmp(new_task, "\\c") == 0) {
        return;
    }

    strncpy(todo->task, new_task, TASK_LENGTH);

}

void cpl(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        return;
    }

    Todo *todo = &todo_list->todo_list[index];
    todo->state = Completed;

}

void undo(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        return;
    }

    Todo *todo = &todo_list->todo_list[index];
    todo->state = Undone;

}
