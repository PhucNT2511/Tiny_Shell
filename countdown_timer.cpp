//Please note that this is Windows specific code
#include <iostream>
#include <Windows.h>


int main()
{
    int counter = 200; //amount of seconds
    Sleep(1000);
    while (counter >= 1)
    {
       std:: cout << "\rTime remaining: " << counter << std::flush;
        Sleep(1000);
        counter--;
    }
}
