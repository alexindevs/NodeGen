#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "../functions.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


int initializeExpressApp() {
    char project_name[400];

    printf("\nWhat do you want your app to be called? ");
    scanf("%399s", project_name);

    char working_directory[1024];
    if (getcwd(working_directory, sizeof(working_directory)) == NULL) {
        printf("Error: Could not get current working directory.\n");
        return 1;
    }

    printf("Creating Express Project %s in directory %s...\n", project_name, working_directory);

    char mkdir_command[512];
    sprintf(mkdir_command, "mkdir %s", project_name);
    system(mkdir_command);

    chdir(project_name);

    system("npm init -y");

    char* sql_or_nosql = databaseSelection();

    if (sql_or_nosql == NULL) {
        return 1;
    }

    free(sql_or_nosql);

    if (folderSetup() == 1) {
        printf("Error: Failed to create folder structure.\n");
        return 1;
    }

    printf ("Your project %s is ready to use!\n", project_name);
    printf("Run 'npm start' to start the server.\n");
    printf("Happy coding!\n");
    return 0;
}

char* databaseSelection() {

    char* sql_or_nosql = (char*)malloc(20 * sizeof(char));
    printf("Will you be working with SQL or NoSQL? ");

    while (1) {
        scanf("%19s", sql_or_nosql);

        for (int i = 0; sql_or_nosql[i]; i++) {
            sql_or_nosql[i] = toupper(sql_or_nosql[i]);
        }

        if (strcmp(sql_or_nosql, "SQL") == 0) {
            printf("Installing SQL dependencies...\n");
            if (system("npm install mysql sequelize") != 0) {
                printf("Error: Failed to install SQL dependencies.\n");
                return NULL;
            }
            break;
        } else if (strcmp(sql_or_nosql, "NOSQL") == 0) {
            printf("Installing NoSQL dependencies...\n");
            if (system("npm install mongodb mongoose") != 0) {
                printf("Error: Failed to install NoSQL dependencies.\n");
                return NULL;
            }
            break;
        } else {
            printf("Invalid input. Please enter 'SQL' or 'NoSQL'.\n");
        }
    }

    return sql_or_nosql;
}

int folderSetup() {
     if (mkdir("src", 0777) != 0) {
        printf("Error: Failed to create 'src' directory.\n");
        return 1;
    }

    chdir("src");

    char* subdirectories[] = {"routes", "controllers", "services", "models", "repositories", "utils", "config"};
    int num_subdirectories = sizeof(subdirectories) / sizeof(subdirectories[0]);

    for (int i = 0; i < num_subdirectories; i++) {
        if (mkdir(subdirectories[i], 0777) != 0) {
            printf("Error: Failed to create '%s' directory.\n", subdirectories[i]);
            return 1;
        }
    }

    FILE *file = fopen("server.js", "w");
    if (file == NULL) {
        printf("Error: Failed to create server.js file.\n");
        return 1;
    }

    fprintf(file, "// Server.js file\n\n");

    // Include necessary libraries
    fprintf(file, "const express = require('express');\n");
    fprintf(file, "const cors = require('cors');\n");
    fprintf(file, "const morgan = require('morgan');\n\n");
    fprintf(file, "require('dotenv').config();\n\n");
    fprintf(file, "bodyParser = require('body-parser');\n\n");

    // Create an Express app
    fprintf(file, "const app = express();\n\n");

    // Use CORS middleware for cross-origin requests
    fprintf(file, "app.use(cors());\n\n");

    // Use bodyParser middleware for parsing JSON and URL-encoded data
    fprintf(file, "app.use(bodyParser.json());\n");
    fprintf(file, "app.use(bodyParser.urlencoded({ extended: true }));\n\n");

    // Use Morgan middleware for logging HTTP requests
    fprintf(file, "app.use(morgan('dev'));\n\n");

    // Define a default route
    fprintf(file, "app.get('/', (req, res) => {\n");
    fprintf(file, "    res.send('Hello, World!');\n");
    fprintf(file, "});\n\n");

    // Start the server
    fprintf(file, "const PORT = process.env.PORT || 3000;\n");
    fprintf(file, "app.listen(PORT, () => {\n");
    fprintf(file, "    console.log(`Server is running on port ${PORT}`);\n");
    fprintf(file, "});\n");

    fclose(file);


    file = fopen("config/db.js", "w");
    if (file == NULL) {
        printf("Error: Failed to create db.js file.\n");
        return 1;
    }
    fprintf(file, "// db.js file\n\n");
    fclose(file);

    file = fopen("../.env", "w");
    if (file == NULL) {
        printf("Error: Failed to create .env file.\n");
        return 1;
    }
    fprintf(file, "// .env file\n\n");
    fclose(file);


    printf("Folder setup completed successfully.\n");

    return 0;
}