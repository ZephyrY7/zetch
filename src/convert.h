void convLowcase(char* str){
  // convert string to lowercase with bitwise 
  int i = 0;
  while (str[i]){
    str[i] = str[i] | 0x20;
    i++;
  }
}

double bytesToGB(DWORDLONG bytes) {
    // convert bytes to gigabytes bye dividing 1024^3
    return (double)bytes / (1024 * 1024 * 1024);
}