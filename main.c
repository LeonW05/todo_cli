#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Detect if the OS is windows or linux
#ifdef _WIN32
    #define PATH_SEPARATOR "\\"
#else
    #define PATH_SEPARATOR "/"
#endif

#define MAX_STRING_LENGTH 256
typedef struct Task {
    int completed;
    char description[MAX_STRING_LENGTH];
    struct Task* next;
} Task;

Task* task_list = NULL;

void get_path(char* buffer, size_t size) {
    char* home = getenv("HOME");
    if (home == NULL) {
        // We are on windows
        home = getenv("USERPROFILE");
    }

    if (home == NULL) {
        // If everything fails, just use the current directory
        snprintf(buffer, size, ".tasks.txt");
    } else {
        snprintf(buffer, size, "%s%s%s", home, PATH_SEPARATOR, ".tasks.txt");
    }
}

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
    int i = 1;
    while (current != NULL) {
        printf("%d  ", i);
        if (current->completed == 0) {
            printf("❌ ");
        } else {
            printf("✅ ");
        }
        printf("%s\n", current -> description);
        current = current -> next;
        i++;
    }
}

void complete(int pos) {
    Task* current = task_list;
    int i = 1;
    while (i != pos && current != NULL) {
        current = current -> next;
        i++;
    }

    if (current == NULL) {
        printf("Invalid index");
        return;
    }

    current -> completed = 1;
}

void uncomplete(int pos) {
    Task* current = task_list;
    int i = 1;
    while (i != pos && current != NULL) {
        current = current -> next;
        i++;
    }

    if (current == NULL) {
        printf("Invalid index");
        return;
    }

    current -> completed = 0;
}

void delete(int pos) {
    Task* current = task_list;
    Task* prev = task_list;
    int i = 1;

    if (pos == 1) {
        task_list = current -> next;
        free(current);
        return;
    }

    while (i != pos && current != NULL) {
        prev = current;
        current = current -> next;
        i++;
    }
    
    if (current == NULL) {
        printf("invalid index");
        return;
    }

    prev -> next = current -> next;
    free(current);
}

void load_file() {
    char path[512];
    get_path(path, sizeof(path));
    FILE* file = fopen(path, "r");
    if (file == NULL) return;

    int status;
    char desc[MAX_STRING_LENGTH];

    while (fscanf(file, "%d;%[^\n]", &status, desc) == 2) {
        add(desc);

        Task* current = task_list;
        while (current -> next != NULL) current = current -> next;
        current -> completed = status;
    }

    fclose(file);
}

void save_file() {
    char path[512];
    get_path(path, sizeof(path));
    FILE* file = fopen(path, "w");
    if (file == NULL) return;

    Task* current_task = task_list;

    while (current_task != NULL) {
        fprintf(file, "%d;%s\n", current_task -> completed, current_task -> description);
        current_task = current_task -> next;
    }

    fclose(file);
}

void print_help() {
    printf("\n");
    printf("  TODO LIST CLI - Help Menu\n");
    printf("  -------------------------\n");
    printf("  Usage: todo <command> [arguments]\n\n");
    printf("  Commands:\n");
    printf("    add <text>       Add a new task (use quotes for sentences)\n");
    printf("    list             List all tasks\n");
    printf("    complete <id>    Mark task <id> as completed\n");
    printf("    uncomplete <id>  Mark task <id> as incomplete\n");
    printf("    delete <id>      Delete task <id> permanently\n");
    printf("    -h, --help       Show this help message\n");
    printf("\n");
    printf("  Examples:\n");
    printf("    todo add \"Buy milk\"\n");
    printf("    todo list\n");
    printf("    todo complete 1\n");
    printf("\n");
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Invalid command. Use todo -h for help.\n");
        exit(EXIT_FAILURE);
    }
    
    load_file();

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            printf("Please provide a task description.\n");
            exit(EXIT_FAILURE);
        }
        add(argv[2]);
        save_file();
    } else if (strcmp(argv[1], "list") == 0) {
        list();
    } else if (strcmp(argv[1], "complete") == 0) {
        if (argc < 3) {
            printf("Please provide the task id to complete.\n");
            exit(EXIT_FAILURE);
        }
        complete(atoi(argv[2]));
        save_file();
    } else if (strcmp(argv[1], "uncomplete") == 0){
        if (argc < 3) {
            printf("Please provide the task id to uncomplete.\n");
            exit(EXIT_FAILURE);
        }
        uncomplete(atoi(argv[2]));
        save_file();
    } else if (strcmp(argv[1], "delete") == 0) {
        if (argc < 3) {
            printf("Please provide the task id to delete.\n");
            exit(EXIT_FAILURE);
        }
        delete(atoi(argv[2]));
        save_file();
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help();
    } else {
        printf("Invalid command, Use todo -h for help.\n");
    }

    return 0;
}