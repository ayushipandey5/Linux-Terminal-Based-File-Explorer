#include "header.h"

#define esc 27

int r=1;
int c=80;
void navigate(){
    char ch;
    struct termios new_t;
    struct termios old;
    struct winsize w;
    tcgetattr(STDIN_FILENO,&old);
    new_t=old;
    new_t.c_lflag &= ~(ECHO | ICANON);
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&new_t)==0){
        while(1){
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            int statusLine = w.ws_row + 1;
            printf("%c[%d;%dH",esc, statusLine, 1);
            printf("<-****************************NORMAL MODE****************************->");
            printf("%c[%d;%dH",esc, r, c);
            
            ch=cin.get();
            
            if(ch==esc){

                ch=cin.get();
                ch=cin.get();

                if(ch=='A'){
                    if((r-1)>0){
                        r--;
                        printf("%c[%d;%dH",esc, r-1, c);
                    }
                }

                if(ch=='B'){
                    if((r+1)<statusLine && (r-1)<(totalFiles-1)){
                        r++;
                        printf("%c[%d;%dH",esc, r, c);
                    }
                }

            }

            if(ch == 10){
                printf("%c[2J",esc);
                char * newPath;
                strcpy(newPath,fileArr[r-1].c_str());
                openDirectory(newPath);
            }


    
                
        }
    }
    tcsetattr(STDIN_FILENO,TCSANOW,&old);
    
}