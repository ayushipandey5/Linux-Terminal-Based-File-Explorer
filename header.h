#include<bits/stdc++.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/ioctl.h> 
using namespace std;


extern char * root;
extern int totalFiles;
extern vector<string> fileArr;

void openDirectory(char * path);
int countFiles(char * path);
void display(char * filePath,char * fileName);
void navigate();
