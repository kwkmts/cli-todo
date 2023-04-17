#ifndef MODEL_H
#define MODEL_H

#define TASK_LENGTH 64

typedef struct Todo Todo;

typedef enum state {
    Undone, Completed
} State;

struct Todo {
    int id;
    State state;
    char *task;
    Todo *prev;
    Todo *next;
};

#endif
