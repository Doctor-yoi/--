#pragma once
bool isRemovableDevice();
bool copySelfToDirectory();
std::string getWorkingPath();
bool selfStart();
bool dirExists(const std::string& dirName_in);
bool fileExists(LPCTSTR lpFileName);