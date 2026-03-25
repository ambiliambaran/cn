#include <stdio.h>

#define MAX 10
#define INF 9999

int main() {
    int n, i, j, k;
    int cost[MAX][MAX], dist[MAX][MAX], via[MAX][MAX];

    printf("Distance Vector Routing\n");

    printf("\nEnter number of nodes: ");
    scanf("%d", &n);

    printf("\nEnter cost matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];

            if(i == j)
                via[i][j] = i;
            else if(cost[i][j] != INF)
                via[i][j] = j;
            else
                via[i][j] = -1;
        }
    }

    // DVR Algorithm
    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {

                if(dist[i][k] != INF && dist[k][j] != INF &&
                   dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                    via[i][j] = via[i][k];
                }
            }
        }
    }

    // PRINT TABLE
    for(i = 0; i < n; i++) {
        printf("\n\nRouting Table for Router %d\n", i+1);
        printf("-------------------------------------------------\n");
        printf("Destination\tNext Hop\tDistance\n");
        printf("-------------------------------------------------\n");

        for(j = 0; j < n; j++) {
            if(via[i][j] == -1)
                printf("%d\t\t-\t\tINF\n", j+1);
            else
                printf("%d\t\t%d\t\t%d\n", j+1, via[i][j]+1, dist[i][j]);
        }
        printf("-------------------------------------------------\n");
    }

    // PRINT PATHS
    printf("\n\nPaths between nodes:\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i != j && via[i][j] != -1) {
                printf("Path from %d to %d: %d", i+1, j+1, i+1);

                int u = i;
                while(u != j) {
                    u = via[u][j];
                    printf(" -> %d", u+1);
                }
                printf("\n");
            }
        }
    }

    return 0;
}
