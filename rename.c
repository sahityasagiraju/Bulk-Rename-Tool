#include "header.h"

/*
Checks if the given path is directory or not
Returns 1 if the path is a directory
*/
int isDirectoryExists(char *path)
{
    if(path==NULL)
    {
        return 0;
    }

    struct stat stats;
    stat(path, &stats);

    if (S_ISDIR(stats.st_mode))
    {
        return 1;
    }

    return 0;
}

/*
Checks if the given path is file or not
Returns 1 if the path is a file
*/
int fileexists(char* filename)
{

    if(filename==NULL)
    {
        return 0;
    }

    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
Renames the file with a new name
Parameters
old_name - Path of file that needs to be renamed
new_name - The new name for the given file
Returns 1 if the renaming is successful
*/
int rename_file(char* old_name, char* new_name)
{
    if(old_name==NULL||new_name==NULL)
    {
        return 0;
    }

    if(strlen(old_name)==0||strlen(new_name)==0)
    {
        return 0;
    }

    int i=fileexists(old_name);
    if(i)
    {
        i=rename(old_name, new_name);
    }
    return (int)(i==0);

}


/*
Copies the file from source path to dest path
Parameters
source_file -Path of source file
dest_file - Path and name of destination
Returns 1 if it is successfully copied
Returns 2 if destination file exists
*/
int copy_files(char* source_file,char* dest_file)
{
   if(source_file==NULL||dest_file==NULL||strcmp(source_file,dest_file)==0)
   {
    return 0;
   }

   if(fileexists(dest_file))
   {
     return 2;
   }

   FILE *source, *target;
   source = fopen(source_file, "r");
   if( source == NULL )
   {
     return 0;
   }
   target = fopen(dest_file, "w");
   if( target == NULL )
   {
      fclose(source);
      return 0;
   }
   int ch;
   while( ( ch = fgetc(source) ) != EOF )
    {
        int ret=fputc(ch, target);
        if(ret==EOF)
        {
           fclose(source);
           fclose(target);
           return 0;
        }
    }

    if(fclose(target)!=0)
    {
        return 0;
    }

    int flag;
    if (feof(source))
    {
        flag=1;
    }
    else if (ferror(source))
    {
        flag=0;
    }
    else
    {
        flag=0;
    }
    if (fclose(source)!=0)
    {
        return 0;
    }
    return flag;

}


/*
A function to return
*/
char *get_filename_ext(char *filename) {

    if(filename==NULL)
    {
        return NULL;
    }

    char *dot = strrchr(filename, '.');

    if(dot==NULL || dot == filename)
    {
        return NULL;
    }

    return dot;
}

/*
Finds all the files in a directory and adds to the queue
Parameters
path - path of the directory
files- Queue to which all the files are enqueued
n- A pointer to int memory which stores the number of files in the directory
Returns 1 if the files can be enqueued to the Queue.
*/
int findAllFiles(char* path,Queue* files,size_t* n)
{
    if(path==NULL||files==NULL||n==NULL)
    {
        return 0;
    }

    (*n)=0;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp("..",dir->d_name)==0 ||strcmp(".",dir->d_name)==0)
            {
                continue;
            }
            char* p=(char*)malloc(sizeof(char)*(strlen(dir->d_name)+strlen(path)+1));
            if(p==NULL)
            {
               (*n)=0;
               return 0;
            }
            int ret=0;
            size_t len=(strlen(dir->d_name)+strlen(path)+1);
            if(path[strlen(path)-1]=='/')
            {
               ret=snprintf(p,len,"%s%s",path,dir->d_name);
            }
            else
            {
               ret=snprintf(p,len,"%s/%s",path,dir->d_name);
            }
               if(ret<0||ret>=len)
               {
                   free(p);
                   return 0;
               }
               if(enQueue(files,p)==0)
               {
                   free(p);
                   return 0;
               }
               free(p);
               (*n)++;
        }
        if(closedir(d)!=0)
        {
            return 0;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}
