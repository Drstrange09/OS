Grep.c 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
int main(int argc, char *argv[]) { 
    if (argc < 3) { 
        printf("Enter Two Arguments: File and Text to Search\n"); 
        return 0; 
    } 
 
    const char *path = argv[1]; 
    const char *text = argv[2]; 
 
    FILE *file = fopen(path, "r"); 
    if (file == NULL) { 
        printf("Error Opening File\n"); 
        return 0; 
    } 
 
    char line[1024]; 
 
    while (fgets(line, sizeof(line), file) != NULL) { 
        if (strstr(line, text) != NULL) { 
            printf("%s", line);  // line already includes newline 
        } 
    } 
 
    fclose(file); 
    return 0; 
} 
 
Copy.c 
#include <stdio.h> 
#include <stdlib.h> 
 
int main(int argc, char *argv[]) { 
    if (argc < 3) { 
        printf("Enter Two Arguments: Source and Destination\n"); 
        return 0; 
    } 
 
    const char *src = argv[1]; 
    const char *dest = argv[2]; 
  
    FILE *file = fopen(src, "r"); 
    if (file == NULL) { 
        printf("Error Opening Source File\n"); 
        return 0; 
    } 
 
    FILE *file2 = fopen(dest, "w"); 
    if (file2 == NULL) { 
        printf("Error Creating Destination File\n"); 
        fclose(file); 
        return 0; 
    } 
 
    char buffer[1024]; 
 
    while (fgets(buffer, sizeof(buffer), file) != NULL) { 
        fputs(buffer, file2); 
    } 
 
    fclose(file); 
    fclose(file2); 
 
    printf("Done Copying The File\n"); 
 
    return 0; 
} 


Code.c 
  
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <string.h> 
 
int main() { 
    int choice; 
    char arg1[100], arg2[100]; 
    pid_t pid; 
 
    printf("What do you want to simulate ??\n"); 
    printf("1. Copy\n"); 
    printf("2. Grep\n"); 
    printf("Enter Your Choice: "); 
    scanf("%d", &choice); 
 
    printf("\n"); 
 
    switch (choice) { 
        case 1: 
            printf("Enter source and destination file names: "); 
            scanf("%s %s", arg1, arg2); 
 
            pid = fork(); 
 
            if (pid == 0) { 
                // Child process 
                char *args[] = {"./copy", arg1, arg2, NULL}; 
                printf("Copying File...\n"); 
                execvp("./copy", args); 
                perror("Error Copying File"); 
                exit(1); 
            } else if (pid > 0) { 
                // Parent process 
                wait(NULL); 
                printf("Copied File Successfully\n"); 
            } else { 
                perror("Fork failed"); 
            } 
 
            break; 
 
        case 2: 
            printf("Enter filename and word to search in: "); 
            scanf("%s %s", arg1, arg2); 
 
            pid = fork(); 
 
            if (pid == 0) { 
                // Child process 
                char *args[] = {"./grep", arg1, arg2, NULL}; 
                execvp("./grep", args); 
                perror("Error Finding in File"); 
                exit(1); 
            } else if (pid > 0) { 
                // Parent process 
                wait(NULL); 
                printf("Execution Success\n"); 
            } else { 
                perror("Fork failed"); 
            } 
 
            break; 
 
        default: 
            printf("Invalid Choice\n"); 
            break; 
    } 
 
    return 0; 
} 
