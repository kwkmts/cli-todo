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

void list(void)
{
    puts("|=----+-----------+-------------------------------------------------------------------=|");
    puts("|  id | done?     | TASK                                                               |");
    for (Todo *todo = todo_list; todo; todo = todo->next) {
        if (todo->state == Undone) {
            puts("|=----+-----------+-------------------------------------------------------------------=|");
            printf("| %3d | %-9s | %-67s|\n", todo->id, state_str[todo->state], todo->task);
        }
    }
    puts("|=----+-----------+-------------------------------------------------------------------=|");
}

void list_all(void)
{
    puts("|=----+-----------+-------------------------------------------------------------------=|");
    puts("|  id | done?     | TASK                                                               |");
    for (Todo *todo = todo_list; todo; todo = todo->next) {
        puts("|=----+-----------+-------------------------------------------------------------------=|");
        printf("| %3d | %-9s | %-67s|\n", todo->id, state_str[todo->state], todo->task);
    }
    puts("|=----+-----------+-------------------------------------------------------------------=|");
}

void add(void)
{
    char *task = calloc(TASK_LENGTH, sizeof(char));

    while (strcmp(task, "") == 0) {
        printf("タスクを入力: ");
        get_str(task, TASK_LENGTH);
    }

    if (strcmp(task, "\\c") == 0) {
        return;
    }

    new_todo(task);
}

void del(int index)
{
    Todo *todo = find_todo(index);
    if (!todo) {
        printf("id %dのToDoは存在しません\n", index);
        return;
    }

    delete_todo(todo);
}

void edit(int index)
{
    Todo *todo = find_todo(index);
    if (!todo) {
        return;
    }

    char *new_task = calloc(TASK_LENGTH, sizeof(char));

    printf("現在のタスク: %s\n", todo->task);
    while (strcmp(new_task, "") == 0) {
        printf("タスクを入力: ");
        get_str(new_task, TASK_LENGTH);
    }

    if (strcmp(new_task, "\\c") == 0) {
        return;
    }

    todo->task = new_task;
}

void cpl(int index)
{
    Todo *todo = find_todo(index);
    if (!todo) {
        return;
    }

    todo->state = Completed;
}

void undo(int index)
{
    Todo *todo = find_todo(index);
    if (!todo) {
        return;
    }

    todo->state = Undone;
}
