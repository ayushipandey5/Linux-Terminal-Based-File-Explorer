#include "headers.h"


vector<string> addDir(string dir_name){
    struct dirent *de;           
    DIR * dir;
    vector<string>tempDirList;
	dir=opendir(dir_name.c_str());
	while((de=readdir(dir))!=NULL)
	{	string filename((de->d_name));
 		tempDirList.push_back(filename);
	}
	closedir(dir);
	return tempDirList;
}

void listFiles(string file_name){
    struct stat buf;
    printf((S_ISDIR(buf.st_mode)) ? "d" : "-");
	printf((buf.st_mode & S_IRUSR) ? "r" : "-");
	printf((buf.st_mode & S_IWUSR) ? "w" : "-");
	printf((buf.st_mode & S_IXUSR) ? "x" : "-");
	printf((buf.st_mode & S_IRGRP) ? "r" : "-");
	printf((buf.st_mode & S_IWGRP) ? "w" : "-");
	printf((buf.st_mode & S_IXGRP) ? "x" : "-");
	printf((buf.st_mode & S_IROTH) ? "r" : "-");
	printf((buf.st_mode & S_IWOTH) ? "w" : "-");
	printf((buf.st_mode & S_IXOTH) ? "x" : "-");


    struct passwd *pw = getpwuid(buf.st_uid);
	struct group *gr = getgrgid(buf.st_gid);
	if (pw != 0)
		printf("\t%s", pw->pw_name);
	if (gr != 0)
		printf("\t%s", gr->gr_name);

	printf("\t%d", buf.st_size);
	char *tt = (ctime(&buf.st_mtime));
	tt[strlen(tt) - 1] = '\0';
	printf("\t%s", tt);
	if(S_ISDIR(buf.st_mode))
	{
		printf("\033[1;36m");
		printf("\t%s\n", file_name);
		printf("\033[0m");
	}
	else
		printf("\t%s\n", file_name);
}

void disDir(int low, int high,vector<string>DirectryList){	
    fflush(stdout);
    tcdrain(STDOUT_FILENO);
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int l = 0;
    int h = w.ws_row - 2;
	cout<<"\033c";//clear screen
	char buffer[256];
	string path = getcwd(buffer, 256);
	cout<<path<<endl<<endl;
	int i;
    sort(DirectryList.begin(),DirectryList.end());
	if(DirectryList.size()<h)
	    high = DirectryList.size();
	
	for(i=low;i<high-1;i++){
	    listFiles(DirectryList[i]);
	    cout<<endl;
	}
	listFiles(DirectryList[i]);
	cout<<endl;
	if(high<22)
	    cout<<"\u001b["<<high-low+2<<"A";
	return;
}
