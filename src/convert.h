void convLowcase(char* str) {
    while (*str) {
        *str |= 0x20;
        str++;
    }
}

double bytesToGB(DWORDLONG bytes) {
    // convert bytes to gigabytes bye dividing 1024^3
    return (double)bytes / (1024 * 1024 * 1024);
}
