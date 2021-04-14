#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct node
{
    void* dataPtr;
    struct node* nextstep;
}
STACK_NODE;

typedef struct
{
    int count;
    STACK_NODE* up;
}
STACK;

STACK* createStack()
{
    STACK* stack;
    stack = (STACK*)malloc(sizeof(STACK));
    if(stack)
    {stack->count = 0;
        stack->up = NULL;
    }
    return stack;
}

bool pushStack(STACK* stack, void* dataInPtr)
{
    STACK_NODE* newPtr;
    newPtr = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    if(!newPtr)
        return false;

    newPtr->dataPtr = dataInPtr;
    newPtr->nextstep = stack->up;
    stack->up = newPtr;
    (stack->count)++;

    return true;
}

void* popStack(STACK* stack)
{
    void* dataOutPtr;
    STACK_NODE* temp;

    if(stack->count==0)
        dataOutPtr = NULL;
    else
    {
        temp = stack->up;
        dataOutPtr=stack->up->dataPtr;
        stack->up=stack->up->nextstep;
        free(temp);
        (stack->count)--;
    }
    return dataOutPtr;
}

bool emptyStack(STACK* stack)
{
    if(stack->count == 0)
        return true;

    return false;
}

bool Comp(char u,char c)
{
    if(u==40 && c==41 || u==123 && c==125)
        return false;
    return true;
}

bool Balance(char X[], size_t N)
{
    int i=0;
    char a='a';
    STACK* stack;
    stack = createStack();
    void* dataOutPtr;

    while(i!=N)
    {a=X[i];
        if(a==40 || a==41 || a==123 || a==125)
        {if(a=='{' || a=='(')
            {pushStack(stack,a);}
            else
            {if(a=='}' || a==')'){
                    if(emptyStack(stack)){
                        printf("\n(wrong! ^'_'^ )***** Eksik Parantez *****\n\n\n");
                        return false;}
                    else{
                        dataOutPtr = popStack(stack);
                        if(Comp(dataOutPtr,a)){
                            printf("\n(wrong! ^'_'^ )***** Eksik Parantez *****\n\n\n");
                            return false;}
                    }
                }
            }
        }
        i++;
    }
    if(emptyStack(stack))
    {
        printf("\n(wp! ^_^ ) ***** Parantez Eslesmelerinde Sorun Yok ***** \n\n\n");
        return true;
    }
    else{
        printf("\n(wrong! ^'_'^ )***** Eksik Parantez *****\n\n\n");
        return false;
        }
}
int main()
{
    char X[MAXSIZE];
    bool True=true;

    printf("Kontrol edilmesini istediginiz karakter dizinini giriniz: "); //Max size 100
    gets(X);

    True = Balance(X,strlen(X));
    if(True)
        printf("\nTrue!\n\n");
    else
        printf("\nFalse!\n\n");

    return 0;
}
