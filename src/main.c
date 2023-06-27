#include <stdio.h>
#include <windows.h>

#include "fetches.h"

int main(){
  // get hostname
  char hostname[MAX_COMPUTERNAME_LENGTH];
  getHostname(hostname);
 
  // get kernel version
  char buildnum[16];
  getBuild(buildnum);
  
  // get system uptime
  char uptime[MAX_PATH];
  getUptime(uptime);

  // get memory usage
  char memusage[MAX_PATH];
  getMemory(memusage);

  printf("  \uf007  ~> %s\n", hostname);
  printf("  \ue796  ~> %s\n", buildnum);
  printf("  \ue388  ~> %s\n", uptime);
  printf("  \ue266  ~> %s\n", memusage);

  return 0;
}