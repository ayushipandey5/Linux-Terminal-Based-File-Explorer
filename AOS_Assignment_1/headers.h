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

extern string * root;
extern vector<char>commandBuff;


void normalMode(int *curr_ptr,vector<string>&dirList);
char getKey();
int getWinRow();
vector<string> addDir(string dir_name);
void listFiles(char * file_name);
void disDir(int low,int high,vector<string>DirectryList);
int up(int curr_ptr,vector<string>&DirectryList);
int down(int curr_ptr,vector<string>&DirectryList);
int left(int curr_ptr,vector<string>&DirectryList);
int right(int curr_ptr,vector<string>&DirectryList);
void home(string& home_path,vector<string>&DirectryList);
void backspace(string home_path,vector<string>&DirectryList);
int enter(int curr_ptr,vector<string>&DirectryList);
