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
#include "instruction.h"

using namespace std; 
string currentDirectory = "";
vector<string> history;


void WELCOME(){
    cout<<"-------------------------------------------------------------------------------------------"<<endl;
    cout<<"                                  Welcome to our Tiny Shell                                    \n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<"                                      Nice to assist you                                      \n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<"\nType \"help\" to discover Tiny Shell.";
   // cout<<"<Please type \"help\" to know what function the shell can help> \n";
}
void runBat(string s)
{
    void run(string command);

    ifstream file(s);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            run(line);
        }
    }
    else
    {
        cout << "File " << s << " do not exist in this directory\n";
    }
}
//
void Instruction(string cmd){
        if(cmd=="exit") {exit();} 
         else if(cmd=="calc back"){calc("back");}
        else if(cmd=="calc fore"){SetConsoleCtrlHandler(Handler, TRUE);calc("fore");}
        else if(cmd=="notepad back"){notepad("back");}
        else if(cmd=="notepad fore"){SetConsoleCtrlHandler(Handler, TRUE);notepad("fore");}
        else if(cmd=="dir") {dir();}
        else if(cmd=="list"){list1();}
        else if(cmd=="date"){ date();}
        else if(cmd=="time") {time_cmd();}
        else if(cmd=="help") {help();}
        else if(cmd[0]=='r'&&cmd[1]=='e'&&cmd[2]=='s'&&cmd[3]=='u'&&cmd[4]=='m'&&cmd[5]=='e'){
            string s="";
            for (int i = 6; i <= cmd.length(); ++i)
            { s += cmd[i]; }
            resume(s);
        }
        else if(cmd[0]=='s'&&cmd[1]=='t'&&cmd[2]=='o'&&cmd[3]=='p'){
            string s="";
            for (int i = 4; i <= cmd.length(); ++i)
            { s += cmd[i]; }
            stop(s);
        }
        else if(cmd=="kill all") kill_All();
        else if(cmd[0]=='k'&&cmd[1]=='i'&&cmd[2]=='l'&&cmd[3]=='l'){
            string s="";
            for (int i = 4; i <= cmd.length(); ++i)
            { s += cmd[i]; }
            kill(s);
        }
        else if(cmd=="countdown back") countdown("back");
        else if(cmd=="countdown fore") {SetConsoleCtrlHandler(Handler, TRUE);countdown("fore");}
        else if(cmd=="snake back") snake("back");
        else if(cmd=="snake fore") {SetConsoleCtrlHandler(Handler, TRUE);snake("fore");}
        else if(cmd.find("path") != std::string::npos)
        {   char envname[cmd.length() - 5];
            if (cmd[4] == '\0') {
            readpath(NULL);
        }   
            else {
            for (int i = 5; i <= cmd.length(); i ++) {
                envname[i - 5] = cmd[i];
            }
            readpath(envname);
        }
        }
        else if(cmd.find("addPATH (") != std::string::npos){
            int a;
        int b = 1;
        for (int i = 9; i< cmd.length(); i++){
            if(cmd[i] == '(') b ++;
            if(cmd[i] == ')') b --;
            if(b == 0) {
                a = i + 2;
                break;
            }
        }
        if(b > 0) {
            cout << "Syntax error\n";
        }
        else {
            if (cmd[a - 1] == ' ') {
                char envname[a - 10];
                char envvalue[cmd.length() - a + 1];
                for (int i = 9; i < a - 2; i++){
                    envname[i - 9] = cmd[i];
                }
                envname[a - 11] = '\0';
                for (int i = a; i <= cmd.length(); i ++){
                    envvalue[i-a] = cmd[i];
                }
                addPATH(envname, envvalue);
            }
            else {
                cout << "Illegal command!\n";
            }   
            }
        }
        else if (cmd.find("delPATH ") != std::string::npos){
        char envname[cmd.length() - 8];
        for (int i = 8; i <= cmd.length(); i++){
            envname[i - 8] = cmd[i];
        }
        delpath(envname);
        }   
        else if (cmd.find(".bat") != std::string::npos) 
        {
        string s = currentDirectory+"\\" + cmd;
        runBat(s);}
        
        else if (cmd.compare("history") == 0)
        {
        int i = 0;
        for (string s: history){
            if (s != "history"){
                i++;
                cout << i << ". "<< s << endl;
            }
        }
        if (i == 0)
            cout << "Empty history!" << endl;
        }

        else if (cmd.compare("clean") == 0)
        {
        history.clear();
        cout << "Your history has been cleaned thoroughly!" << endl;
        }
        else if (cmd.compare("clear") == 0)
        {
        system("cls");
        }
        else if (cmd[0]=='c' && cmd[1] == 'd')
        { 
            //if(cmd=="cd")  curDir();// trung voi lenh dir
            if(cmd=="cd ..") parentDir();
            else{
            string s = "";
            for (int i = 3; i < cmd.length(); ++i)
                s += cmd[i];
            changeDir(s);
            }            
        }
        else cout<<"Illigal command.\n";
        if(cmd!="clean")history.push_back(cmd);
}


string trim(string command) {
    int j = -1, k = command.length(), g = command.length();
    for(int i = 0; i < g; ++i) {
        if(command[i] == ' ') {
            j = i;
        }
        else {
            break;
        }
    }

    for(int i = g - 1; i > j; i--) {
        if(command[i] == ' ') {
            k = i;
        }
        else break;
    }
    string s = "";
    for(int i = j + 1; i < k; ++i) {
        s = s + command[i];
    }
    return s;
}
//
vector<string> createJobs(string command) {
	vector<string> jobs;
	string s = "";
	int a = command.length();
	for(int i = 0; i < a; ++i) {
		if(command[i] != '>') {
			s = s + command[i];
		}
		else {
			jobs.push_back(s);
			s = "";
		}
	}
	jobs.push_back(s);
	return jobs;
}
void run(string command)
{
    vector<string> jobs;
    jobs = createJobs(command);
    for (int i = 0; i < jobs.size(); ++i)
    {
         Instruction(trim(jobs[i]));
    }
}

//
int main(int argc, char** argv){
           
    string cmd;
    WELCOME();
    cout<<endl;
    char *buffer1 = _getcwd(NULL, 0);
    int i = 0;
    while(buffer1[i] != '\0')
        {
            currentDirectory += buffer1[i];
            i++;
        }
    
    while(1){
        
        char *buffer = _getcwd(NULL, 0);    
        printf("%s", buffer);
        cout << ">";
        getline(cin,cmd);
        if(cin.eof() || cin.fail())  {SetConsoleCtrlHandler(Handler_shell,TRUE); sleep(1);}
        else if(cmd=="exit") {exit(); break;} 
        else Instruction(cmd);
    }
    
    system("pause");
    return 0;
}

