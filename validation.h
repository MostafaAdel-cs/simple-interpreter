#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubleLinkedList.h"

int verify(char *filename)
{
    FILE *fptr=fopen(filename,"r");
    int i,k,l,z,flag,flag2,flag3,flag4=0;
    char *token,*r,buffer[1024],left[1024],right[1024],tempexp[1024];
    DoublyLinkedList* list=init();
    while(!feof(fptr))
    {
        i=0;
        fscanf(fptr,"%[^\n]\n",buffer);
        strcpy(tempexp,buffer);
        flag2=1;
        while(i<strlen(tempexp))
        {
            if(tempexp[i]=='=')
            {
                flag2=0;
            }
            i++;
        }
        if(flag2==1)
         {
             printf("%s is an invalid expression\n",tempexp);
             flag4++;
             continue;
             }
        token = strtok(buffer,"=");
        strcpy(left,token);
        i=0;
        while(i<strlen(left))
        {
            flag=1;
            if(left[i]>64 && left[i]<91 )
                flag=0;
            else if(left[i]>96 && left[i]<123)
                flag=0;
            else if(left[i]==32)
                flag=0;
            else
                break;
            i++;
        }
        if(flag==1)
        {
            printf("%s is an invalid expression\n",tempexp);
            flag2=0;
            flag4++;
        }
        token=strtok(NULL,"\n");
        strcpy(right,token);
        DoublyLinkedList *list=init();
        char* token=strtok(right," ");
        insert(list,token);
        Nodee* pt = list->head;
        int j=0;
        while(token)
        {
            if(j>0)
            {
                Nodee* temp=newNodee(token);
                pt->next=temp;
                temp->prev=pt;
                temp->next=NULL;
                pt=temp;
            }
            Nodee* null=newNodee("null");
            pt->next=null;
                null->prev=pt;
                null->next=NULL;
            token=strtok(NULL," ");
            j++;
        }
        pt=list->head;
        k=0,l=0,z=1;
        flag3=0;
        while(z<=length(list))
        {
            if(strcmp(pt->data,"(")==0)
                k++;
            if(strcmp(pt->data,")")==0)
                l++;
            if(l>k)
            {
                flag3=1;
            }
            if(strcmp(pt,"+")==0||strcmp(pt,"*")==0||strcmp(pt,"/")==0||strcmp(pt,"^")==0)
            {
                if(strcmp(pt->prev->data,"+")==0||strcmp(pt->prev->data,"*")==0||strcmp(pt->prev->data,"/")==0||strcmp(pt->prev->data,"-")==0||strcmp(pt->prev->data,"^")==0||strcmp(pt->prev->data,"null")==0||strcmp(pt->prev->data,"(")==0)
                    flag3=1;
                if(strcmp(pt->next->data,"+")==0||strcmp(pt->next->data,"*")==0||strcmp(pt->next->data,"/")==0||strcmp(pt->next->data,"^")==0||strcmp(pt->next->data,"null")==0||strcmp(pt->next->data,")")==0)
                    flag3=1;
            }
            else if(strcmp(pt,"-")==0)
            {
                if(strcmp(pt->next->data,"+")==0||strcmp(pt->next->data,"*")==0||strcmp(pt->next->data,"/")==0||strcmp(pt->next->data,"-")==0||strcmp(pt->next->data,"^")==0||strcmp(pt->next->data,"null")==0||strcmp(pt->next->data,")")==0)
                    flag3=1;
            }
            z++;
                pt=pt->next;
        }
        if(l!=k)
            flag3=1;
        if(flag3==1){
            printf("%s is an invalid expression\n",tempexp);
            flag4++;
        }
            destroy(list);
    }
        printf("\n");
        fclose(fptr);
        return(flag4);
}

