#include "header.h"

vector<string> fileArr;
int totalFiles;

void openDirectory(char * path){
    // struct dirent *de;
    DIR *d = opendir(path);
    if(d==NULL){
        printf("Could not open current directory\n");
    }
    else{
        totalFiles = countFiles(path);
        for(int i=0;i<totalFiles;i++){
            display(path);
        }
    }
    return;
}

int countFiles(char * path){
    int count = 0;
    struct dirent *de;
    DIR *d = opendir(path);
    if(d==NULL){
        return count;
    }
    else{
        while ((de = readdir(d)) != NULL){
            if(de->d_name != ".." && strcmp(path,root)!=0){
                count++;
                fileArr.push_back(de->d_name);
            }
        }
        closedir(d);
    }
    return count;
}

void display(char * path){
    struct stat buf;

}
