#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int frames, window;
    int ack[50];

    srand(time(NULL));

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter window size: ");
    scanf("%d", &window);

    for(int i = 0; i < frames; i++) {
        ack[i] = 0;
    }

    for(int i = 0; i < frames; i += window) {
        printf("\nSending frames: ");

        for(int j = i; j < i + window && j < frames; j++) {
            printf("%d ", j);
        }

        printf("\n");
        sleep(1);

        for(int j = i; j < i + window && j < frames; j++) {
            if(ack[j] == 0) {
                int received = rand() % 2;

                if(received == 1) {
                    ack[j] = 1;
                    printf("ACK received for frame %d\n", j);
                } else {
                    printf("ACK lost for frame %d\n", j);
                }
            }
        }

        for(int j = i; j < i + window && j < frames; j++) {
            if(ack[j] == 0) {
                printf("Resending frame %d\n", j);
                sleep(1);
                ack[j] = 1;
                printf("ACK received for frame %d\n", j);
            }
        }
    }

    printf("\nAll frames sent successfully\n");
    return 0;
}
