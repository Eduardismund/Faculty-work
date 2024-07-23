#include <stdio.h>

void readSequences(int values[]) {
    int input;
    int maxSequenceMax = 0;
    int maxElement = 0;

    printf("Enter sequences of positive integers (each sequence ends with 0, all sequences end with -1):\n");

    while (1) {
        int sequenceMax = 0;
        int i = 0;

        do {
            scanf("%d", &input);
            values[i] = input;
            i++;

            if (input == -1) {
                if (sequenceMax > maxSequenceMax) {
                    maxSequenceMax = sequenceMax;
                }
                if (maxElement < maxSequenceMax) {
                    maxElement = maxSequenceMax;
                }
                printf("Maximum element of current sequence: %d\n", sequenceMax);
                printf("Global maximum element: %d\n", maxElement);
                return;
            }

            if (input > sequenceMax) {
                sequenceMax = input;
            }

            if (input > maxSequenceMax) {
                maxSequenceMax = input;
            }
        } while (input != 0);

        printf("Maximum element of current sequence: %d\n", sequenceMax);
    }
}

void findLongestContiguousSubsequence(int values[]) {
    int start, end;
    int maxLength = 0;
    int currentLength = 0;
    int maxStartIndex = -1;
    int maxEndIndex = -1;
    int currentIndex = 0;
    int longestStartIndex = -1;

    printf("Enter the start of the interval: ");
    scanf("%d", &start);
    printf("Enter the end of the interval: ");
    scanf("%d", &end);

    while (values[currentIndex] != -1) {
        if (values[currentIndex] >= start && values[currentIndex] <= end) {
            currentLength++;
            if (currentLength == 1) {
                maxStartIndex = currentIndex;
            }
            if (currentLength > maxLength) {
                maxLength = currentLength;
                maxEndIndex = currentIndex;
                longestStartIndex = maxStartIndex;
            }
        }
        else {
            currentLength = 0;
        }
        currentIndex++;
    }

    if (longestStartIndex != -1 && maxEndIndex != -1) {
        printf("Longest contiguous subsequence within the interval [%d, %d]:\n", start, end);
        for (int i = longestStartIndex; i <= maxEndIndex; i++) {
            printf("%d ", values[i]);
        }
        printf("\n");
    }
    else {
        printf("No contiguous subsequence found within the interval [%d, %d].\n", start, end);
    }
}


int main() {
    int choice;
    int values[100];

    do {
        printf("\nMenu:\n");
        printf("1. Read sequences of positive integer numbers\n");
        printf("2. Find the longest contiguous subsequence within a given interval\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readSequences(values);
                break;
            case 2:
                findLongestContiguousSubsequence(values);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
