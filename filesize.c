// C program to find the size of file and calculate the number of sectors it will occupy
/*.PHONY: boot0.size Old Method
boot0.size:
	wc -c boot0.bin | awk '{if(NR==1) print $1}' > boot0.size
*/
#include <stdio.h>
unsigned long findSize(char file_name[]) 
{ 
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "r"); 
  
    // checking if the file exist or not 
    if (fp == NULL) 
    { 
        printf("%s Not Found!\n", file_name); 
        return -1; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
  
    // calculating the size of the file 
    unsigned long res = ftell(fp); 
  
    // closing the file 
    fclose(fp); 
  
    return res; 
} 

int writeSize(char file_name[], unsigned long length)
{
    FILE* fp = fopen(file_name, "w+");
    if (fp == NULL) { 
        printf("%s error creating \n", file_name); 
        return -1; 
    }
    int sectorsize = 512;
    double q;

    if(length > 0)
    {
        q = 1 + ((length - 1) / sectorsize);
    }
    else
    {
        q = 0;
    }
    
    fprintf(fp, "NumOfSectors: equ %i", (int)q);
    fclose(fp);
    return 0;
}

// Driver code 
int main(int argc, char *argv[]) 
{  
    if(argc < 3)
    {
        printf("Expecting two files\n ");
        return -1;
    }
    unsigned long res = findSize(argv[1]);
    int file; 
    if (res != -1)
    {
        //printf("Size of the file is %lu bytes \n", res);
        file = writeSize(argv[2], res);
    }
        
    return 0; 
} 






     

  

