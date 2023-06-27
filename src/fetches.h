#include <stdlib.h>
#include <windows.h>

#include "convert.h"

void getHostname(char *hostname){
  DWORD size = MAX_COMPUTERNAME_LENGTH;
  
  // access Windows API to get computer name
  GetComputerNameA(hostname, &size);
  convLowcase(hostname);
}

void getBuild(char *buildnum){
  HKEY hKey;
  // open registry
  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
    // run if successfully open registry key 
    DWORD bufferSize = 6;
    DWORD major, minor, currentver;
    char currentbuild[6];
    
    // read registry values of build number
    RegGetValueA(hKey, NULL, "CurrentBuildNumber", RRF_RT_REG_SZ, NULL, currentbuild, &bufferSize);
    RegGetValueA(hKey, NULL, "CurrentMajorVersionNumber", RRF_RT_REG_DWORD, NULL, &major, &bufferSize);
    RegGetValueA(hKey, NULL, "CurrentMinorVersionNumber", RRF_RT_REG_DWORD, NULL, &minor, &bufferSize);
    RegGetValueA(hKey, NULL, "UBR", RRF_RT_REG_DWORD, NULL, &currentver, &bufferSize);
    
    snprintf(buildnum, 16, "%lu.%lu.%s.%lu", major, minor, currentbuild, currentver);
    
    // close registry
    RegCloseKey(hKey);
  }
}

void getUptime(char *uptime){
  // read system uptime in milliseconds
  ULONGLONG sysuptime = GetTickCount64();
  // convert milliseconds to minutes
  DWORD minutes = sysuptime / (60*1000);
  // convert minutes to hours
  DWORD hours = minutes / 60;

  if (hours % 24 == 0){
    snprintf(uptime, MAX_PATH, "%ld minutes", minutes % 60);
  } else {
    snprintf(uptime, MAX_PATH, "%ld hours %ld minutes", hours % 24, minutes % 60);
  }
  // format result to string and return to *uptime
  
}

void getMemory(char *memusage){
  MEMORYSTATUSEX memoryStatus = {sizeof(memoryStatus)};
  if (GlobalMemoryStatusEx(&memoryStatus)) {
    double totalPhyMem = memoryStatus.ullTotalPhys;
    double usedPhyMem = totalPhyMem - memoryStatus.ullAvailPhys;
    
    //convert bytes to GB
    usedPhyMem = bytesToGB(usedPhyMem);
    totalPhyMem = bytesToGB(totalPhyMem);
    
    // format string to X.XX/X.XX GB
    snprintf(memusage, MAX_PATH, "%.2f/%.2f GB", usedPhyMem, totalPhyMem);
  } else {
    return;
  }
}

int pathCheck(const char *path){
  // return 1 if path exist, 0 if non
  DWORD attributes = GetFileAttributesA(path);
  return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

int countPkgs(char *path){
  // initialize folder search vars
  WIN32_FIND_DATAA fData;
  HANDLE fHandle;
  int count = 0;
  // append *.* to find folders in directory (path)
  snprintf(path, MAX_PATH, "%s\\*.*", path);
  fHandle = FindFirstFile(path, &fData);
  if (fHandle == INVALID_HANDLE_VALUE){
    // if no file exist
    return 0;
  }
  // count folders in directory
  do{
    // ensure attribute is directory, excludes current "." & parent directory ".." & scoop itself
    if ((fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && strcmp(fData.cFileName, ".") != 0 && strcmp(fData.cFileName, "..") != 0 && strcmp(fData.cFileName, "scoop") !=0) {
      count++;
    }
  } while (FindNextFile(fHandle, &fData));
  // close file handler
  FindClose(fHandle);
  return count;
}

int getPkgs(){
  // get user environment 
  const char* userProfile = getenv("USERPROFILE");
  if (userProfile != NULL){
    char path[MAX_PATH];
    // scoop pkgs path
    snprintf(path, MAX_PATH, "%s\\scoop\\apps\\", userProfile);
    if (pathCheck(path) == 1) {
      return countPkgs(path);
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}