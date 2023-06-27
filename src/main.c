#include <stdio.h>

#include "fetches.h"

#define ascii "\x1b[38;2;245;224;220m"    // #f5e0dc
#define glyph "\x1b[38;2;137;180;250m"    // #89b4fa
#define arrow "\x1b[38;2;249;226;175m"    // #f9e2af
#define text "\x1b[38;2;205;214;244m"     // #cdd6f4

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

  printf(ascii"\n  \\    /\\ "  glyph"  \uf007  " arrow"~>" text" %s\n", hostname);
  printf(ascii"   )  ( ')"      glyph"  \ue796  " arrow"~>" text" %s\n", buildnum);
  printf(ascii"  (  /  ) "      glyph"  \ue388  " arrow"~>" text" %s\n", uptime);
  printf(ascii"   \\(__)| "     glyph"  \ue266  " arrow"~>" text" %s\n", memusage);
  if (pkgs != 0){
    printf("          "         glyph"  \ueb29  " arrow"~>" text" %d (scoop)\n", pkgs);
  }

  return 0;
}