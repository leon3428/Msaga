int main(void) {
    int x = 0;
    int y = 0;

    int a = (int)'a';
    const char b = (const char)x;
    const int c = (const int)'a';
    char d = (char)((const int)300 + (int)'a');
    int e = (int)(char)(const int)(const char)(x + y);
    int f[10] = {1,2,3,4};
    int g = (char)f;

    return 0;
}