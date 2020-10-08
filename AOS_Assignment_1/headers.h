#include<iostream>
#include<bits/stdc++.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <errno.h>  
#include <sys/wait.h>
#include <fstream>
#include <sys/ioctl.h>
#include <dirent.h>


using namespace std;

extern vector<string> dirList;
extern vector<char>commandBuff;
extern string root="";
extern int low;
extern int high;

// int getkey();
void normalMode(int *curr_ptr);
vector<string> addDir(string dir_name);
void listFiles(string file_name);
void disDir(int low,int high,vector<string>DirectryList);