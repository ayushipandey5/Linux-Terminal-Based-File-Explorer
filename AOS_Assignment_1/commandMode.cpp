# include "headers.h"


vector<char>commandBuffer;

void commandMode(int * curr_ptr , vector<string> dirList){
    char esc_start[] = { 0x1b, ']', '0', ';', 0 };
    char esc_end[] = { 0x07, 0 };
    char key;
    cout << esc_start <<"************** COMMAND MODE **************"<< esc_end;

    while(1){
        struct termios new_t;
        struct termios old;
        tcgetattr(STDIN_FILENO,&old);
        new_t=old;
        new_t.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO,TCSAFLUSH,&new_t);
        key = cin.get();

        if(key!=10 && key!=27 && key!=127){
			cout<<key;
			commandBuffer.push_back(key);
		}

        //escape key
        else if(key==27){
            // clear the end line
			cout<<"\u001b["<<1<<"K";
            // set cursor to original
			cout<<"\033["<<3<<";1H";
            normalMode(curr_ptr,dirList);
			break;	 
		}

        //enter
        else if(key == 10){
            string str = string(commandBuffer.begin(),commandBuffer.end());
			vector<string> tokens;
			tokens.clear();
			stringstream check1(str);
			string rawcode;
			while(getline(check1, rawcode, ' ')){
			    tokens.push_back(rawcode);
			}

            // <-######### Copy, move, rename, create #########->
            if(tokens.size()>2){
                //copy command
				if(tokens[0]=="copy_file"){
                    string msg;
				    string desti,basePath;
					char buffer[256];
					basePath = getcwd(buffer, 256);
					desti = tokens[tokens.size()-1];				
					for(unsigned int i=1;i<tokens.size()-1;i++){
						string src = basePath+"/"+tokens[i];
						string dest = desti+"/"+tokens[i];
                        msg=copy(src,dest);
					}
					//	"File Successfully Copied";
					setCommandModeStatus(commandBuffer,msg);
				}                
            }
        }








        // //backspace
		// else if(key==127){
		// 	string msg="";
		// 	setCommandModeStatus(commandBuffer,msg);
		// }       

        tcsetattr(STDIN_FILENO,TCSAFLUSH,&old);
    }
}