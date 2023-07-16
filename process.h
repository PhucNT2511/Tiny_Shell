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
#include <direct.h>
#include <signal.h>
#include <unistd.h>
#include <winnt.h>

using namespace std;

struct BackGround
{   HANDLE handle;
    HANDLE thread;
    PROCESS_INFORMATION pi;
    LPCSTR cString;
    int status;       
    DWORD id;    };
#define cwd getcwd
#define cdr chdir
int n = 0;
vector <BackGround> processList;

// mo tien trinh background
void openProcessInBackGround(const string &s)
{   
    ++n;
    PROCESS_INFORMATION po;
    STARTUPINFO so;
    so.cb = {sizeof(STARTUPINFO)};     
    ZeroMemory(&so, sizeof(so)); 
    LPCSTR k=strdup(s.c_str());
    if (!CreateProcess (k,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL, &so,&po))
    {
        TerminateProcess(po.hProcess, 0);
        CloseHandle(po.hThread);
        CloseHandle(po.hProcess);
        n--;
        cout<<"Changing of directory or opening file not successful!\n";
        return;
    }
    // 
    BackGround cur;
    cur.cString=k;
    cur.pi=po;
    cur.status=1;
    cur.id =po.dwProcessId;
    cur.handle=po.hProcess;
    cur.thread=po.hThread;
    processList.push_back(cur);
    
}
// Cac thao tac quan ly tien trinh
void kill(string s) // Huy bo mot tien trinh
{
    int Id = atoi(s.c_str());
    int a = 1;

    for (auto &P :processList)
    {   
        if (P.id == Id)
        {   HANDLE handle =P.handle;
            TerminateProcess(handle, 0);
            cout<< "Process " <<P.id<<" killed\n";
            n--;
            a = 0;
            for (auto it = processList.begin(); it != processList.end(); ++it)
                    {
                        if (it->handle == handle)
                        {
                            CloseHandle(it->handle);
                            CloseHandle(it->thread);
                            processList.erase(it);
                            break;
                        }
                    }
           break;
        }
    }

    if (a)
    {cout<< "Can't find the file with the id=" <<Id<<"\n";}
}
//
void kill_All()// Huy tat ca tien trinh
{
    for (auto &P :processList)
    {
            TerminateProcess(P.handle, 0);
            CloseHandle(P.handle);
            CloseHandle(P.thread);
            
    }
    processList.erase(processList.begin(),processList.end());
    cout<<"All the processes are canceled.\n";
    n = 0;
}
// Dung mot tien trinh

void stop(string s)
{
    int Id = atoi(s.c_str());
    int a = 1;
    for (auto &P:processList)
    {
        if (P.id == Id)
        {
            a = 0;
            if (P.status == 1)
            {
                P.status = 0;
                cout << "Process " << P.cString << " stops.\n";
                SuspendThread(P.thread);
                break;
            }
            else
            {
                cout << "Process " << P.cString << " stopped before." << endl;
                break;
            }
        }
    }
    if (a)
    {
        cout<< "Can't find the file with the id=" <<Id<<"\n";
    }
}
// Phuc hoi tien trinh dang dung
void resume(string s)
{
    int Id = atoi(s.c_str());
    int a = 1;
    for (auto& P: processList)
    {   BackGround P1=P;
        if (P.id==Id)
        {
            a = 0;
            if (P.status == 0)
            {
                P.status = 1;
                cout << "Process " << P.cString << " runs again.\n";
                ResumeThread(P.thread);
                break;
            }
            else
            {
                cout << "Process " << P.cString << " is still running." << endl;
                break;
            }
        }
    }
    if (a)
    {
        cout<< "Can't find the file with the id=" <<Id<<"\n";
    }
}
void listOfCurrent()
{
    char *buffer;
    if ((buffer = cwd(NULL, 0)) == NULL)
        perror("_wgetcwd error");
    if (cdr(buffer))
    {
        switch (errno)
        {
        case ENOENT:
            cout<<"No such a file or direction.\n";
            break;
        case EINVAL:
            cout<<"Invalid buffer.\n";
            break;
        default:
            cout<<"Syntax Error.\n";
            break;
        }
    }
    else
        system("dir");// Dung lenh cua he thong
    free(buffer);
}
// dir
void dir(){
    listOfCurrent();
}
void list1()
{
     cout<<"\n";
    cout<<"----------------------------------------------------------------------------------------------------------\n";
    cout<<"| Numbers            IdProcess                hProcess               Status                      Name   \n";
    cout<<"----------------------------------------------------------------------------------------------------------\n";
    int i=1;
    for (auto &P:processList)
    {   
        DWORD dwExitCode;
        GetExitCodeProcess(P.handle, &dwExitCode);
        if (dwExitCode != 259)
        {    HANDLE handle = P.handle;
            TerminateProcess(handle,0);

        /*for (auto it = processList.begin(); it != processList.end(); ++it)
                    {
                        if (it->handle == handle)
                        {
                            CloseHandle(it->handle);
                            CloseHandle(it->thread);
                            processList.erase(it);
                            break;}
        }}*/}
        else
        {
        const char *a = (P.status == 0) ? "Stopping" : "Running ";
        printf("|   %-19d%-26d%-20p%s          %s", i,P.id,  P.handle, a, P.cString);  i++;
        cout<<endl; }
        
        
    }
     cout<<"----------------------------------------------------------------------------------------------------------\n";
}
//
