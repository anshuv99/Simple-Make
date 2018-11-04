//
// Created by Anshu on 11/2/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reader.h"

void validateTarget(char *line, unsigned int size, int lineNo) {
    if (size == 0) {
        fprintf(stderr, "%d Invalid line : %s", lineNo, line);
        exit(EXIT_FAILURE);
    }
    if (line[0] == ' ') {
        fprintf(stderr, "%d Invalid line : %s", lineNo, line);
        exit(EXIT_FAILURE);
    }
    int countColon = 0;
    for (int i = 0; i < size; i++) {
        if (line[i] == ':')
            countColon++;
    }
    if (countColon != 1) {
        fprintf(stderr, "%d Invalid line : %s", lineNo, line);
        exit(EXIT_FAILURE);
    }
}

char *stripWhiteSpace(char *str) {
    char *newStr = malloc(MAX_SIZE * sizeof(char));
    int i = 0;
    while (*str != '\0') {
        if (*str != ' ') {
            *(newStr + i++) = *str;
        }
        str++;

    }
    return newStr;
}

void validateCommands(char *line, unsigned int size, int lineNo) {
    if (size == 0) {
        fprintf(stderr, "%d Invalid line : %s", lineNo, line);
        exit(EXIT_FAILURE);
    }
    int countTab = 0;
    for (int i = 0; i < size; i++) {
        if (line[i] == '\t')
            countTab++;
    }
}

void reader() {
    FILE *file_pointer;
    char *line = (char *) malloc(MAX_SIZE * sizeof(char));

    if (line == NULL) {
        fprintf(stderr, "Unable to allocate memory for reader input buffer");
        exit(1);
    }

    size_t len = 0;
    graph_node *graphNodeArray[MAX_SIZE];

    // Reading Makefile
    file_pointer = fopen("testmake", "r");
    if (!file_pointer) {
        // In case readfile is not present. Trying reading Makefile
        file_pointer = fopen("akefile", "r");
        // If this also fails then throw error
        if (!file_pointer) {
            fprintf(stderr, "Could not find makefile or Makefile");
            exit(EXIT_FAILURE);
        }
    }
    int lineNo = 0;
    unsigned int curNode = 0;
    unsigned int index = 0;
    // Read line by line the contents of the file
    graph_node *node = NULL;
    int c;
    do {
        lineNo++;
        // Concatente everything line;
        do {
            c = fgetc(file_pointer);
            line[index++] = (char) c;
        } while (c != '\n' && c != EOF && index < MAX_SIZE);

        if (index >= MAX_SIZE) {
            fprintf(stderr, "THIS LINE EXHAUSTED THE BUFFER SIZE %d AND HAS BEEN DISCARDED\n", MAX_SIZE);
            index = 0;
            free(line);
            line = (char *) malloc(MAX_SIZE * sizeof(char));
            continue;
        } else {
            line[index - 1] = '\0';
        }

        char *token;

        if (line[0] == '\t') {
            // Commands
            validateCommands(line, index, lineNo);

            token = strtok(line, "\t");
            if (node == NULL) {
                fprintf(stderr, "Commands before target. Don't know what to do. exiting!!!");
                exit(EXIT_FAILURE);
            } else {
                if (!node->commands) {
                    linked_list_node *llNode = createLLNode(token);
                    node->commands = llNode;
                } else {
                    appendToLL(node->commands, token);
                }
            }

        } else if (line[0] == '#' || line[0] == '\0') {
            index = 0;
            free(line);
            line = (char *) malloc(MAX_SIZE * sizeof(char));
            continue;
        } else {
            validateTarget(line, index, lineNo);
            // Now check if it's a target or not

            token = strtok(line, ":");
            // Line which is not comment, target or command
            if (!token) {
                fprintf(stderr, "%d: Invalid line : %s\n", lineNo, line);
                exit(EXIT_FAILURE);
            }

            char *targetName = malloc(sizeof(char) * MAX_SIZE);

            strcpy(targetName, token);
            targetName = stripWhiteSpace(targetName);

            token = strtok(NULL, " ");

            // New Target found. Create a new graph node.
            node = createGraphNode(targetName, NULL, NULL);
            graphNodeArray[curNode++] = node;

            int total_dep = 0;
            while (token != NULL) {
                if (strlen(token) > 0) {
                    total_dep++;
                    if (!node->dependencies) {
                        linked_list_node *llNode = createLLNode(token);
                        node->dependencies = llNode;
                    } else {
                        appendToLL(node->dependencies, token);
                    }
                }

                token = strtok(NULL, " ");
            }
        }
        index = 0;
        free(line);
        line = (char *) malloc(MAX_SIZE * sizeof(char));

    } while (c != EOF);


    createConnections(graphNodeArray, curNode);
    int isCycleFound = is_cycle_found(curNode, graphNodeArray);

    if (isCycleFound) {
        printf("Cyclic dependency found. Terminating.");
        exit(EXIT_FAILURE);
    }


    graph_node *root = graphNodeArray[0];
    int i = 0;

    while (root != NULL) {
        traverseAndExecute(root);
        i++;
        root = graphNodeArray[i];
    }

    if (fclose(file_pointer)) {
        fprintf(stderr, "Failed to close makefile or Makefile");
        exit(EXIT_FAILURE);
    }
}

int main_read() {
    reader();
    exit(EXIT_SUCCESS);
}
