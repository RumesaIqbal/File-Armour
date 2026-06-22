#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t now = time(NULL);
    if (now == (time_t)-1) {
        printf("Unable to get current time.\n");
        return 1;
    }

    struct tm *local = localtime(&now);
    if (local == NULL) {
        printf("Unable to convert time.\n");
        return 1;
    }

    char buffer[100];
    if (strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local) == 0) {
        printf("Unable to format date/time.\n");
        return 1;
    }

    printf("Today's date and time: %s\n", buffer);
    return 0;
}
