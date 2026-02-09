#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256
typedef struct Task {
    int completed;
    char description[MAX_STRING_LENGTH];
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
    Task* current = task_list;
    int i = 0;
    while (current != NULL) {
        if (current->completed == 0) {
            printf("❌");
        } else {
            printf("✅");
        }
        printf("%s\n", current -> description);
        current = current -> next;
        i++;
    }
}

void complete() {

}

void delete() {

}

void load_file() {
    FILE* file = fopen("tasks.txt", "r");
    if (file == NULL) return;

    int status;
    char desc[256];

    while (fscanf(file, "%d;%[^\n]", &status, desc) == 2) {
        add(desc);

        Task* current = task_list;
        while (current -> next != NULL) current = current -> next;
        current -> completed = status;
    }
}

void save_file() {
    FILE* file = fopen("tasks.txt", "w");
    if (file == NULL) return;

    Task* current_task = task_list;

    while (current_task != NULL) {
        fprintf(file, "%d;%s\n", current_task -> completed, current_task -> description);
        current_task = current_task -> next;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Invalid command. Use todo -h for help.\n");
    }
    
    load_file();

    if (strcmp(argv[1], "add") == 0) {
        add(argv[2]);
        save_file();
    } else if (strcmp(argv[1], "list") == 0) {
        list();
    }

    return 0;
}