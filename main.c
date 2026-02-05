#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256
typedef struct Task {
    char description[MAX_STRING_LENGTH];
    int completed;
    struct Task* next;
} Task;

Task* task_list = NULL;

void add(char *description) {
    Task* new_task = (Task*)malloc(sizeof(Task));
    if (new_task == NULL) {
        printf("Malloc error");
        exit(EXIT_FAILURE);
    }

    strcpy(new_task -> description, description);
    new_task -> completed = 0;
    new_task -> next = NULL;

    if (task_list == NULL) {
        task_list = new_task;
    } else {
        Task* current = task_list;
        while (current -> next != NULL) {
            current = current -> next;
        }
        current -> next = new_task;
    }
    
}

void list() {

}

void complete() {

}

void delete() {

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Invalid command. Use todo -h for help.\n");
    }
    return 0;
}