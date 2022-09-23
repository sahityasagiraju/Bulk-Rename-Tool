#include "header.h"

/*
Works in combination with stringGenerate function.
Parameters
s - String key
len- length of string
str- Queue to which the String should be enqueued
choice - 1 represents alphabetic key and 2 represents numeric key
n - Number of strings that need to be generated
position - the start position of the # in the String
end_position - the end position of the # in the String
*/
void generator(char *s, Queue* str,int choice, size_t*n,int position,int end_position)
{
    if(n==NULL||s==NULL||str==NULL)
    {
        return;
    }

    if(position>strlen(s)||end_position>strlen(s)||position<0||end_position<0)
    {
       return;
    }

    if((*n) == 0)
    {
        return;
    }

    int counter = choice==1?26:10;
    if(position==end_position+1)
    {

        enQueue(str,s);
        (*n)--;
        return;
    }
    int i;
    char c=choice==1?'A':'0';
    for(i=0;i<counter;i++)
    {
        s[position]=(char)(c+i);
        generator(s,str,choice,n,position+1,end_position);
    }
}


/*
A function that generates all string permutations needed
The parameters
s - String key
len- length of string
str- Queue to which the String should be enqueued
choice - 1 represents alphabetic key and 2 represents numeric key
n - Number of strings that need to be generated
returns 1 if strings can be generated
*/
int stringGenerate(char *s,Queue* str,int choice, size_t*n)
{
    if(s==NULL||str==NULL||n==NULL||(*n)==0)
    {
        return 0;
    }

    size_t len=strlen(s);
    int position=-1,end_position=-1;
    size_t count=0;
    int check=verifyString(s,len,&count,&position,&end_position);

    if(check==0)
    {
        return 0;
    }
    char* s_temp=(char*)malloc(len+1);

    if(s_temp==NULL)
    {
        return 0;
    }
    int ret=snprintf(s_temp,len+1,"%s",s);
    if(ret<0||ret>=len+1)
    {
        free(s_temp);
        return 0;
    }
    generator(s_temp,str,choice,n,position,end_position);
    free(s_temp);
    return 1;

}


/*
Verifies if the string is a perfect key and has a # for which string combinations can be generated
Parameters
s - String key
len- length of string
count - Pointer to int memory which stores the number of # in the String
position - Pointer to int memory which stores the initial start index position of # in the String
end_position - Pointer to int memory which stores the end position index of the # in the String
Returns 1 if the String is a perfect key
*/
int verifyString(char* s,size_t len, size_t* count, int* position, int* end_position)
{
    if(s==NULL||count==NULL||position==NULL||end_position==NULL||len==0)
    {
        return 0;
    }

    if(len>255)
    {
        return 0;
    }

    (*count)=0;
    *position = -1;
    (*end_position)=-1;
    int pos =-1;
    size_t i;
    for(i=0;i<len;i++)
    {
        if(s[i]=='#')
        {
            pos=i;
            break;
        }
    }
    if(pos==-1)
    {
        return 0;
    }
    (*position) = pos;

    for(i=pos;i<len;i++)
    {
        if(s[i]!='#')
        {
            pos=i;
            (*end_position)=pos-1;
            break;
        }
        else if(i==len-1)
        {
            *count++;
            pos=i;
            (*end_position)=pos;
            break;
        }
        else
        {
            (*count)++;
        }
    }

    for(i=pos+1;i<len;i++)
    {
        if(s[i]=='#')
        {
            (*count)=0;
            (*position) = -1;
            (*end_position)=-1;
            return 0;
        }
    }
    return 1;
}
