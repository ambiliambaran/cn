#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int frames, window, i = 0;
    int ack;

    srand(time(NULL));

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter window size: ");
    scanf("%d", &window);

    while(i < frames) {
        printf("\nSending frames: ");

        int last = i + window - 1;
        if(last >= frames)
            last = frames - 1;

        for(int j = i; j <= last; j++) {
            printf("%d ", j);
        }

        printf("\n");
        sleep(1);

        ack = rand() % 2;

        if(ack == 1) {
            printf("ACK received till frame %d\n", last);
            i = last + 1;
        } else {
            printf("ACK lost! Resending from frame %d\n", i);
        }
    }

    printf("\nAll frames sent successfully\n");
    return 0;
}
