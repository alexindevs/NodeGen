#include <stdio.h>
#include <stdlib.h>

char* initialize(void) {
    if (system("node -v > /dev/null 2>&1") != 0) {
        printf("Node.js is not installed or not executable.\n");
        exit(EXIT_FAILURE);
    }
    if (system("npm -v > /dev/null 2>&1") != 0) {
        printf("npm is not installed or not executable.\n");
        exit(EXIT_FAILURE);
    }

    printf("Welcome to NodeGen!\n");
    printf("Please pick a framework:\n");
    printf("1. ExpressJS\n");
    printf("2. ExpressJS + Typescript\n");
    printf("3. NestJS\n");

    int choice;
    printf("Enter your choice (1, 2, or 3): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Please enter a number between 1 and 3.\n");
        exit(EXIT_FAILURE);
    }

    char* framework;
    switch (choice) {
        case 1:
            framework = "ExpressJS";
            break;
        case 2:
            framework = "ExpressJS + Typescript";
            break;
        case 3:
            framework = "NestJS";
            break;
        default:
            framework = "Unknown";
            break;
    }
    return (framework);
}