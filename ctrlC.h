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
using namespace std;


PROCESS_INFORMATION p;
STARTUPINFO f;
HANDLE Ctrl_handler;
bool fgp_interrupt = false;
LPCSTR task;

//
bool Check_fgp_status()
{
    DWORD id_status;
   GetExitCodeProcess(p.hProcess, &id_status);
    if(id_status == STILL_ACTIVE) return true;
    return false;
}
void Get_signal()
{
    string sig = "";
    while(Check_fgp_status())
    {
        DWORD id_status;
        GetExitCodeProcess(p.hProcess, &id_status);
        if(id_status != STILL_ACTIVE) return;
        getline(cin, sig);
        if(cin.fail() || cin.eof())
        {
            cin.clear();
            return;
        }
        else
        {
            if(Check_fgp_status()) cout<<"Unknown command.\n";
            else return;
        }
    }
    return;
}
// Mo tien trinh Foreground
void openProcessInForeGround(const string &s)
{   
    task = strdup(s.c_str());
    ZeroMemory(&f, sizeof(f)); 
    f.cb = sizeof(STARTUPINFO);
    CreateProcess (task,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL, &f,&p);
    
     DWORD Id;
    Ctrl_handler = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Get_signal, NULL, 0, &Id);
    HANDLE Handle[2] = {p.hProcess, Ctrl_handler};

    //WaitForSingleObject(pi.hProcess, MAX_TIME);
    WaitForMultipleObjects(2, Handle, FALSE,INFINITE);

    TerminateProcess(p.hProcess, 0);
    CloseHandle(p.hProcess);
    CloseHandle(p.hThread);
    CloseHandle(Ctrl_handler);

    sleep(1);

    //if(!fgp_interrupt) cout<<"Foreground process ended successfully. Press enter to continue ...\n";
    //WaitForSingleObject(Ctrl_handler, MAX_TIME);
    fgp_interrupt = false;
    return;

}
//

void SIGINT_Handler(int param)
{
    TerminateProcess(p.hProcess, 0);
    CloseHandle(p.hProcess);
    CloseHandle(p.hThread);
    fgp_interrupt = true;
    
    cout<<"Foreground process was interrupted by Ctrl-C signal.\n";
   
	return;
}

BOOL WINAPI Handler(DWORD cntrlEvent)
{
    if(cntrlEvent != CTRL_C_EVENT)
    {
        cout<<"Unknown command.\n";
        
        return TRUE;
    }
    SIGINT_Handler(0);
    return TRUE;
}

void RaiseCtrlCInterrupt()
{
    cout<<"Ctrl-C interrupt signal found.\n";
    return;
}
void SIGINT_Handler_Shell(int param)
{
    RaiseCtrlCInterrupt();
    return;
}

BOOL WINAPI Handler_shell(DWORD cntrlEvent)
{
	if(cntrlEvent != CTRL_C_EVENT)
    {
    	
        cout<<"Unknown command.\n";
  
        return TRUE;
    }
    SIGINT_Handler_Shell(0);
    return TRUE;
}