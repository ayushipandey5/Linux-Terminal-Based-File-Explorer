#include "headers.h"

void setCommandModeStatus(vector<char>&commandBuffer,string mesg){
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cout<<"\u001b["<<1<<"K";
	cout<<"\033["<<w.ws_row<<";1H";
	cout<<"Enter Command:";
	cout<<mesg;				
	cout<<"\033["<<w.ws_row<<";"<<15+mesg.length()<<"H";
	commandBuffer.clear();
}

string copy(string src, string dest){
    string msg;
    ifstream fs;
	ofstream ft;
	char ch;
	fs.open(src);
	if(!fs){
	    msg="Error in opening source file..!!";		

	}		
	ft.open(dest);
	if(!ft){
		msg="Error in opening target file..!!";
		fs.close();		
	}
	while(fs.eof()==0){
	    fs>>ch;
		ft<<ch;
	}	
	fs.close();
	ft.close();
    return msg;
}


string move(string src,string dest)
{
	ifstream fs;
	ofstream ft;
	char ch;
	string mesg;
	fs.open(src);
	if(!fs)
	{
		mesg="Error in opening source file..!!";						
    }							
	ft.open(dest);
	if(!ft)
	{
		mesg="Error in opening target file..!!";
		fs.close();										
	}
	while(fs.eof()==0)
	{
	    fs>>ch;
	    ft<<ch;
	}						
	fs.close();
	ft.close();
	return mesg;
}

string createDir(string src)
{
	string mesg;
	if (mkdir(src.c_str(),0777) != 0)
    {
        mesg="directory not created successfully";
    }
	return mesg;
}

void copyDir(string dir,string dest)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char buffer[256];
	string  basePath = getcwd(buffer, 256);
	if((dp = opendir(dir.c_str())) == NULL) 
	{
	
	}
	chdir(dir.c_str());
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{
		if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
		continue;
        cout<<dir+"/"+string(entry->d_name)<<dest+"/"+string(entry->d_name);
        createDir(dest+"/"+string(entry->d_name));
		copyDir(dir+"/"+string(entry->d_name),dest+"/"+string(entry->d_name));
	    }
	    else 
		{		
            copy(dir+"/"+string(entry->d_name),dest+"/"+string(entry->d_name));
		}
	}
	chdir(basePath.c_str());
	closedir(dp);
}	

string renameFiles(string src,string dest)
{
	ifstream fsin;
	ofstream ftop;
	char ch;
	string mesg;
	fsin.open(src);
	if(!fsin)
	{
		mesg="Error in opening source file..!!";							
	}							
	ftop.open(dest);
	if(!ftop)
	{
		mesg="Error in opening target file..!!";
		fsin.close();											
	}
	while(fsin.eof()==0)
	{
		fsin>>ch;
		ftop<<ch;
	}						
	fsin.close();
	ftop.close();
	return mesg;
}

string createfile(string src)
{								
	ofstream ftsrc;
	char ch;
	string mesg;							
	ftsrc.open(src);
	if(!ftsrc)
	{
		mesg="Error in creating  file..!";													
	}
	else 
	{
		mesg="File Created Successfully";
	}
	
	ftsrc.close();

	return mesg;
}


string deletefile(string src)
{   
    string mesg; 
    if( remove(src.c_str()) != 0 )
        mesg="Error deleting file" ;
    else
        mesg= "File successfully deleted" ;
	return mesg;                                        
}

string delete_dir(string src)
{
    string mesg;
    if (rmdir(src.c_str()) != 0)
        mesg= "Error deleting folder";
    else
        mesg= "Folder successfully deleted" ;
    return mesg;                        
}

vector<string> searchFile(string dir,vector<string>&search1,string file)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char buffer[256];
	string  basePath = getcwd(buffer, 256);
	if((dp = opendir(dir.c_str())) == NULL) 
	{
	//return search1;
	}
	chdir(dir.c_str());
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{
		if(strcmp(".",entry->d_name) == 0 ||
		strcmp("..",entry->d_name) == 0)
		continue;
		search1=searchFile(dir+"/"+string((entry->d_name)),search1,file);
	    }
	    else 
		{
			if(string(entry->d_name)==file)
			//search1.push_back(dir);
			///////////////////////*
				{vector<string> tokens;
					
					stringstream check1(dir);
					string rawcode;
					while(getline(check1, rawcode, '/'))
					{
						tokens.push_back(rawcode);
					}	
					search1.push_back(tokens[tokens.size()-1]);}
			//////////////////
			//search1.push_back(dir+"/"+string(entry->d_name));
		
		}
	}
	chdir(basePath.c_str());
	closedir(dp);
	return search1;
}


void displaySearchResult(int low,int high,vector<string>DirectryList)
{	
	cout<<"\033c";//clear screen
	char buffer[256];
	string path = getcwd(buffer, 256);
	cout<<path<<endl<<endl;
	int i;
	if(DirectryList.size()<25)
	high=DirectryList.size();
	cout<<"\u001b[33m";
	for(i=low;i<high;i++)
	{
	cout<<DirectryList[i]<<endl;
	
	}
	cout<<"\u001b[0m";
	if(high<22)
	cout<<"\u001b["<<high-low+2<<"A";
	
}