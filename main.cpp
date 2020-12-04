#include "headers.h"

string * root;

string terminalMode="NORMAL";
int main(int argc, char ** argv){
    int curr_ptr=0;
    cout<<"\u001b[2J"; //clear screen
    vector<string>dirList;
    if(argc>=2){
        string current = argv[1];
        dirList = addDir(current);
        if(chdir(current.c_str())<0)
            cout<<"Error"<<endl;
        int low = 0 ;
        fflush(stdout);
        tcdrain(STDOUT_FILENO);
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int high = w.ws_row - 2;
        disDir(low,high,dirList);

        char pathBuff[200];
        string path = getcwd(pathBuff,200);
        *root = path;
        commandMode(&curr_ptr,dirList);
    }
    else if(argc < 2){   
        int low = 0 ;
        int high = getWinRow()-3;

        char pathBuff[256];
        string path = getcwd(pathBuff,256);
        root = &path;
        dirList = addDir(".");

        for(int i=0;i<dirList.size();i++){
            cout<<dirList[i]<<endl;
        }
        disDir(low,high,dirList);
        normalMode(&curr_ptr,dirList);
    }

    
}

