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
                string msg;
                //copy file command
				if(tokens[0]=="copy_file"){
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

                
                ///copy directory
				else if(tokens[0]=="copy_dir")
				{						
				    char buffer[256];
					string basePath = getcwd(buffer, 256);					
					string compSrc,compDest;
					string dest=tokens[2];				
					compSrc=basePath+"/"+tokens[1];					
					compDest=basePath+"/"+dest;
					msg=createDir(compDest);
					copyDir(compSrc,compDest);
					msg="Directory copied Successfully";
					setCommandModeStatus(commandBuffer,msg);
				}                            
            
                // move file command
                else if(tokens[0]=="move_file"){
		    		string compSrc;
			    	char buffer[256];
    				string basePath = getcwd(buffer, 256);
	    			string dest=tokens[tokens.size()-1];
		    		for(unsigned int i=1;i<tokens.size()-1;i++)
			    	{
				        compSrc=basePath+"/"+tokens[i];
	    			    string compDest=dest+"/"+tokens[i];
    	    			    move(compSrc,compDest);							
			        }
    				for(unsigned int i=1;i<tokens.size()-1;i++)
	    			{
		    			compSrc=basePath+"/"+tokens[i];
			    		if( remove(compSrc.c_str()) != 0 )
				    		msg="Error deleting file" ;
					    else
    						msg="File successfully moved";							
	    			}							
		    		setCommandModeStatus(commandBuffer,msg);
			    }

                ///////////rename file////////////////
				else   if(tokens[0]=="rename")
				{				
    				char buffer[256];
	    			string basePath = getcwd(buffer, 256);
		    		string src,dest;
			    	src=tokens[1];
				    dest=tokens[2];				
    				string compSrc=basePath+"/"+src;
	    			string compDest=basePath+"/"+dest;					
		    		renameFiles(compSrc,compDest);
			    	msg= compSrc=basePath+"/"+src;
				    if( remove(compSrc.c_str()) != 0 )
					    msg= "Error deleting file";
    				else
	    				msg="File successfully renamed";				
		    		setCommandModeStatus(commandBuffer,msg);
			    }

                /////////create directory//////////////
				else if(tokens[0]=="create_dir")
				{					
					char buffer[256];
					string basePath = getcwd(buffer, 256);					
					string compSrc;
					string dest=tokens[2];
					if(dest==".")
					{
						compSrc=basePath+"/"+tokens[1];
					}
					else{
						compSrc=tokens[2]+"/"+tokens[1];
					}	
					msg=createDir(compSrc);
					setCommandModeStatus(commandBuffer,msg);
				}
				
				/////////create file////////////
				else if(tokens[0]=="create_file")
				{				
				    char buffer[256];
					string basePath = getcwd(buffer, 256);				
					string compSrc;
					string dest=tokens[2];
					if(dest==".")
					{
						compSrc=basePath+"/"+tokens[1];
					}
					else{
					    compSrc=tokens[2]+"/"+tokens[1];
					}
						msg = createfile(compSrc);
						setCommandModeStatus(commandBuffer,msg);
				}
				else 
				{
					msg="command not found";
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
