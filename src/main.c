#include <stdio.h>

#include "fetches.h"

#define ascii "\x1b[38;2;245;224;220m"    // #f5e0dc

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[39m"
#define RESET   "\x1b[0m"

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

  // get packages
  int pkgs = getPkgs();

  // print system information with ascii
  printf(ascii"\n\n  \\    /\\ "  BLUE"  \uf2c0  " YELLOW"~>" WHITE" %s\n", hostname);
  printf(ascii"   )  ( ')"        BLUE"  \ueaf8  " YELLOW"~>" WHITE" %s\n", buildnum);
  printf(ascii"  (  /  ) "        BLUE"  \uf017  " YELLOW"~>" WHITE" %s\n", uptime);
  printf(ascii"   \\(__)| "       BLUE"  \uf51e  " YELLOW"~>" WHITE" %s\n", memusage);
  if (pkgs != 0){
    printf("          "           BLUE"  \ueb29  " YELLOW"~>" WHITE" %d (scoop)\n", pkgs);
  }
  // print colored bar
  printf("\n     " RED "\u25CF   " GREEN "\u25CF   " YELLOW "\u25CF   " BLUE "\u25CF   " MAGENTA "\u25CF   " CYAN "\u25CF   " RESET "\u25CF   \n\n");
  
  return 0;
}