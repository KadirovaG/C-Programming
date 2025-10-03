#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[100];
    printf("What's your name? ");
    if (fgets(name, sizeof(name), stdin) == NULL) return 0;

    name[strcspn(name, "\n")] = '\0';

    printf("hello, %s!\n", name);
    return 0;
}
