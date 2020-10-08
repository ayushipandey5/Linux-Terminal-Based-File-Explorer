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
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int low = 1 ;
        int high = w.ws_row - 2;

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
        int low = 1 ;
        fflush(stdout);
        tcdrain(STDOUT_FILENO);
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int high = w.ws_row - 2;
        disDir(low,high,dirList);

        char pathBuff[200];
        string path = getcwd(pathBuff,200);
        root = path;
        commandMode();
    }
    
}

