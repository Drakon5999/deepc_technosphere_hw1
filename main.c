#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// convert num from P numeral system to Q numeral system, where 2<Q<P<36
char * P2Q(int p, int q, char *num) {
    if (q < 2 || p < q || p > 36) return NULL;
    size_t n = 0;
    size_t sizen = 1;
    char *qur = num;
    bool sign_flag = true;
    // bool space_flag = true;
    while (*qur != '\0') {
        if ((*qur < '0' || *qur > '9') && (*qur < 'a' || *qur > 'z') && (*qur < 'A' || *qur > 'Z') &&
                !(sign_flag && *qur == '+') /*&& !(space_flag && (*qur == ' ' || *qur == 160 || *qur == '\n' ||
                                                               *qur == '\t' || *qur == '\r'))*/)
            return NULL;
        if (*qur >= '0' && *qur <= '9') {
            n *= p;
            n += *qur - '0';
        }
        else if (*qur >= 'a' && *qur <= 'z') {
            n *= p;
            n += *qur - 'a' + 10;
        }
        else if (*qur >= 'A' && *qur <= 'Z') {
            n *= p;
            n += *qur - 'A' + 10;
        }
        sign_flag = false;
        qur++;
        sizen++;
    }
    char *result = NULL;
    if (sizen > 1)
        result = malloc(33 * sizeof(char));
    else return NULL;
    sizen = 0;
    while (n > 0) {
        int mod = n % q;
        if (mod <= 9) {
            result[sizen] = mod + '0';
        }
        else {
            result[sizen] = mod - 10 + 'A';
        }
        n /= q;
        sizen++;
    }
    result[sizen] = '\0';
    sizen++;
    result = realloc(result, sizeof(char) * sizen);
    strrev(result);
    return result;

}

int main() {
    int p, q;
    char *s = malloc(33* sizeof(char));
    scanf("%d%d%s", &p, &q, s);
    printf("%s", P2Q(p, q, s));
    return 0;
}