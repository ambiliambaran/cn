#include <stdio.h>

int main() {
    int bucket_size, output_rate, num_packets;
    int incoming[50];
    int i, current_bucket = 0;

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);

    printf("Enter output rate: ");
    scanf("%d", &output_rate);

    printf("Enter number of packets: ");
    scanf("%d", &num_packets);

    printf("Enter packet sizes:\n");
    for(i = 0; i < num_packets; i++) {
        scanf("%d", &incoming[i]);
    }

    printf("\nPkt No\tIncoming\tAccepted\tDropped\tSent\tRemaining\n");

    for(i = 0; i < num_packets; i++) {
        int accepted, dropped, sent;

        if(current_bucket + incoming[i] <= bucket_size) {
            accepted = incoming[i];
            dropped = 0;
        } else {
            accepted = bucket_size - current_bucket;
            if(accepted < 0) accepted = 0;
            dropped = incoming[i] - accepted;
        }

        current_bucket += accepted;

        if(current_bucket >= output_rate)
            sent = output_rate;
        else
            sent = current_bucket;

        current_bucket -= sent;

        printf("%d\t%d\t\t%d\t\t%d\t%d\t%d\n",
               i+1, incoming[i], accepted, dropped, sent, current_bucket);
    }

    return 0;
}
