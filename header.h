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
using namespace std;


char * root;

 void openDirectory(char * path);
 int countFiles(char * path);
 void display(char * path);
