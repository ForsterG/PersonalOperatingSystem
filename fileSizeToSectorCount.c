#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    if( argc == 3 ) 
    {
      printf("The argument supplied is %s\n", argv[1]);
   }
   else if( argc > 3 ) {
      printf("Form Needed: %s inputFile outputFile\n", argv[0]);
   }
   else {
      printf("Three arguments expected.\n");
      return 0;
   }

   FILE *fp;
   char buff[255];
   int size;

   fp = fopen(argv[1], "r"); // open the file
   if(fp == NULL)
   {
    printf("ERROR on file pointer");
   }
   fscanf(fp, "%s", buff);
   size = atoi(buff);
   printf("Read In Size(int): %i\n", size);
   double sizeDouble = (double) size;
   printf("Read In Size(double): %f\n", sizeDouble);
   double sizeinsectors = sizeDouble / 512.0;
   printf("Number of Sectors(double): %f\n", sizeinsectors);
    double x = sizeDouble;
    double y = 512;
   double q = 1 + ((x - 1) / y); // if x != 0, ceil is not working correctly at the moment
   printf("Number of Total Sectors:%f\n", q);

    fclose(fp); // close the file
   FILE *wp;
   wp = fopen(argv[2], "w+"); // open the file
   if(wp == NULL)
   {
    printf("ERROR on file pointer");
   }
   fprintf(wp, "%i", (int)q);
   fclose(wp);
    return 0;
}