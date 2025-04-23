Grep.c
#include <stdio.h>    // Include standard input/output library for file operations and printing
#include <stdlib.h>   // Include standard library for memory allocation and process control
#include <string.h>   // Include string manipulation functions (e.g., strstr)

int main(int argc, char *argv[]) {   // Main function with arguments: argc (count), argv (array of arguments)
    if (argc < 3) {                   // Check if there are fewer than 3 arguments (program name, file, text to search)
        printf("Enter Two Arguments: File and Text to Search\n");  // Print error if arguments are missing
        return 0;                     // Exit the program
    }

    const char *path = argv[1];  // File path from the first argument
    const char *text = argv[2];  // Text to search for from the second argument

    FILE *file = fopen(path, "r");  // Open the file in read mode
    if (file == NULL) {  // Check if the file could not be opened
        printf("Error Opening File\n");  // Print error if file opening fails
        return 0;        // Exit the program
    }

    char line[1024];  // Buffer to store each line of the file

    while (fgets(line, sizeof(line), file) != NULL) {  // Read each line from the file
        if (strstr(line, text) != NULL) {  // Check if the line contains the search text
            printf("%s", line);  // Print the line if the text is found (line includes newline character)
        }
    }

    fclose(file);  // Close the file after reading
    return 0;      // Exit the program
}


Copy.c
#include <stdio.h>    // Include standard I/O functions
#include <stdlib.h>   // Include standard library functions for memory allocation and control

int main(int argc, char *argv[]) {  // Main function with command-line arguments (argc, argv)
    if (argc < 3) {  // Check if there are fewer than 3 arguments (program name, source file, destination file)
        printf("Enter Two Arguments: Source and Destination\n");  // Print error if arguments are missing
        return 0;  // Exit the program
    }

    const char *src = argv[1];  // Source file path from the first argument
    const char *dest = argv[2]; // Destination file path from the second argument

    FILE *file = fopen(src, "r");  // Open the source file in read mode
    if (file == NULL) {  // Check if the source file could not be opened
        printf("Error Opening Source File\n");  // Print error if the source file cannot be opened
        return 0;  // Exit the program
    }

    FILE *file2 = fopen(dest, "w");  // Open the destination file in write mode
    if (file2 == NULL) {  // Check if the destination file could not be created
        printf("Error Creating Destination File\n");  // Print error if destination file cannot be created
        fclose(file);  // Close the source file before exiting
        return 0;  // Exit the program
    }

    char buffer[1024];  // Buffer to store data read from the source file

    while (fgets(buffer, sizeof(buffer), file) != NULL) {  // Read each line from the source file
        fputs(buffer, file2);  // Write the line to the destination file
    }

    fclose(file);  // Close the source file after copying
    fclose(file2); // Close the destination file after copying

    printf("Done Copying The File\n");  // Notify the user that the copying is complete

    return 0;  // Exit the program
}


Code.c
#include <stdio.h>    // Include standard I/O functions
#include <stdlib.h>   // Include standard library functions
#include <unistd.h>   // Include POSIX API for system calls like fork()
#include <sys/wait.h> // Include wait() to wait for child processes
#include <string.h>   // Include string functions (e.g., strcpy, strcat)

// Main function
int main() {
    int choice;  // Variable to store the user's choice
    char arg1[100], arg2[100];  // Buffers to store source and destination file names
    pid_t pid;  // Variable to store the process ID (PID) of the child process

    printf("What do you want to simulate ??\n");  // Prompt user for action
    printf("1. Copy\n");   // Option for file copying
    printf("2. Grep\n");   // Option for searching in a file
    printf("Enter Your Choice: ");  // Prompt for choice
    scanf("%d", &choice);   // Read the user's choice

    printf("\n");

    switch (choice) {
        case 1:  // Case 1: File copy simulation
            printf("Enter source and destination file names: ");  // Prompt user for file names
            scanf("%s %s", arg1, arg2);  // Read source and destination file names

            pid = fork();  // Create a child process
            if (pid == 0) {  // If in the child process
                // Prepare arguments for the "copy" executable
                char *args[] = {"./copy", arg1, arg2, NULL};  
                printf("Copying File...\n");  // Print a message indicating file copy
                execvp("./copy", args);  // Replace the current process with the "copy" program
                perror("Error Copying File");  // If execvp fails, print an error
                exit(1);  // Exit the child process with an error code
            } else if (pid > 0) {  // If in the parent process
                wait(NULL);  // Wait for the child process to finish
                printf("Copied File Successfully\n");  // Notify the user that the file has been copied
            } else {  // If fork() fails
                perror("Fork failed");  // Print error if fork fails
            }

            break;

        case 2:  // Case 2: Grep simulation (search in a file)
            printf("Enter filename and word to search in: ");  // Prompt user for filename and search word
            scanf("%s %s", arg1, arg2);  // Read filename and search word

            pid = fork();  // Create a child process
            if (pid == 0) {  // If in the child process
                // Prepare arguments for the "grep" executable
                char *args[] = {"./grep", arg1, arg2, NULL};
                execvp("./grep", args);  // Replace current process with "grep" program
                perror("Error Finding in File");  // If execvp fails, print an error
                exit(1);  // Exit the child process with an error code
            } else if (pid > 0) {  // If in the parent process
                wait(NULL);  // Wait for the child process to finish
                printf("Execution Success\n");  // Notify the user that execution was successful
            } else {  // If fork() fails
                perror("Fork failed");  // Print error if fork fails
            }

            break;

        default:  // Invalid choice
            printf("Invalid Choice\n");  // Print error for invalid choice
            break;
    }

    return 0;  // Exit the program
}
