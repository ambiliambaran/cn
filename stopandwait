#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int frames, i;
    int ack;

    srand(time(NULL));

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(i = 0; i < frames; i++) {
        while(1) {
            printf("\nSending frame %d\n", i);
            sleep(1);

            ack = rand() % 2;

            if(ack == 1) {
                printf("ACK received for frame %d\n", i);
                break;
            } else {
                printf("ACK lost! Resending frame %d\n", i);
            }
        }
    }

    printf("\nAll frames sent successfully\n");
    return 0;
}
