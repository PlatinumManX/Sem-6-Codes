
#include <stdio.h>
#include <stdbool.h>

int isPrime(int n);
int calculateModPow(int pow, int p, int g);
int getMod(int M, int e, int n);
int helper(int M, int e, int n, int mapPow[], int mapVal[], int mapSize);
int generator(int p);
int setGenerator(int p, int numSet[], int checkNum);

int main() {
    int p, g, x, y, R1, R2, K1, K2;

    printf("Enter the value of x:");
    scanf("%d", &x);

    printf("Enter the value of P:");
    scanf("%d", &p);
    while (!isPrime(p)) {
        printf("Enter the prime value of p:");
        scanf("%d", &p);
    }

    g = generator(p);

    R1 = getMod(g, x, p);
    printf("\nThe value of R1:%d\n", R1);

    printf("\nEnter the value of y:");
    scanf("%d", &y);

    R2 = getMod(g, y, p);
    printf("The value of R2:%d\n", R2);

    K1 = getMod(R2, x, p);
    printf("\nThe value of K from Alice:%d\n", K1);

    K2 = getMod(R1, y, p);
    printf("\nThe value of K from Bob:%d\n", K2);

    return 0;
}

int isPrime(int n) {
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0)
            return 0;
        i++;
    }
    return 1;
}

int getMod(int M, int e, int n) {

    int mapPow[100], mapVal[100];
    int powerBreak[100];
    int mapSize = 0, pbSize = 0;

    int pow = 1;
    int mult = 2;

    while (e != 0) {

        int found = 0;
        for (int i = 0; i < mapSize; i++) {
            if (mapPow[i] == pow) {
                found = 1;
                break;
            }
        }

        if (found) {
            e -= pow;
            powerBreak[pbSize++] = pow;
        } else {
            e -= pow;

            mapPow[mapSize] = pow;
            mapVal[mapSize] = helper(M, pow, n, mapPow, mapVal, mapSize);
            mapSize++;

            powerBreak[pbSize++] = pow;
            pow *= mult;
        }

        while (pow > e) {
            pow /= mult;
        }
    }

    int cipher = 1;

    for (int i = 0; i < pbSize; i++) {
        int value = 0;
        for (int j = 0; j < mapSize; j++) {
            if (mapPow[j] == powerBreak[i]) {
                value = mapVal[j];
                break;
            }
        }
        cipher = (cipher * value) % n;
    }

    return cipher % n;
}

int helper(int M, int e, int n, int mapPow[], int mapVal[], int mapSize) {

    if (e == 0)
        return 1;

    if (e == 1)
        return M % n;

    int quotient = e / 2;
    int first = 0;

    for (int i = 0; i < mapSize; i++) {
        if (mapPow[i] == (e - quotient)) {
            first = mapVal[i];
            break;
        }
    }

    return (first * helper(M, e - quotient, n, mapPow, mapVal, mapSize)) % n;
}

int generator(int p) {

    int numSet[100] = {0};
    int g = 0;

    for (int i = 1; i < p; i++)
        numSet[i] = 1;

    for (int i = 2; i < p; i++) {

        if (setGenerator(p, numSet, i)) {
            g = i;

            printf("\n\nThe set generated is:%d", g);
            printf("\nGeneartor generate terms as:-\n");

            for (int pow = 1; pow < p; pow++) {
                if (numSet[pow]) {
                    printf("%d ^ %d mod %d = %d\n",
                           i, pow, p, getMod(i, pow, p));
                }
            }
            break;
        }
    }
    return g;
}

int setGenerator(int p, int numSet[], int checkNum) {

    int temp[100] = {0};

    for (int pow = 1; pow < p; pow++) {
        if (numSet[pow]) {
            int val = getMod(checkNum, pow, p);
            temp[val] = 1;
        }
    }

    for (int i = 1; i < p; i++) {
        if (temp[i] != numSet[i])
            return 0;
    }

    return 1;
}
