#include "headers.h"

#define esc 27 

// // <-####### CANONICAL MODE SETTING #######->
// char getKey(){
//     char ch;
//     struct termios new_t;
//     struct termios old;
//     tcgetattr(STDIN_FILENO,&old);
//     new_t=old;
//     new_t.c_lflag &= ~(ECHO | ICANON);
//     tcsetattr(STDIN_FILENO,TCSAFLUSH,&new_t);
//     ch = getchar();
//     tcsetattr(STDIN_FILENO,TCSAFLUSH,&old);
//     return ch;
// }


void normalMode(int *curr_ptr, vector<string>&dirList){
    char esc_start[] = { 0x1b, ']', '0', ';', 0 };
    char esc_end[] = { 0x07, 0 };
    char key;
    struct termios newie;
    struct termios oldie;
    tcgetattr(STDIN_FILENO,&oldie);
    newie=oldie;
    newie.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&newie);

    while(1){
        struct termios new_t;
        struct termios old;
        tcgetattr(STDIN_FILENO,&old);
        new_t=old;
        new_t.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO,TCSAFLUSH,&new_t);
        cout << esc_start <<"************** NORMAL MODE **************"<< esc_end;
        key = cin.get();
        // <-####### CURSOR UP,DOWN,LEFT,RIGHT #######->
		if (key == 27){
		    key = cin.get();
		    key = cin.get();
            // Up key
            if(key == 'A'){
                *curr_ptr = up(*curr_ptr,dirList);
            }
            //Down key
            else if(key == 'B'){
                *curr_ptr=down(*curr_ptr,dirList);
            }
            //Left key
            else if(key == 'D'){
                *curr_ptr=left(*curr_ptr,dirList);
            }
            //Left key
            else if(key == 'C'){
                *curr_ptr=right(*curr_ptr,dirList);
            }
		}
        // <-####### CURSOR H => Home key #######->
        if(key == 104){
            home(*root,dirList);
			curr_ptr=0;
        }
        // <-####### CURSOR Backspace Key #######->
        if(key == 127){
            backspace(*root,dirList);
            curr_ptr = 0;
        }
        // <-####### CURSOR Enter key #######->
        if(key == 10){
            *curr_ptr = enter(*curr_ptr,dirList);
        }

        tcsetattr(STDIN_FILENO,TCSAFLUSH,&old);
    }
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&oldie);
}
