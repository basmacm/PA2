// bcm180002
// file counter program that recursively traverses a
// directory to ciunt the number of directories, files, or size in bytes


#include<dirent.h>
#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#include <linux/limits.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
struct dir_info                                                 //declaring dir_info struct
{
    int dcount;
    int fcount;
    int fsize;
};
struct dir_info filecnt(char*);                                //prototype filecnt() 

#define DEBUGGING 0


static int flag = 0, dir_count = 0, file_count = 0, file_size = 0;



int main(int argc, char* argv[])
{
    struct dir_info temp;
    char resolved_path[PATH_MAX];

    if (argc != 2) {
        cout << "error: invalid number of arguments" << endl;
        cout << "usage: filecnt directoryName" << endl;
        return -1;
    }
    //reads path of directory

    realpath(argv[1], resolved_path);
    if (DEBUGGING)
    {
        cout << "<<<<<" << resolved_path << ">>>>>>>" << endl;
    }
    temp = filecnt(resolved_path);



    if (DEBUGGING)
    {
        cout << argv[1];
    }


    //calls filecnt(path) to retrieve dir info
    //prints results

    cout << "The total number of directories in directory " << argv[1] << " is: " << temp.dcount << endl;
    cout << "The total number of files in directory " << argv[1] << " is: " << temp.fcount << endl;
    cout << "The total number of bytes occupied by all files in directory " << argv[1] << " is: " << temp.fsize << endl;

    if (DEBUGGING)
    {
        cout << argv[1];
    }
    return 0;

}

//argument:directory path name
//return:dir_info
struct dir_info filecnt(char* Path)
{

    struct dir_info temp1;

    struct stat st;
    char newpath[1000];                                      

 // checks directory permissions to skip if not accessible


    if (lstat(Path, &st) == 0)
    {

        mode_t perm = st.st_mode;
        if ((perm & S_IXOTH) == 0)
        {
            if (DEBUGGING)
            {
                cout << " No permissiotn to exec director  " << Path << endl;
            }

            // return perv data
            temp1.dcount = dir_count;
            temp1.fcount = file_count;
            temp1.fsize = file_size;
            return temp1;

        }
    }


    DIR* parentDir;
    struct dirent* dirent;
    if (DEBUGGING)
    {
        cout << " before open path " << Path << endl;
    }
    parentDir = opendir(Path);
    //open directory

    if (DEBUGGING)
    {
        cout << " inside filecnt " << Path << endl;
    }
    if (parentDir == NULL && flag == 0)                           
    {
        cout << "Error opening directory" << Path << endl;
        exit(-1);

    }

    while ((dirent = readdir(parentDir)) != NULL)               
    {
        flag = 1;
        if (strcmp((*dirent).d_name, ".") != 0 && strcmp((*dirent).d_name, "..") != 0)  
        {


            if ((*dirent).d_type == DT_DIR)                        
            {
                dir_count++;                                   
                strcpy(newpath, Path);                         

                strcat(newpath, "/");
                strcat(newpath, (*dirent).d_name);
                filecnt(newpath);                               
            }
            if ((*dirent).d_type == DT_REG)                        
            {
                file_count++;                                
                file_size = file_size + (*dirent).d_reclen;         
            }


        }
    }

    closedir(parentDir);                                       
    temp1.dcount = dir_count;
    temp1.fcount = file_count;
    temp1.fsize = file_size;
    return temp1;                                             
}
