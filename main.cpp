#include "header.h"

char *root;

int main(int argc,char *argv[]){

    if(argc==1){
        string s = ".";
		char *path = new char[s.length() + 1];
		strcpy(path, s.c_str());
		root = path;
		openDirectory(".");
    }

    else if(argc==2){

    }

    navigate();


    return 0;
}
