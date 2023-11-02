#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <time.h>

using namespace std;

string getFormatedTime() {
    auto now = chrono::system_clock::now();
    time_t timeNow = chrono::system_clock::to_time_t(now);
    tm* currentTime = new tm();

    localtime_s(currentTime, &timeNow);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%u-%H:%M", currentTime);

    return string(buffer);
}

int getCurrentSecond() {
    auto now = chrono::system_clock::now();
    time_t timeNow = chrono::system_clock::to_time_t(now);
    tm* currentTime = new tm();

    localtime_s(currentTime, &timeNow);

    return currentTime->tm_sec;
}