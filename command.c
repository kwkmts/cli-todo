#include <stdio.h>
#include <string.h>
#include "model.h"
#include "lib.h"

#define TASK_LENGTH 64

char state_str[][10] = {"Undone", "Completed"};

void help(void)
{
    puts("------------------------------------------------");
    puts("help         ヘルプを表示");
    puts("list         未完了のToDoを表示");
    puts("list -a      全てのToDoを表示");
    puts("add          ToDoを新規作成(\\cでキャンセル)");
    puts("del <id>     ToDoを削除");
    puts("edit <id>    ToDoを編集(\\cでキャンセル)");
    puts("cpl <id>     ToDoを完了済みにする");
    puts("undo <id>    ToDoを未完了に戻す");
    puts("exit         アプリを終了");
    puts("------------------------------------------------");
}

void list(const List *todo_list)
{
    Todo *list = todo_list->todo_list;

    printf("  id | done?     | TASK                             \n");
    for (int i = 0; i < todo_list->length; i++) {
        if (list[i].state == Undone) {
            printf("-----+-----------+--------------------------------------------------------------------\n");
            printf(" %3d | %-9s | %-68s\n", list[i].id, state_str[list[i].state], list[i].task);
        }
    }
}

void list_all(const List *todo_list)
{
    Todo *list = todo_list->todo_list;

    printf("  id | done?     | TASK                             \n");
    for (int i = 0; i < todo_list->length; i++) {
        if (list[i].state != Unregistered) {
            printf("-----+-----------+--------------------------------------------------------------------\n");
            printf(" %3d | %-9s | %-68s\n", list[i].id, state_str[list[i].state], list[i].task);
        }
    }
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
        puts("操作がキャンセルされました");
        return;
    }

    for (i = 0; i < todo_list->length; i++) {
        if (list[i].state == Unregistered) {
            list[i].state = Undone;
            strncpy(list[i].task, task, 32);
            printf("ToDo(id: %d, TASK: %s)を作成しました\n", list[i].id, list[i].task);
            return;
        }
    }

    make_list(todo_list, 10);

    list = todo_list->todo_list;
    list[i].state = Undone;
    strncpy(list[i].task, task, 32);
    printf("ToDo(TASK: %s)を作成しました\n", list[i].task);
}

void del(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        puts("ToDoが見つかりませんでした");
    } else {
        Todo *todo = &todo_list->todo_list[index];

        printf("ToDo(TASK: %s)を削除しました\n", todo->task);
        todo->state = Unregistered;
        strcpy(todo->task, "");
    }
}

void edit(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        puts("ToDoが見つかりませんでした");
    } else {
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
            puts("操作がキャンセルされました");
            return;
        }

        strncpy(todo->task, new_task, TASK_LENGTH);
        printf("TASKが変更されました: %s => %s\n", task, todo->task);
    }
}

void cpl(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        puts("ToDoが見つかりませんでした");
    } else {
        Todo *todo = &todo_list->todo_list[index];

        todo->state = Completed;
        printf("ToDo(TASK: %s)を完了済みとしました\n", todo->task);
    }
}

void undo(List *todo_list, int index)
{
    if (index >= todo_list->length || todo_list->todo_list[index].state == Unregistered) {
        puts("ToDoが見つかりませんでした");
    } else {
        Todo *todo = &todo_list->todo_list[index];

        todo->state = Undone;
        printf("ToDo(TASK: %s)を未完了に戻しました\n", todo->task);
    }
}
