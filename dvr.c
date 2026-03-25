#include <stdio.h>

#define MAX 10
#define INF 9999

int main() {
    int cost[MAX][MAX], dist[MAX][MAX], next[MAX][MAX];
    int n, i, j, k;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            next[i][j] = j;
        }
    }

    // Distance Vector Algorithm
    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Print routing table
    for(i = 0; i < n; i++) {
        printf("\nRouting table for node %d:\n", i+1);
        printf("Destination\tNext Hop\tDistance\n");
        for(j = 0; j < n; j++) {
            printf("%d\t\t%d\t\t%d\n", j+1, next[i][j]+1, dist[i][j]);
        }
    }

    return 0;
}
