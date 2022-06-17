#ifndef MODEL_H
#define MODEL_H

#define TASK_LENGTH 64

typedef enum state {
    Undone, Completed, Unregistered
} State;

typedef struct todo {
    unsigned id;
    State state;
    char task[TASK_LENGTH];
} Todo;

typedef struct list {
    unsigned length;
    Todo *todo_list;
} List;

#endif
