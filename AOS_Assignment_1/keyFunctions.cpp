#include "headers.h"

stack<string>backward_history;
stack<string>forward_history;


int getWinRow(){
    fflush(stdout);
    tcdrain(STDOUT_FILENO);
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}


int up(int curr_ptr,vector<string>&DirectryList){
	if((curr_ptr > 0) && (curr_ptr+1 <= DirectryList.size())){
        int limit = getWinRow();
	    if(curr_ptr < limit){
	        curr_ptr--;
			cout<<"\u001b[1A";
		}
        else{
            curr_ptr--;
	        disDir(curr_ptr-limit+1,curr_ptr+1,DirectryList);
	    }
	}		
	return curr_ptr;
}

int down(int curr_ptr,vector<string>&DirectryList){
	if(curr_ptr+1<DirectryList.size() && curr_ptr>=0){
		int limit = getWinRow();
		if(curr_ptr>=limit){
			curr_ptr++;
            disDir(curr_ptr-limit+1,curr_ptr+1,DirectryList);
		}
	    else{
		    curr_ptr++;	
			cout<<"\u001b[1B";
		}
    }		
    return curr_ptr;				
}
int left(int curr_ptr,vector<string>&DirectryList){
	int low,high;
		if(!backward_history.empty()){
            DirectryList.clear();
			DirectryList=addDir(backward_history.top());
			int c=chdir((backward_history.top()).c_str());
			curr_ptr=0;
            int limit = getWinRow();
			low=0;
            high=limit;
			disDir(low,high,DirectryList);
			cout<<"\033[3;1H";
			forward_history.push(backward_history.top());	
			backward_history.pop();			
		}		
	return curr_ptr;
}

int right(int curr_ptr,vector<string>&DirectryList){
	int low,high;
	if(!forward_history.empty()){
	// if(backward_history.top()!=home_path){
		DirectryList.clear();
		DirectryList=addDir(forward_history.top());
		int c=chdir((forward_history.top()).c_str());
		curr_ptr=0;
		low=0;
        high=getWinRow();
		disDir(low,high,DirectryList);
		cout<<"\033[3;1H";
		backward_history.push(forward_history.top());	
		forward_history.pop();
    }
	return curr_ptr;
}

void home(string& home_path,vector<string>&DirectryList){
	int low,high;
	DirectryList.clear();
	DirectryList=addDir(home_path);
	int c = chdir(home_path.c_str());
	low=0;
    high=getWinRow();
	disDir(low,high,DirectryList);	
}

void backspace(string home_path,vector<string>&DirectryList){
	char buffer[256];
	string path = getcwd(buffer, 256);
	if(path!=home_path){
		int low,high;
		DirectryList.clear();
		DirectryList=addDir("..");
		int c=chdir("..");
		low=0;
    	high=getWinRow();
		disDir(low,high,DirectryList);
		cout<<"\033[3;1H";
	}
}

int enter(int curr_ptr,vector<string>&DirectryList){
    int low,high;
	char path_buf[200];
	string path = getcwd(path_buf,200);
	backward_history.push(path);
	string currentPath;
	vector<string> tokens;
						
	stringstream check1(path);
	string rawcode;
	while(getline(check1, rawcode, '/')){
		tokens.push_back(rawcode);
	}
	if(tokens[tokens.size()-1]!=DirectryList[curr_ptr]){
		currentPath = path+"/"+DirectryList[curr_ptr];
		int c=chdir(currentPath.c_str());
	}
	else {
		currentPath=path;
	}


	struct stat buf;
	string filename = currentPath;

	stat(filename.c_str(),&buf);
	if(S_ISDIR(buf.st_mode)){
		DirectryList.clear();
		DirectryList = addDir(currentPath);
		curr_ptr=0;
		low=0;
    	high=getWinRow();
		disDir(low,high,DirectryList);
		cout<<"\033[3;1H";	
	}
	else{
		if (fork() == 0) {
		execl("/usr/bin/xdg-open", "xdg-open", (DirectryList[curr_ptr]).c_str(), (char *)0);
		exit(1);
		}
	}
	return curr_ptr;
}

