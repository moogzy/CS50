#include <stdio.h>
#include <stdlib.h>


int main()
{
   char str1[10], str2[10], str3[10];
   int year = 0;
   int index = 0;
   FILE * fp;

   fp = fopen ("file.txt", "w+");
   fputs("We are in 2012", fp);
   
   rewind(fp);
   for(char *str = fscanf(fp, "%s", str); str != EOF; char *str = fscanf(fp, "%s", str))
   {
       index++;
       printf("Read String%i |%s|\n", index, str);
   }
   //fscanf(fp, "%s", str1);
   //fscanf(fp, "%s", str2);
   //fscanf(fp, "%s", str3);
   
   //printf("Read String1 |%s|\n", str1 );
   //printf("Read String2 |%s|\n", str2 );
   //printf("Read String3 |%s|\n", str3 );
   //printf("Read Integer |%d|\n", year );

   fclose(fp);
   
   return(0);
}