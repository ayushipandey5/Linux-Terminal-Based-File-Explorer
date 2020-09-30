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
        cout<<totalFiles<<"\n";
        for(int i=0;i<totalFiles;i++){
            int size = fileArr[i].length() + 1;
            char * fileName = new char[size];
		    strcpy(fileName, fileArr[i].c_str());
            if(strcmp(fileName,".")==0){
                display(path,".");
            }
            // else if(fileName == ".."){   
            //     //when selection will be done
            // }
            else{
                string s = string(path) + "/" + string(fileName);
                char * filePath = new char[s.length()+1];
                strcpy(filePath, s.c_str());
		        display(filePath,fileName);
            }
        }
    }
    return;
}

int countFiles(char * path){
    int count = 0;
    fileArr.clear();
    struct dirent *de;
    DIR *d = opendir(path);
    if(d==NULL){
        return count;
    }
    else{
        while ((de = readdir(d)) != NULL){
            if(strcmp(de->d_name,"..")==0 && strcmp(path,root)==0){
            }
            else{
                count++;
                fileArr.push_back(de->d_name);
            }
        }
        closedir(d);
        sort(fileArr.begin(),fileArr.end());
    }
    return count;
}

void display(char * filePath,char * fileName){
    struct stat buf;
    if (stat(filePath, &buf) == -1)
	{
		perror("lstat");
	}
    printf((S_ISDIR(buf.st_mode)) ? "d" : "-");
	printf((buf.st_mode & S_IRUSR) ? "r" : "-");
	printf((buf.st_mode & S_IWUSR) ? "w" : "-");
	printf((buf.st_mode & S_IXUSR) ? "x" : "-");
	printf((buf.st_mode & S_IRGRP) ? "r" : "-");
	printf((buf.st_mode & S_IWGRP) ? "w" : "-");
	printf((buf.st_mode & S_IXGRP) ? "x" : "-");
	printf((buf.st_mode & S_IROTH) ? "r" : "-");
	printf((buf.st_mode & S_IWOTH) ? "w" : "-");
	printf((buf.st_mode & S_IXOTH) ? "x" : "-");


    struct passwd *pw = getpwuid(buf.st_uid);
	struct group *gr = getgrgid(buf.st_gid);
	if (pw != 0)
		printf("\t%s", pw->pw_name);
	if (gr != 0)
		printf("\t%s", gr->gr_name);

	printf("\t%d", buf.st_size);
	char *tt = (ctime(&buf.st_mtime));
	tt[strlen(tt) - 1] = '\0';
	printf("\t%s", tt);
	if(S_ISDIR(buf.st_mode))
	{
		printf("\033[1;32m");
		printf("\t%-20s\n", fileName);
		printf("\033[0m");
	}
	else
		printf("\t%-20s\n", fileName);

}
