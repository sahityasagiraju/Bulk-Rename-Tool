#include "header.h"

void display(Queue* q)
{
    if(q==NULL)
    {
        printf("Queue is not created\n");
    }
    QNode* temp=q->front;
    if(temp==NULL)
    {
        printf("Nothing in Queue\n");
    }
    else
    {
        while(temp!=NULL)
        {
            printf("%s\n",temp->data);
            temp=temp->next;
        }
    }

}

int inputDirectory(char* msg,char** path)
{
    if(msg==NULL||path==NULL)
    {
        printf("\nError handling memory! Restart the program\n");
        *path=NULL;
        return 0;
    }

    int ch,i;
    size_t chars_read;
    int flag=0;

    *path=(char*)malloc(261);
    if(*path==NULL)
    {
        printf("\nError handling memory! Restart the program\n");
        return 0;
    }

    while(flag==0)
    {
        printf("\n%s\n",msg);

        i=0;
        chars_read=0;
        while((ch=getchar())!='\n'&&ch!=EOF)
        {
            if(i<259)
                (*path)[i++]=(char)ch;
            chars_read++;
        }
        (*path)[i]='\0';

        if(feof(stdin)||ch==EOF)
        {
            free(*path);
            printf("\nThe Source path has unrecognizable characters!\n");
            return 0;
        }
        else if(ferror(stdin))
        {
            printf("\nError occured! Please restart the code!\n");
            free(*path);
            return 0;
        }

        if(chars_read>i)
        {
            printf("\nThe Source path can only be 260 characters!\nCharacters typed after 260 are discarded\n");
        }

        flag=isDirectoryExists(*path);
        if(flag==0)
        {
            printf("\nThe entered directory is invalid\n");
        }
    }

    if((*path)[strlen(*path)-1]!='/')
    {
        int len=strlen(*path);
        (*path)[len]='/';
        (*path)[len+1]='\0';
    }
    return 1;
}

int inputString(char* msg,char** name)
{
    if(msg==NULL||name==NULL)
    {
        printf("\nError handling memory! Restart the program\n");
        (*name)=NULL;
        return 0;
    }

    int ch,i;
    size_t chars_read;
    int flag=0;

    (*name)=(char*)malloc(257);
    if((*name)==NULL)
    {
        printf("\nError handling memory! Restart the program\n");
        return 0;
    }

    while(flag==0)
    {
        printf("\n%s\n",msg);

        i=0;
        chars_read=0;

        while((ch=getchar())!='\n'&&ch!=EOF)
        {
            if(i<256)
            {
                (*name)[i++]=(char)ch;
            }
            chars_read++;
        }
        (*name)[i]='\0';

        if(feof(stdin)||ch==EOF)
        {
            free(*name);
            printf("The String has unrecognizable characters!\n");
            return 0;
        }
        else if(ferror(stdin))
        {
            free(*name);
            printf("Error occured! Please restart the code!\n");
            return 0;
        }

        if(chars_read>i)
        {
            printf("The String can only be 256 characters!\nCharacters typed after 256 are discarded\n");
        }

        size_t count=0;
        int position=-1,end_position=-1;
        flag=verifyString(*name,strlen(*name),&count,&position,&end_position);
        if(flag==0)
        {
            printf("\nThe entered String is invalid\n");
        }
    }
    return 1;
}


int inputChoice(char* msg,int* res)
{
    if(msg==NULL||res==NULL)
    {
         printf("\nError handling memory! Restart the program\n");
         return 0;
    }

    (*res)=0;
    int flag=1,flag_ch,choice=0,ch;
    while(flag)
    {
        flag_ch=1;

        printf("\n%s\n",msg);

        while(((ch=getchar())=='\n')&&ch!=EOF);
        choice=ch;
        ch=getchar();
        if(ch!='\n')
        flag_ch=0;
        while(ch!=EOF&&ch!='\n'&&(ch=getchar())!='\n');

        if(feof(stdin)||ch==EOF)
        {
            printf("The choice entered has unrecognizable characters!\n");
            return 0;
        }
        else if(ferror(stdin))
        {
            printf("Error occured! Please restart the code!\n");
            return 0;
        }

        if((choice==(int)'1'||choice==(int)'2')&&flag_ch==1)
        {
            flag=0;
        }
        else
        {
            printf("The entered choice is invalid\n");
        }

    }
    (*res)=(choice==(int)'1')?1:2;
    return 1;
}

int inputYesOrNo(char* msg,int* res)
{
    if(msg==NULL||res==NULL)
    {
        printf("\nError handling memory! Restart the program\n");
        return 0;
    }

    (*res)=0;
    int flag=1,flag_ch,choice,ch;
    while(flag)
    {
        flag_ch=1;

        printf("\n%s\n",msg);

        while(((ch=getchar())=='\n')&&ch!=EOF);
        choice=ch;
        ch=getchar();
        if(ch!='\n')
        {
           flag_ch=0;
        }
        while(ch!=EOF&&ch!='\n'&&(ch=getchar())!='\n');

        if(feof(stdin)||ch==EOF)
        {
            printf("The choice entered has unrecognizable characters!\n");
            return 0;
        }
        else if(ferror(stdin))
        {
            printf("Error occured! Please restart the code!\n");
            return 0;
        }

        if((choice==(int)'y'||choice==(int)'Y'||choice==(int)'N'||choice==(int)'n')&&flag_ch==1)
        {
            flag=0;
        }
        else
        {
            printf("The entered choice is invalid\n");
        }
   }
   (*res)=(choice==(int)'Y'||choice==(int)'y')?1:0;
   return 1;
}

void freeData(char* source_path,char* name,char* dest_path,char* s_new,Queue* str,Queue* files)
{
    if(source_path!=NULL)
    {
        free(source_path);
    }
    if(name!=NULL)
    {
        free(name);
    }
    if(dest_path!=NULL)
    {
        free(dest_path);
    }
    if(s_new!=NULL)
    {
        free(s_new);
    }
    if(str!=NULL)
    {
        deleteQueue(str);
    }
    if(files!=NULL)
    {
        deleteQueue(files);
    }
}

int main(void)
{
    int choice,choice_copy,choice_yn,ret,choice_move;
    size_t n;
    char *source_path,*name,*dest_path,*ext;
    char* f_path,*s_temp;
    Queue *files,*str;
    printf("\n\nBulk Rename Tool\n\n");

    source_path=NULL;
    if(inputDirectory("Enter the source directory",&source_path)==0)
    {
        printf("\nExiting!\n");
        return 0;
    }

    name=NULL;
    if(inputString("Enter the String\nThe Key should be entered as #\nEg.My_File##\n",&name)==0)
    {
        freeData(source_path,NULL,NULL,NULL,NULL,NULL);
        printf("\nExiting!\n");
        return 0;
    }

    choice=0;
    if(inputChoice("Enter the choice\n Enter 1 for Alphabetic Key\n Enter 2 for Numeric Key",&choice)==0)
    {
        freeData(source_path,name,NULL,NULL,NULL,NULL);
        printf("\nExiting!\n");
        return 0;
    }

    choice_copy=0;
    if(inputYesOrNo("Make a copy of all the files in a different directory? (Y/N)",&choice_copy)==0)
    {
        freeData(source_path,name,NULL,NULL,NULL,NULL);
        printf("\nExiting!\n");
        return 0;
    }

    str=createQueue();
    files=createQueue();
    n=0;
    if(findAllFiles(source_path,files,&n)==0)
    {
        freeData(source_path,name,NULL,NULL,str,files);
        printf("Cannot open the source directory!\n");
        return 0;
    }

    //display(files);

    if(n==0)
    {
        freeData(source_path,name,NULL,NULL,str,files);
        printf("Source Folder empty!!!\n!");
        return 0;
    }
    if(stringGenerate(name,str,choice,&n)==0)
    {
        freeData(source_path,name,NULL,NULL,str,files);
        printf("Please restart the program. Cannot generate the file names!.");
        return 0;
    }

    //display(str);



    dest_path=NULL;
    if(choice_copy)
    {
        if(inputDirectory("Enter the destination directory",&dest_path)==0)
        {
            freeData(source_path,name,NULL,NULL,str,files);
            printf("\nExiting!\n");
            return 0;
        }
        if(strcmp(source_path,dest_path)==0)
        {
            printf("The source and destination directories are the same!!\nA copy of the existing file with the new name will be created in the same directory\n");
        }

        while(isempty(files)==0&&isempty(str)==0)
        {
            f_path=files->front->data;

            if(isDirectoryExists(f_path))
            {
                printf("\n%s is a sub directory! Skipping to the next\n",f_path);
                if(deQueue(files)==0)
                {
                    freeData(source_path,name,dest_path,NULL,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
                continue;
            }

            ext=get_filename_ext(f_path);

            if(strcmp(ext,".txt")!=0)
            {
                printf("\n%s is not a txt file! Skipping to the next\n",f_path);
                if(deQueue(files)==0)
                {
                    freeData(source_path,name,dest_path,NULL,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
                continue;
            }

            s_temp=str->front->data;

            char msg[300];
            ret=snprintf(msg,sizeof(msg),"\nCopy %s to %s%s%s? (Y/N)\n",f_path,dest_path,s_temp,ext);
            if(ret<0||ret>=sizeof(msg))
            {
                freeData(source_path,name,dest_path,NULL,str,files);
                printf("\nError handling memory! Restart the program\n");
                return 0;
            }

            choice_yn=0;
            if(inputYesOrNo(msg,&choice_yn)==0)
            {
                printf("\nExiting!\n");
                freeData(source_path,name,dest_path,NULL,str,files);
                return 0;
            }
            if(choice_yn==1)
            {
                size_t len= strlen(dest_path)+strlen(s_temp)+strlen(ext)+1;
                char* s_new=(char*)malloc(len);
                if(s_new==NULL)
                {
                    freeData(source_path,name,dest_path,NULL,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
                ret=snprintf(s_new,len,"%s%s%s",dest_path,s_temp,ext);
                if(ret<0||ret>=len)
                {
                    freeData(source_path,name,dest_path,s_new,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }

                int res=copy_files(f_path,s_new);
                if(res==1)
                {
                    printf("\nSuccessful!\n");
                }
                else if(res==2)
                {
                    printf("\nFile with path %s already exists! Cannot rewrite\n",s_new);
                }
                else
                {
                    printf("\nNot Successful!\n");
                }
                if(deQueue(str)==0)
                {
                    freeData(source_path,name,dest_path,s_new,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
                free(s_new);
            }
            else
            {
                printf("\nSkipping to the next!\n");
            }
            if(deQueue(files)==0)
            {
                freeData(source_path,name,dest_path,NULL,str,files);
                printf("\nError handling memory! Restart the program\n");
                return 0;
            }
        }
    }


    else
    {

        choice_move=0;
        if(inputYesOrNo("\nMove the files and rename in a different directory? (Y/N)",&choice_move)==0)
        {
            freeData(source_path,name,NULL,NULL,str,files);
            printf("\nExiting!\n");
            return 0;
        }

        if(choice_move)
        {
            if(inputDirectory("\nEnter the destination directory",&dest_path)==0)
            {
                freeData(source_path,name,NULL,NULL,str,files);
                printf("\nExiting!\n");
                return 0;
            }
            if(strcmp(dest_path,source_path)==0)
            {
                printf("\nSince the destination directory is same as source all the files in the directory will just be renamed\n");
            }
        }
        else
        {
            dest_path=(char*)malloc(strlen(source_path)+1);
            if(dest_path==NULL)
            {
                freeData(source_path,name,NULL,NULL,str,files);
                printf("\nError handling memory! Restart the program\n");
                return 0;
            }
            ret=snprintf(dest_path,strlen(source_path)+1,"%s",source_path);
            if(ret<0||ret>=strlen(source_path)+1)
            {
                freeData(source_path,name,dest_path,NULL,str,files);
                printf("\nError handling memory! Restart the program\n");
                return 0;
            }
        }

        while(isempty(files)==0&&isempty(str)==0)
        {

            f_path=files->front->data;
            if(isDirectoryExists(f_path))
            {
                printf("\n%s is a sub directory! Skipping to the next\n",f_path);
                if(deQueue(files)==0)
                {
                    freeData(source_path,name,dest_path,NULL,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
                continue;
            }

            ext=get_filename_ext(f_path);
            s_temp=str->front->data;

            char msg[300];
            ret=snprintf(msg,sizeof(msg),"\nChange %s to %s%s%s? (Y/N)\n",f_path,dest_path,s_temp,ext);
            if(ret<0||ret>=sizeof(msg))
            {
                freeData(source_path,name,dest_path,NULL,str,files);
                printf("\nError handling memory! Restart the program\n");
                return 0;
            }

            choice_yn=0;
            if(inputYesOrNo(msg,&choice_yn)==0)
            {
                freeData(source_path,name,dest_path,NULL,str,files);
                printf("\nExiting!\n");
                return 0;
            }

            if(choice_yn)
            {
                size_t len=strlen(dest_path)+strlen(s_temp)+strlen(ext)+1;
                char* s_new=(char*)malloc(len);
                if(s_new==NULL)
                {
                    freeData(source_path,name,dest_path,NULL,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
                ret=snprintf(s_new,len,"%s%s%s",dest_path,s_temp,ext);
                if(ret<0||ret>=len)
                {
                    freeData(source_path,name,dest_path,s_new,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
                if(rename_file(f_path,s_new))
                {
                    printf("\nSuccessful!\n");
                }
                else
                {
                    printf("\nNot Successful!\n");
                }
                free(s_new);
                if(deQueue(str)==0)
                {
                    freeData(source_path,name,dest_path,NULL,str,files);
                    printf("\nError handling memory! Restart the program\n");
                    return 0;
                }
            }
            else
            {
                printf("\nSkipping to the next\n");
            }
            if(deQueue(files)==0)
            {
                freeData(source_path,name,dest_path,NULL,str,files);
                printf("\nError handling memory! Restart the program\n");
                return 0;
            }
        }
    }

    if(files->front==NULL)
    {
        printf("\nAll the files and directories in the directory have been dealt with!\n");
    }
    else if(str->front==NULL)
    {
        printf("\nThe key String given can only deal with so many files!\n");
    }

    freeData(source_path,name,dest_path,NULL,str,files);
    return 0;
}

