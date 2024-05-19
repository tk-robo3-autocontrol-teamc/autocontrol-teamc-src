#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0, cnt;
    int data, log[10000];
    char ch;
    FILE *fp;

    while (1) {
        ch = getchar();

        if (ch == 'g') {
            data = 0;
            printf("G\n");
        } else if (ch == 'l') {
            data = 1;
            printf("L\n");
        } else if (ch == 'e') {
            printf("E\n");
            sleep(1);

            break;
        } else {
            data = 100;
        }

        while (getchar() != '\n');

        log[i] = data;
        i++;
    }
    cnt = i;

    fp = fopen("log_.txt", "w");
    for (int j = 0; j < cnt; j++) {
        fprintf(fp, "%d\n", log[j]);
    }
    fclose(fp);

    return 0;
}
