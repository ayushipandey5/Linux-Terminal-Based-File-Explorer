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
			string mesg;
            string str = string(commandBuffer.begin(),commandBuffer.end());
			vector<string> tokens;
			tokens.clear();
			stringstream check1(str);
			string rawcode;
			while(getline(check1, rawcode, ' ')){
			    tokens.push_back(rawcode);
			}
			if(tokens.size()==1)
			{
				mesg="command not found";
				setCommandModeStatus(commandBuffer,mesg);
				
			}

            // <-######### Copy, move, rename, create #########->
            else if(tokens.size()>2){
                string msg;
                //copy file command
				if(tokens[0]=="copyfile"){
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
				else if(tokens[0]=="copydir")
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
                else if(tokens[0]=="movefile"){
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
				else if(tokens[0]=="createdir")
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
				else if(tokens[0]=="createfile")
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

			else if(tokens.size()==2)
			{
				string basePath; 
                string msg;
				/////////////delete file ////////////
				if(tokens[0]=="deletefile")
				{			
					char buffer[256];
					basePath = getcwd(buffer, 256);
					string dest;
                    string compSrc;
					dest=tokens[1];
                    compSrc=basePath+"/"+dest;
                    msg = deletefile(compSrc);
					setCommandModeStatus(commandBuffer,msg);
				}
				///////////delete dir///////////
				else if(tokens[0]=="deletedir")
				{			
					char buffer[256];
					basePath = getcwd(buffer, 256);		
                    string compSrc;
					string dest=tokens[1];
                    compSrc=basePath+"/"+dest;
                    msg= delete_dir(compSrc);
					setCommandModeStatus(commandBuffer,msg);
				}	
				///////////////goto//////////////////////
				else if(tokens[0]=="goto")
				{			
    				char buffer[256];
	    			basePath = getcwd(buffer, 256);			
                    string compSrc;
			    	string dest=tokens[1];
                    compSrc = *root + "/" + dest;
	    			msg="Directory Goto Successfully";
		    		setCommandModeStatus(commandBuffer,msg);
			    	cout<<compSrc;
				    chdir(compSrc.c_str());
    				dirList.clear();
	    			dirList = addDir(compSrc);
		    		int low=0;
                    int high = getWinRow() - 3;
				    disDir(low,high,dirList);
    				cout<<"\033[3;1H";
                    normalMode(curr_ptr , dirList);
		    		break;
				}	
				////////////searching file/////////////////
				else if(tokens[0]=="search")
				{
					string inputFil=tokens[1];
					vector<string>searchResult;
					char buffer[256];
					basePath = getcwd(buffer, 256);			
					string path=basePath;
					searchResult=searchFile(*root,searchResult,inputFil);
					if(searchResult.size()==0)
					{
						msg="File not Found";
					}
					else
					{
						for (int i=0;i<searchResult.size();i++)
						{
							msg+=searchResult[i]+" "+"Found";
						}
							displaySearchResult(0,searchResult.size(),searchResult );
							cout<<"\033[3;1H";
							chdir(basePath.c_str());
							dirList=searchResult;
                            normalMode(curr_ptr,dirList);
							break;			
					} 
					chdir(basePath.c_str());
					setCommandModeStatus(commandBuffer,msg);
				}
				else 
				{
					msg="command not found";
					setCommandModeStatus(commandBuffer,msg);
				}
            }
        }
        //backspace
		else if(key==127){
			string msg="";
			setCommandModeStatus(commandBuffer,msg);
		}       

        tcsetattr(STDIN_FILENO,TCSAFLUSH,&old);
    }
}