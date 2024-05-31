#include <stdio.h>
#define PI 3.14159
#include "functions.h"
#include <stdlib.h>
#include <string.h>


int main() {
   char* framework = initialize();
   printf("Your framework is: %s\n", framework);

   if (strcmp(framework, "ExpressJS") == 0) {
      if (initializeExpressApp() == 1) {
         printf("Error: Failed to initialize Express app.\n");
         return 1;
      }
   }

   return (0);
}