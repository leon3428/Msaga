int f(int x, int y) {
    return x + y;
}

int main(void) {
    const int x = 0;
    int y[2] = {'a', 'b'};

    int c = f(x, y);
    return 0;
}