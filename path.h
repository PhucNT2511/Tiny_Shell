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
// read path
void readpath(char* t) {
    #define MAX_NAME 16383
    #define MAX_VALUE 100000
    HKEY hkey;
    BYTE value[MAX_VALUE] ;
    DWORD valsize = sizeof(value) ;
    RegOpenKeyEx(HKEY_CURRENT_USER,"Environment", 0, KEY_ALL_ACCESS, &hkey);

    if (t == NULL) {
        for (int i = 0; ; i ++) {
            TCHAR name[MAX_NAME];
            DWORD namesz = MAX_NAME;
            value[0] = '\0';
            DWORD valsize = MAX_VALUE;
            if (RegEnumValue(hkey, i, name, &namesz, NULL, NULL, value, &valsize) == 0) {
                cout << (i < 9 ? "0":"") << i + 1 <<". " << name
                     << " = " << value << "\n";
            }
            else {
                break;
            }
        }
        
    }
    else if (RegQueryValueEx(hkey, t, NULL, NULL, value, &valsize ) == 0) {
        cout << "The value of "<< t<<" is: "<< value<<"\n";   
    }
    else {
        cout << "There no variables has the name "<< t<< "\n";
    }
    
    RegCloseKey(hkey);
}
// add path
void addPATH(char* envname, char *envvalue) {
    cout << "The environment variable "<< envname<< " is added\n";
    HKEY hkey;
    static BYTE value[100000] ;
    DWORD valsize = sizeof(value) ;                                  
    RegOpenKeyEx(HKEY_CURRENT_USER,"Environment", 0, KEY_ALL_ACCESS, &hkey);
    if(RegQueryValueEx(hkey, envname, NULL, NULL, value, &valsize) == 0){
        char *name  = (char*) value;
        strcat(name, ";");
        strcat(name, envvalue);
        RegSetValueEx(hkey,envname,0,REG_SZ,(BYTE*) name, strlen(name));
    }
    else {
        RegSetValueEx(hkey,envname,0,REG_SZ,(BYTE*) envvalue, strlen(envvalue));
    }
    RegCloseKey(hkey);

}
// del path
void delpath(char*t){
    HKEY hkey;
    RegOpenKeyEx(HKEY_CURRENT_USER,"Environment", 0, KEY_ALL_ACCESS, &hkey);
    if (RegDeleteValue(hkey, t) == 0) {
        cout << "The environment variable "<< t<< " is deleted\n";
    }
    else {
        cout << "There no variables has the name called "<< t<< "\n";
    }
    RegCloseKey(hkey);
}

