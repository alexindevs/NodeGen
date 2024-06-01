#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../functions.h"

int initializeNestJSApp() {
    char project_name[400];

    printf("\nWhat do you want your app to be called? ");
    scanf("%399s", project_name);

    char working_directory[1024];
    if (getcwd(working_directory, sizeof(working_directory)) == NULL) {
        printf("Error: Could not get current working directory.\n");
        return 1;
    }

    printf("Creating NestJS Project %s in directory %s...\n", project_name, working_directory);

    if (system("npm i -g @nestjs/cli") != 0) {
        printf("Error: Failed to install NestJS CLI.\n");
        return 1;
    }

    char nest_command[512];
    sprintf(nest_command, "nest new %s", project_name);
    system(nest_command);

    printf("Your NestJS project %s is ready to use!\n", project_name);
    printf("Run 'cd %s' to enter the project directory.\n", project_name);
    printf("Run 'npm start' to start the server.\n");
    printf("Happy coding!\n");
    
    return 0;
}
