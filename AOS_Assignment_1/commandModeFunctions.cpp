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
