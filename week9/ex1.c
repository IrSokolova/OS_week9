#include <stdio.h>
#include <limits.h>

typedef struct page {
    int number;
    unsigned int counter;
    int reference;
    int clock;
} page;

int exists(page pages[], int number, int m) {
    for (int i = 0; i < m; ++i) {
        if (pages[i].number == number)
            return 1;
    }
    return 0;
}

int pageToReplace(page pages[], int n) {
    int minCount = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < n; ++i) {
        if (pages[i].counter < minCount) {
            minIndex = i;
            minCount = pages[i].counter;
        }
    }
    return minIndex;
}

int main() {
    int n;
    int m;
    scanf("%d %d", &n, &m);
    page pageFrames[n];
    int clock;
    int number;
    page pages[m];

    int hits = 0;
    int misses = 0;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &clock, &number);
        pages[i].clock = clock;
        pages[i].number = number;
        pages[i].counter = 0;
        pages[i].reference = 0;
    }

    pageFrames[0] = pages[0];
    pages[0].reference = 1;
    printf("0\n");
    misses++;

    for (int i = 1; i < m; ++i) {
        if (pages[i].clock == pages[i-1].clock) {
            if (i < n) {
                pageFrames[i] = pages[i];
                pages[i].reference = 1;
                misses++;
                printf("0\n");
            } else if (exists(pageFrames, pages[i].number, n)) {
                hits++;
                pages[i].reference = 1;
                printf("1\n");
            } else {
                pageFrames[pageToReplace(pageFrames, n)] = pages[i];
                misses++;
                pages[i].reference = 1;
                pages[i].counter = 0;
                printf("0\n");
            }
        } else {
            for (int j = 0; j < n; ++j) {
                pageFrames[j].counter =
                        (pageFrames[j].counter >> 1) | (pageFrames[j].reference << 7);
                pageFrames[j].reference = 0;
            }
            if (i < n) {
                pageFrames[i] = pages[i];
                pages[i].reference = 1;
                misses++;
                printf("0\n");
            } else if (exists(pageFrames, pages[i].number, n)) {
                hits++;
                pages[i].reference = 0;
                printf("1\n");
            } else {
                pageFrames[pageToReplace(pageFrames, n)] = pages[i];
                misses++;
                pages[i].reference = 1;
                pages[i].counter = 0;
                printf("0\n");
            }
        }
    }


    double hitMisRatio = 0.0;

    hitMisRatio = (double) hits / (double) misses;

    printf("%f \n", hitMisRatio);
}