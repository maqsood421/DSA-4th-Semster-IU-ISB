#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <regex.h>

#define PIPE_NAME "/tmp/logpipe"
#define MAX_LINE_LENGTH 516
#define MAX_PATH_LENGTH 2024  // Increased buffer size for paths

// Define Pattern structure
struct Pattern {
    char description[MAX_LINE_LENGTH];
    int threshold;
};

// Define ServerConfig structure
struct ServerConfig {
    int timezoneOffset;
    char serverName[MAX_LINE_LENGTH];
};

// Global maps (arrays of structures for simplicity in C)
struct Pattern patterns[10];
int patternCount = 0;
struct ServerConfig servers[10];
int serverCount = 0;

// Parse configuration file
void parseConfigFile(const char* configFile) {
    FILE* file = fopen(configFile, "r");
    if (!file) {
        perror("Failed to open config file");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Pattern", 7) == 0) {
            char patternName[MAX_LINE_LENGTH], description[MAX_LINE_LENGTH];
            int threshold;
            sscanf(line, "%[^:]: %[^,], %d", patternName, description, &threshold);
            struct Pattern pat;
            strcpy(pat.description, description);
            pat.threshold = threshold;
            patterns[patternCount++] = pat;
        } else if (strncmp(line, "Server", 6) == 0) {
            char serverName[MAX_LINE_LENGTH];
            int offset;
            sscanf(line, "%[^:]: %d", serverName, &offset);
            struct ServerConfig server;
            server.timezoneOffset = offset;
            strcpy(server.serverName, serverName);
            servers[serverCount++] = server;
        }
    }
    fclose(file);
}

// Check if directory exists
int directoryExists(const char* path) {
    struct stat info;
    return (stat(path, &info) == 0 && (info.st_mode & S_IFDIR));
}

// Check if log file exists, and create if necessary
void createLogFileIfNeeded(const char* logPath) {
    FILE* file = fopen(logPath, "r");
    if (file) {
        fclose(file);
        return;  // Log file exists, no need to create
    }

    // Log file does not exist, create it
    file = fopen(logPath, "w");
    if (!file) {
        perror("Failed to create log file");
        return;
    }

    // Write some default content for testing
    fprintf(file, "Log data for testing\n");
    fprintf(file, "Error: Something went wrong\n");
    fclose(file);
}

// Create the named pipe if it doesn't exist or unlink and recreate it
void createPipeIfNeeded() {
    struct stat st;
    if (stat(PIPE_NAME, &st) == -1) {
        // Pipe doesn't exist, so create it
        if (mkfifo(PIPE_NAME, 0666) == -1) {
            perror("Failed to create pipe");
            exit(EXIT_FAILURE);
        }
        printf("Named pipe created: %s\n", PIPE_NAME);
    } else {
        // Pipe exists, so unlink (remove) it first
        if (unlink(PIPE_NAME) == -1) {
            perror("Failed to unlink pipe");
            exit(EXIT_FAILURE);
        }
        printf("Named pipe unlinked: %s\n", PIPE_NAME);

        // Now create a new pipe
        if (mkfifo(PIPE_NAME, 0666) == -1) {
            perror("Failed to create pipe after unlinking");
            exit(EXIT_FAILURE);
        }
        printf("Named pipe recreated: %s\n", PIPE_NAME);
    }
}

// Analyze a single log file
void analyzeLogFile(const char* serverName, const char* logDirectory) {
    char logPath[MAX_PATH_LENGTH];
    snprintf(logPath, sizeof(logPath), "%s/%s.log", logDirectory, serverName);

    // Check if the log directory exists
    if (!directoryExists(logDirectory)) {
        fprintf(stderr, "Failed to open server directory: %s\n", logDirectory);
        return;
    }

    // Ensure log file exists, and create if necessary
    createLogFileIfNeeded(logPath);

    FILE* logFile = fopen(logPath, "r");
    if (!logFile) {
        perror("Failed to open log file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int patternCounts[10] = {0};  // Array to store match counts for each pattern
    while (fgets(line, sizeof(line), logFile)) {
        for (int i = 0; i < patternCount; ++i) {
            struct Pattern pat = patterns[i];
            regex_t regex;
            regcomp(&regex, pat.description, REG_EXTENDED | REG_NOSUB);
            if (regexec(&regex, line, 0, NULL, 0) == 0) {
                patternCounts[i]++;
            }
            regfree(&regex);
        }
    }
    fclose(logFile);

    // Write to report file
    FILE* reportFile = fopen("report.txt", "a");
    if (!reportFile) {
        perror("Failed to open report file");
        return;
    }

    for (int i = 0; i < patternCount; ++i) {
        if (patternCounts[i] >= patterns[i].threshold) {
            fprintf(reportFile, "%s, %s, %s, %d times\n", serverName, logDirectory, patterns[i].description, patternCounts[i]);
        }
    }
    fclose(reportFile);
}

// Writer process to send data to the pipe
void writeToPipe() {
    int fd = open(PIPE_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open pipe for writing");
        return;
    }

    const char* message = "Log data from server";
    write(fd, message, strlen(message) + 1);
    close(fd);
}

// Reader process to read data from the pipe
void readFromPipe() {
    int fd = open(PIPE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open pipe for reading");
        return;
    }

    char buffer[256];
    read(fd, buffer, sizeof(buffer));
    printf("Received from server: %s\n", buffer);
    close(fd);
}

int main() {
    parseConfigFile("config.txt");

    // Create the named pipe if needed
    createPipeIfNeeded();

    // Fork a process for writing to the pipe
    pid_t writerPid = fork();
    if (writerPid == 0) {
        // Child process: write to pipe
        writeToPipe();
        exit(0);  // Exit after writing to the pipe
    }

    // Fork a process for reading from the pipe
    pid_t readerPid = fork();
    if (readerPid == 0) {
        // Child process: read from pipe
        readFromPipe();
        exit(0);  // Exit after reading from the pipe
    }

    // Wait for both child processes to finish
    waitpid(writerPid, NULL, 0);
    waitpid(readerPid, NULL, 0);

    // Assuming the log files are organized in directories by server name
    for (int i = 0; i < serverCount; ++i) {
        pid_t logAnalyzingPid = fork();
        if (logAnalyzingPid == 0) {
            // Child process: analyze log file
            analyzeLogFile(servers[i].serverName, "./logs");
            exit(0);  // Exit after analyzing the log
        }
    }

    // Wait for all log analysis processes
    for (int i = 0; i < serverCount; ++i) {
        waitpid(-1, NULL, 0);
    }

    return 0;
}
