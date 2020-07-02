#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SomeStructure.h"
#include "validation.h"



int main()
{
    //project start===========================================================================================

    FILE *fptr;
    char filename[260];
    objects* obj=constructObjects();
    objects* heapArr=constructObjects();
    Node *root=NULL;

    printf("Enter filename\n");
       puts("----------------------------------");
    if(fgets(filename, 260, stdin)!=NULL ){

        filename[strlen(filename)-1]='\0';
        fptr=fopen(filename,"r");
        if(fptr)
        {
            fclose(fptr);
            if(verify(filename)>0)
            {printf("please fix the wrong expressions and try again");exit(0);}
            extractData(obj,root,filename);

         //  copyToHeapArr(obj,heapArr);
        //   printf("%s \t %f",heapArr->obj[1]->key,heapArr->obj[1]->value);
//copyArr(arr,heapArr,size); //copy not sorted array into other array to preform operations on
    //bottomUp(heapArr,obj->counter); // intial heapify operation to make valid heap tree
   heapSort(obj,heapArr,obj->counter); //sorting first call needs a the intial full number of elemnts
//printHeapArr(heapArr,obj->counter);

        }
        else
        {
            puts("File Not Found!\n");
            puts("----------------------------------\n");
        }
    }
//project end===========================================================================================



    return 0;

}






