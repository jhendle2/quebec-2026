void fizzBuzz(const int n) {
    for (int i = 0; i < n; i++) {
        if      (i %  3 == 0) printf("Fizz\n");
        else if (i %  5 == 0) printf("Buzz\n");
        else if (i % 15 == 0) printf("FizzBuzz\n");
        else printf("%d\n", i);
    }
}

int main(void) {
    fizzBuzz(20);
    return 0;
}