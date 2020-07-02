#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *key;
    char *expression;
    float value;

} object;

typedef struct
{
    object* obj[10];
    int counter;
} objects;

object* constructObject(char *key,char *expression)
{
    object *o=malloc(sizeof(object));
    o->key=malloc(strlen(key)+1);
    o->expression=malloc(strlen(expression)+1);
    strcpy(o->key,key);
    strcpy(o->expression,expression);
    return o;
}

objects* constructObjects()
{
    objects *o=malloc(sizeof(objects));
    o->counter=0;
    return o;
}


void manageSpaces(char *expression){

int i,j;
char spaces[1024];
for(i=0,j=0;i<strlen(expression);i++)
{
    if(expression[i]=='-')
    {
        if(spaces[j-2]=='-'||spaces[j-2]=='+'||spaces[j-2]=='*'||spaces[j-2]=='/'||spaces[j-2]=='^')
        {
            spaces[j++]=expression[i];
        }
        else if(spaces[j-2]==')'||isdigit(spaces[j-2])||((spaces[j-2] >= 'a' && spaces[j-2] <= 'z') || (spaces[j-2] >= 'A' && spaces[j-2] <= 'Z')))
        {
             spaces[j++]=expression[i];
             spaces[j++]=' ';

        }

    }
     else  if(expression[i]!=' ')
    {
        if(expression[i]=='.')
        {
            spaces[j++]=expression[i];
        }
       else if((isdigit(expression[i])&&(isdigit(expression[i+1])||expression[i+1]=='.'))||(isdigit(expression[i])&&(isdigit(expression[i+1])||expression[i+1]=='.')&&(isdigit(expression[i-1])||expression[i-1]=='.')))
        {
            spaces[j++]=expression[i];
        }
        else
        {
            spaces[j++]=expression[i];
            spaces[j++]=' ';
        }
     }
    }
        spaces[j]=NULL;
       strcpy(expression,spaces);
}





typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/
typedef struct
{
    Item *data;
    int topp;


} Stack;
/*
*
*/
Stack * initialize(int size)
{
    Stack*s=malloc(sizeof(Stack));
    s->data=malloc(size*4);
    s->topp=0;

    return s;
}
/*
*
*/
int isEmpty(Stack *s)
{
    return s->topp==0;
}
/*
*
*/
Item top(Stack *s)
{
    return s->data[s->topp-1];
}

/*
*
*/
Item pop(Stack *s)
{

    return s->data[--s->topp];
}

/*
*
*/
void push(Stack *s, Item val)
{

    s->data[s->topp++]=val;

}
void pushch(Stack *s,char l)
{
    Item x;
    x.cData=l;
    s->data[s->topp++]=x;
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22+31 --> 22 31 +
* e.g., (2+3)*4 --> 2 3 + 4 *
*/
int precedance(char c)
{
    if(c=='^')
        return 2;
    if(c=='*'||c=='/'||c=='%')
        return 1;
    if(c=='+'||c=='-')
        return 0;
    if(c=='(')
        return -1;
    if(c==')')
        return -2;
}
void infixToPostfix(char* infix, char* postfix)
{
    int s;
    Stack* post;
    post=initialize(strlen(infix)+1);
    char temp;
    int i=0;
    int j=0;

    for(i=0,j=0; i<strlen(infix)-1; i++,j++)
    {
        if(isdigit(infix[i])||infix[i]=='.'||(infix[i]=='-'&&isdigit(infix[i+1]))||isalpha(infix[i]))
        {

         postfix[j]=infix[i];

        }
        else if(infix[i]==' ')
        {
         j--;
        continue;
        }
        else
        {
           if(postfix[j-1]!=' ') postfix[j++]=' ';


            if(isEmpty(post))
            {
                pushch(post,infix[i]);
                j--;
            }

            else
            {
                if(precedance(infix[i])==-1)
                {
                j--;
                    pushch(post,infix[i]);
                }
                else if((precedance(infix[i])>=1)&&(precedance(top(post).cData)==0))
                {
                    j--;
                    pushch(post,infix[i]);

                }
                else if((precedance(infix[i])==1)&&(precedance(top(post).cData)==1))
                {

                    postfix[j++]=pop(post).cData;
                    postfix[j]=' ';
                    pushch(post,infix[i]);
                }
                 else if((precedance(infix[i])==1)&&(precedance(top(post).cData)==2))
                 {

                    postfix[j++]=pop(post).cData;
                   //if(postfix[j-1]!=' ') postfix[j]=' ';
                    pushch(post,infix[i]);
                 }
                else if(precedance(infix[i])==0&&precedance(top(post).cData)==0)
                {
                    postfix[j++]=pop(post).cData;
                    postfix[j]=' ';
                    pushch(post,infix[i]);

                }
                else if(precedance(infix[i])==0&&precedance(top(post).cData)>=1)
                {
                    i--;
                    postfix[j++]=pop(post).cData;
                    postfix[j]=' ';

                }
                else if((precedance(infix[i])>=0)&&precedance(top(post).cData)==-1)
                {
                    pushch(post,infix[i]);
                    j--;
                }
                else if(precedance(infix[i])==2){

                    pushch(post,infix[i]);
                    j--;
                }
                else if(precedance(infix[i])==-2)
                {

                    while(top(post).cData!='(')
                    {
                        postfix[j++]=pop(post).cData;
                       // printf("postfix[j]= %c \n",postfix[j]);
                        postfix[j]=' ';
                    }
                    pop(post);
                    j--;
                }


            }


        }


    }

     if(postfix[j-1]!=' ') postfix[j++]=' ';
    while(!isEmpty(post)){
    postfix[j++]=pop(post).cData;
    postfix[j++]=' ';
    }
    postfix[j-1]=NULL;



     free(post->data);
    free(post);
}
/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
* ASSUME single-digit operands
*/
double findMod(double a, double b)
{
    double mod;
    // Handling negative values
    if (a < 0)
        mod = -a;
    else
        mod =  a;
    if (b < 0)
        b = -b;

    // Finding mod by repeated subtraction

    while (mod >= b)
        mod = mod - b;

    // Sign of result typically depends
    // on sign of a.
    if (a < 0)
        return -mod;

    return mod;
}

long double mypow(long double v, long double p)
{


    return pow(v,p);
}
float evaluatePostfix(char* postfix,objects* objs)
{
    strcat(postfix," ");
Stack *s=initialize(strlen(postfix));
char pt[4];
int j=0,i;
Item x;
float temp1,temp2;
object temp3;
int l=0;
for(i=0;i<strlen(postfix);i++,j++)
{
    if(postfix[i]!=' ')
    {
    pt[j]=postfix[i];
    //printf("j=%d i=%d pt[j]=%c\n",j,i,pt[j]);
    }
    else
    {
        pt[j]=NULL;
        j=-1;
        if(isdigit(pt[0])||isdigit(pt[1]))
        {
        x.fData=atof(pt);
        push(s,x);
      // printf("%f\n",x.fData);
        }
        else if(isalpha(pt[0])||isalpha(pt[1]))
        {
           while(l<objs->counter)
           {
                if(strcmp(pt,objs->obj[l]->key)==0)
                {
                    x.fData=objs->obj[l]->value;
                    push(s,x);
                    l=0;
                    break;
                }
                l++;
           }
        }
        else
        {
        if(pt[0]=='+')
            {temp1=pop(s).fData;
             temp2=pop(s).fData;
             x.fData=temp1+temp2;
             push(s,x);
            }
        else if(pt[0]=='-')
            {temp2=pop(s).fData;
             temp1=pop(s).fData;
             x.fData=temp1-temp2;
             push(s,x);
            }
        else if(pt[0]=='*')
            {temp1=pop(s).fData;
             temp2=pop(s).fData;
             x.fData=temp1*temp2;
             push(s,x);
            }
        else if(pt[0]=='/')
            {temp2=pop(s).fData;
             temp1=pop(s).fData;
             x.fData=temp1/temp2;
             push(s,x);
            }
        else if(pt[0]=='%')
            {temp2=pop(s).fData;
             temp1=pop(s).fData;
             x.fData=findMod(temp1,temp2);
             push(s,x);
            }
        else if(pt[0]=='^')
            {temp1=pop(s).fData;
             temp2=pop(s).fData;
             x.fData=mypow(temp2,temp1);
             push(s,x);
            }
        }
    }
}
x.fData=pop(s).fData;
free(s->data);
free(s);


    return x.fData;
}
/*
*
*/




//====================================================================================================================================
//===========================trees================================================================================================

typedef struct Node
{
    object *obj;
    struct Node* left;
    struct Node* right;
} Node;


Node* newNode(object *w)
{
    Node *n=malloc(sizeof(Node));
    n->obj=w;
    n->left=NULL;
    n->right=NULL;
}


Node* insertsa(Node* node, object *w)
{
    if (node == NULL)
        return newNode(w);
    if (strcasecmp(w->key,node->obj->key)<0)
        node->left = insertsa(node->left, w);
    else if (strcasecmp(w->key,node->obj->key)>0)
        node->right = insertsa(node->right, w);
    return node;
}

void InOrdertraverse(Node *t)
{

if (t!=NULL)
{

InOrdertraverse(t->left);
printf("%s=%f\n",t->obj->key,t->obj->value);
InOrdertraverse(t->right);

}

}



void extractData(objects *objs,Node *root,char *filename)
{
    FILE *fptr=fopen(filename,"r");
    char *token,buffer[1024],tempkey[1024],tempexp[1024];

    while(!feof(fptr))
    {

        fscanf(fptr,"%[^\n]\n",buffer);
        token=strtok(buffer,"=");
        strcpy(tempkey,token);
        token=strtok(NULL,"=");
        strcpy(tempexp,token);
        manageSpaces(tempkey);
        tempkey[strlen(tempkey)-1]=NULL;
        if(addToObjects(root,objs,tempkey,tempexp))
        {
        objs->obj[objs->counter]=constructObject(tempkey,tempexp);
        manageSpaces(objs->obj[objs->counter]->expression);
        infixToPostfix(objs->obj[objs->counter]->expression,objs->obj[objs->counter]->expression);
        objs->obj[objs->counter]->value=evaluatePostfix(objs->obj[objs->counter]->expression,objs);

        root=insertsa(root,objs->obj[objs->counter++]);
        }
    }






        InOrdertraverse(root);

    fclose(fptr);
}



int addToObjects(Node *root,objects *objs,char *tempkey,char *tempexp)
{
   int j;
   for(j=0;j<objs->counter;j++)
    {

        if(strcmp(tempkey,objs->obj[j]->key)==0)
        {
            strcpy(objs->obj[j]->expression,tempexp);
            manageSpaces(objs->obj[j]->expression);
            infixToPostfix(objs->obj[j]->expression,objs->obj[j]->expression);
            objs->obj[j]->value=evaluatePostfix(objs->obj[j]->expression,objs);
            return 0;
        }
    }



    return 1;
}





//<-----------------------------------------THIS IS HEAP PART------------------------------------------------------->>
// --------------------------------------------
int leftChild(int index){
return 2*index;
}
int rightChild(int index){
return leftChild(index)+1;
}

void bottomUp(objects * heapArr,int elementsNum){
int counter;
for(counter=elementsNum/2;counter>=1;counter--){
  maxHeapify(heapArr,counter,elementsNum);
}
}



void maxHeapify(objects * heapArr,int index,int elementsNum){
int l=leftChild(index);
int r=rightChild(index);
int largest;
int n = elementsNum;
if(l<=n&& heapArr->obj[l]->value >  heapArr->obj[index]->value){
   largest=l;
}
else{
    largest=index;
}
if(r<=n&&heapArr->obj[r]->value >heapArr->obj[largest]->value){
    largest=r;
}
if(largest!=index){
   exchangeTwoIndex(heapArr,index,largest);
    maxHeapify(heapArr,largest,n);
}



}



void exchangeTwoIndex(objects * arr,int indexOne,int indexTwo){
 object* tempo;
tempo=arr->obj[indexOne];
arr->obj[indexOne]=arr->obj[indexTwo];
arr->obj[indexTwo]=tempo;
}


void heapSort(objects * obj,objects * heapArr,int elementsNum){
copyToHeapArr(obj,heapArr);
bottomUp(heapArr,obj->counter);
int n=elementsNum;
int counter;
//printf("Sorted By Value :\n");
for(counter=n;counter>=1;counter--){
   if(counter==1) {
   // printf("%s  =   %f\n",heapArr->obj[1]->key,heapArr->obj[1]->value);  //this condition to check that if only one node left after deletion of all nodes to print it directly as no need for further operation
   }
   else{
    exchangeTwoIndex(heapArr,1,counter);  //exchange last node with root node which is largest node
  //  printf("%s  =   %f\n",heapArr->obj[counter]->key,heapArr->obj[counter]->value); // print largest value at last node after exchange
    bottomUp(heapArr,counter-1);  //counter -1 as we delete last elements which was the largest as no need for it again
    //so size is decreased by one ,as we have 8 elements to sort if intial input was 9


   }

}
printHeapArr(heapArr,obj->counter);
freeHeapArr(heapArr,obj->counter);
}

// -----------------------------------------------------------------------------


object* constructHeapObject(char *key,float value)
{
    object *o=malloc(sizeof(object));
    o->key=malloc(strlen(key)+1);
    o->value=value;
    strcpy(o->key,key);
    return o;
}

void copyToHeapArr(objects *objs,objects *heapArr){
int counterOne=0;
int counterTwo;
int arrSize=objs->counter;
for(counterOne=0,counterTwo=1;counterOne<arrSize;counterOne++,counterTwo++){
 heapArr->obj[counterTwo]=constructHeapObject(objs->obj[counterOne]->key,objs->obj[counterOne]->value);



}






}


void printHeapArr(objects*heapArr,int elementsNum){
int counter ;
printf("Sorted By Value :\n");

for(counter=1;counter<=elementsNum;counter++){
    printf("%s=%f\n",heapArr->obj[counter]->key,heapArr->obj[counter]->value);


}
printf("End Of Sorting");







}

void freeHeapArr(objects *heapArr,int elementsNum){
int counter=1;
for(;counter<=elementsNum;counter++){
    free(heapArr->obj[counter]);
}

}



