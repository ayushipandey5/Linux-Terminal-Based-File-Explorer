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
