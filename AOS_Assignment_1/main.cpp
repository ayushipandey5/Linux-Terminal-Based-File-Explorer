#include "headers.h"
// #include"DirListing.h"
// #include"keyMovement.h"
// #include"commandExecution.h"


string root;

int main(int argc, char ** argv){
    cout<<"\u001b[2J";
    if(argc == 1){
        string current=".";
        dirList = addDir(current);
        if(chdir(current.c_str())<0)
            cout<<"Error"<<endl;
        low=0;high=25;
        disDir(low,high,dirList);

        char pathBuff[200];
        string path = getcwd(pathBuff,200);
        root = path;
        int curr_ptr=0;
        normalMode(&curr_ptr);
    }

    if(argc>=2){
        string current=argv[1];
        dirList = addDir(current);
        if(chdir(current.c_str())<0)
            cout<<"Error"<<endl;
        disDir(low,high,dirList);

        char pathBuff[200];
        string path = getcwd(pathBuff,200);
        root = path;
        commandMode();
    }
    
}

