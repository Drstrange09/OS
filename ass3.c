#include <stdio.h>      // For input/output functions
#include <unistd.h>     // For pipe(), fork(), read(), write(), close(), dup2()
#include <stdlib.h>     // For exit()
#include <string.h>     // For strlen()

// Function: Communication using pipe with redirection of output to a file
void withRedirection() {
    int pipefd[2];                         // Array to hold file descriptors: pipefd[0] for reading, pipefd[1] for writing
    pid_t pid;                             // Variable to store process ID
    char message[] = "Hello from Parent with Redirection!";
    char buffer[100];                     // Buffer to store data read from pipe

    if (pipe(pipefd) == -1) {             // Create a pipe
        perror("Pipe Failed");
        exit(1);
    }

    pid = fork();                         // Create a child process
    if (pid < 0) {
        perror("Fork Failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]);                 // Close write end of the pipe
        read(pipefd[0], buffer, sizeof(buffer)); // Read message from pipe
        printf("Child Received: %s\n", buffer);  // Print message to console

        // Redirect standard output to a file
        FILE *file = fopen("output.txt", "w");
        if (file == NULL) {
            perror("File Opening Failed");
            exit(1);
        }

        dup2(fileno(file), STDOUT_FILENO);       // Redirect stdout to the file
        printf("This message is redirected to output.txt\n"); // This line writes to the file
        fclose(file);                            // Close file
        close(pipefd[0]);                        // Close read end
    } else {
        // Parent process
        close(pipefd[0]);                        // Close read end of the pipe
        write(pipefd[1], message, strlen(message) + 1); // Write message to pipe
        close(pipefd[1]);                        // Close write end
    }
}

// Function: Communication using pipe without any redirection (console output)
void withoutRedirection() {
    int pipefd[2]; 
    pid_t pid;
    char message[] = "Hello from Parent without Redirection!";
    char buffer[100];

    if (pipe(pipefd) == -1) {                   // Create a pipe
        perror("Pipe Failed");
        exit(1);
    }

    pid = fork();                               // Create a child process
    if (pid < 0) {
        perror("Fork Failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]);                       // Close write end
        read(pipefd[0], buffer, sizeof(buffer)); // Read from pipe
        printf("Child Received: %s\n", buffer);  // Print message to console
        close(pipefd[0]);                       // Close read end
    } else {
        // Parent process
        close(pipefd[0]);                       // Close read end
        write(pipefd[1], message, strlen(message) + 1); // Write message to pipe
        close(pipefd[1]);                       // Close write end
    }
}

// Main function to select between the two communication modes
int main() {
    int choice;

    // Ask user for mode of communication
    printf("Choose the Mode:\n");
    printf("1. With Redirection (Output to File)\n");
    printf("2. Without Redirection (Output to Console)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Execute the corresponding function based on user input
    switch (choice) {
        case 1:
            withRedirection();                    // Call function with redirection
            printf("Output redirected to 'output.txt'.\n");
            break;
        case 2:
            withoutRedirection();                 // Call function without redirection
            break;
        default:
            printf("Invalid choice! Please enter 1 or 2.\n");
    }

    return 0;
}
