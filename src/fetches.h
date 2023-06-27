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

  // format result to string and return to *uptime
  snprintf(uptime, MAX_PATH, "%ld Hours %ld Minutes", hours % 24, minutes % 60);
}

void getMemory(char *memusage){
  MEMORYSTATUSEX memoryStatus = {sizeof(memoryStatus)};
  if (GlobalMemoryStatusEx(&memoryStatus)) {
    double totalPhysicalMemory = memoryStatus.ullTotalPhys;
    double usedPhysicalMemory = totalPhysicalMemory - memoryStatus.ullAvailPhys;
    
    //convert bytes to GB
    usedPhysicalMemory = bytesToGB(usedPhysicalMemory);
    totalPhysicalMemory = bytesToGB(totalPhysicalMemory);
    
    // format string to X.XX/X.XX GB
    snprintf(memusage, MAX_PATH, "%.2f/%.2f GB", usedPhysicalMemory, totalPhysicalMemory);
  } else {
    return;
  }
}