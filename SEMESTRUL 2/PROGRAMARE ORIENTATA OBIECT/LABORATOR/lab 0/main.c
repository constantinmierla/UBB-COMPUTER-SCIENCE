#include <stdio.h>

int main() {
    int n, s, x, i;
    scanf("%d", &n);
    s = 0;
    for(i = 0; i < n; i++)
    {
        scanf("%d", &x);
        s = s + x;
    }
    printf("%d", s);
    return 0;
}
