#include <windows.h>
#include <bits/stdc++.h>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <tlhelp32.h>
#include <tchar.h>
#include <debugapi.h>
#include <processthreadsapi.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <map>
#include <iomanip>
#include <iterator>
#include<direct.h>
#include <signal.h>
#include <unistd.h>
#include "path.h"
#include "ctrlC.h"
#include "process.h"
#include "cd.h"
using namespace std;


void help()
{
    // Display all commands

	cout<<"------------------------------------Some fuction of the Shell-------------------------------\n";
    cout.width(30);
    cout << left << "1.  help"//
         << "Provide Help information for Windows commands\n";
    cout.width(30);
    cout << left << "2.  dir"//
         << "Display list of files in parent directory\n";
    cout.width(30);
    cout << left << "3.  date"//
         << "Display date\n";
    cout.width(30);
    cout << left << "4.  time"//
         << "Display time\n";
    cout.width(30);
    cout << left << "5.  calc <fore|back>"//
         << "Open system calculator, add fore or back mode, example: calc fore, calc back\n";
    cout.width(30);
    cout << left << "6.  notepad <fore|back>"//
         << "Open system notepad, add fore or back mode, example: notepad fore, notepad back\n";
     cout.width(30);
     cout << left << "7.  countdown <fore|back>"//
         << "Open system notepad, add fore or back mode, example: notepad fore, notepad back\n";
     cout.width(30);
    cout << left << "8.  snake <fore|back>"//
         << "Open system notepad, add fore or back mode, example: notepad fore, notepad back\n";
     cout.width(30);
    cout << left << "9.  cd .."//
         << "Change to the parrent directory of the current directory\n";
    cout.width(30);
    cout << left << "10. cd <path>"//
         << "Change current directory to this path\n";
    cout.width(30);
    cout << left << "11. stop <ID>"//
         << "Stop a running process\n";
    cout.width(30);
    cout << left << "12. resume <ID>"//
         << "Resume a stopping process\n";
    cout.width(30);
    cout << left << "13. kill <ID>"//
         << "Kill a running process\n";
    cout.width(30);
    cout << left << "14. kill all"//
         << "Kill all running processes\n";
    cout.width(30);
    cout << left << "15. list"//
         << "Display list of processes\n";
    cout.width(30);
    cout << left << "16. *.bat"
         << "Read *.bat file and run list of command lines\n";
    cout.width(30);
    cout << left << "17. path <|env>"//
    	 << "Display the value of the environment variable a\n";
    cout.width(30);
    cout << left << "18. addPATH <(a)> b"//
    	 << "Add the environment variable a (name) with its path b\n";
    cout.width(30);
    cout << left << "19. delPATH a"//
    	 << "Delete the environment variable a\n";
    cout.width(30);
    cout << left << "20. exit"//
         << "Exit process\n";
    cout.width(30);
    cout << left << "21. CTRL+C"//
         << "Cancer running foreground process\n";
    cout.width(30);
    cout << left << "22. history"//
         << "Print all used commands\n";
     cout.width(30);
    cout << left << "23. clean"//
         << "Clean the history\n";
     cout.width(30);
    cout << left << "24. clear"//
         << "Clear tiny shell screen\n";
    printf("----------------------------------------------------------------------------------------------\n");
}

void exit(){
    cout<<"Goodbye.\n"<<"Kill all the child processes.\n";
    void kill_All();
}


//snake
void snake(string cmd){
    if(cmd=="fore") openProcessInForeGround("D:\\c++\\Tiny_Shell\\ran_san_moi.exe");
    if(cmd=="back") openProcessInBackGround("D:\\c++\\Tiny_Shell\\ran_san_moi.exe");
}
//countdown
void countdown(string cmd){
    if(cmd=="fore") openProcessInForeGround("D:\\c++\\Tiny_Shell\\countdown_timer.exe");
    if(cmd=="back") openProcessInBackGround("D:\\c++\\Tiny_Shell\\countdown_timer.exe");
}
// calc
void calc(string cmd){
    if(cmd=="fore") openProcessInForeGround("c:\\Windows\\System32\\calc.exe");
    if(cmd=="back") openProcessInBackGround("c:\\Windows\\System32\\calc.exe");
}
// notepad
void notepad(string cmd){
    if(cmd=="fore") openProcessInForeGround("c:\\Windows\\System32\\notepad.exe");
    if(cmd=="back") openProcessInBackGround("c:\\Windows\\System32\\notepad.exe");
}

//date
int date(){
    time_t t = time(0);
	struct tm * now = localtime(&t);
    int i =now->tm_wday%7;
    string weekday[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};    
	cout << "Current Date: " <<weekday[i]<<" "<< now->tm_mday << '/'
		<< (now->tm_mon + 1) << '/'
		<< (now->tm_year + 1900)
		<< endl;
	return 0;
}

//time
int time_cmd(){
    time_t t = time(0);
	struct tm * now = localtime(&t);
	cout << "Current time: " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << endl;
	return 0;
}
//history


