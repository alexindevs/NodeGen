#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "../functions.h"

int initializeExpressTSApp() {
    char project_name[400];

    printf("\nWhat do you want your app to be called? ");
    scanf("%399s", project_name);

    char working_directory[1024];
    if (getcwd(working_directory, sizeof(working_directory)) == NULL) {
        printf("Error: Could not get current working directory.\n");
        return 1;
    }

    printf("Creating Express-TypeScript Project %s in directory %s...\n", project_name, working_directory);

    char mkdir_command[512];
    sprintf(mkdir_command, "mkdir %s", project_name);
    system(mkdir_command);

    chdir(project_name);

    if (installDependencies() == 1) {
        printf("Error: Failed to install dependencies.\n");
        return 1;
    }
    char* sql_or_nosql = TSdatabaseSelection();
    if (sql_or_nosql == NULL) {
        printf("Error: Failed to select Database.\n");
        return 1;
    }
    free(sql_or_nosql);
    if (TSFolderSetup() == 1) {
        printf("Error: Failed to create folder structure.\n");
        return 1;
    }

    printf("Your project %s is ready to use!\n", project_name);
    printf("Run 'cd %s' to enter the project directory.\n", project_name);
    printf("Run 'npm start' to start the server.\n");
    printf("Happy coding!\n");


    return 0;
}

int installDependencies() {
    printf("Installing dependencies...\n");
    if (system("npm init -y") != 0) {
        printf("Error: Failed to install dependencies.\n");
        return 1;
    }
    if (system("npm install typescript -D") != 0) {
        printf("Error: Failed to install dependencies.\n");
        return 1;
    }
    if (system("npm install @types/node @types/express @types/body-parser @types/cors dotenv @types/bcrypt @types/jsonwebtoken jsonwebtoken bcrypt joi express cors body-parser winston @types/winston uuid") != 0) {
        printf("Error: Failed to install dependencies.\n");
        return 1;
    }

    return 0;
}

int TSFolderSetup() {
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

    FILE *file = fopen("server.ts", "w");
    if (file == NULL) {
        printf("Error: Failed to create server.ts file.\n");
        return 1;
    }

    fprintf(file, "import express from \"express\";\n");
    fprintf(file, "import bodyParser from \"body-parser\";\n");
    fprintf(file, "import cors from \"cors\";\n");
    fprintf(file, "import { config } from \"dotenv\";\n\n");

    fprintf(file, "config();\n\n");

    fprintf(file, "const app = express();\n");
    fprintf(file, "const port = process.env.PORT || 7000;\n\n");

    fprintf(file, "app.use(bodyParser.json());\n");
    fprintf(file, "app.use(cors());\n\n");

    fprintf(file, "app.get(\"/\", (req, res) => {\n");
    fprintf(file, "  res.send(\"Hello, World!\");\n");
    fprintf(file, "});\n\n");

    fprintf(file, "app.listen(port, () => {\n");
    fprintf(file, "  console.log(`Server is running on port ${port}`);\n");
    fprintf(file, "});\n");

    fclose(file);

    file = fopen("../tsconfig.json", "w");
    if (file == NULL) {
        printf("Error: Failed to create tsconfig.json file.\n");
        return 1;
    }

    fprintf(file, "{\n");
    fprintf(file, "  \"compilerOptions\": {\n");
    fprintf(file, "    \"target\": \"ES2020\",\n");
    fprintf(file, "    \"module\": \"commonjs\",\n");
    fprintf(file, "    \"outDir\": \"./dist\",\n");
    fprintf(file, "    \"strict\": true,\n");
    fprintf(file, "    \"esModuleInterop\": true,\n");
    fprintf(file, "    \"forceConsistentCasingInFileNames\": true,\n");
    fprintf(file, "    \"skipLibCheck\": true,\n");
    fprintf(file, "    \"resolveJsonModule\": true\n");
    fprintf(file, "  },\n");
    fprintf(file, "  \"include\": [\n");
    fprintf(file, "    \"./src/**/**/*.ts\",\n");
    fprintf(file, "    \"./src/**/*.ts\",\n");
    fprintf(file, "    \"src/server.ts\"\n");
    fprintf(file, "  ],\n");
    fprintf(file, "  \"exclude\": [\n");
    fprintf(file, "    \"./dist\"\n");
    fprintf(file, "  ]\n");
    fprintf(file, "}\n");

    fclose(file);

    file = fopen("../.env", "w");
    if (file == NULL) {
        printf("Error: Failed to create .env file.\n");
        return 1;
    }
    fprintf(file, "// .env file\n\n");
    fclose(file);

    printf("TypeScript project setup completed successfully.\n");

    chdir("..");
    return 0;
}

char* TSdatabaseSelection() {

    char* sql_or_nosql = (char*)malloc(20 * sizeof(char));
    printf("Will you be working with SQL or NoSQL? ");

    while (1) {
        scanf("%19s", sql_or_nosql);

        for (int i = 0; sql_or_nosql[i]; i++) {
            sql_or_nosql[i] = toupper(sql_or_nosql[i]);
        }

        if (strcmp(sql_or_nosql, "SQL") == 0) {
            printf("Installing SQL dependencies...\n");
            if (system("npm install mysql prisma; npx prisma init") != 0) {
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
