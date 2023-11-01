/*
    Author: Magaly Camacho
	Creation Date: 11/1/2023
	Lab: 8
	Description: Football Score Possibilities
    Input: A score
    Output: scoreCombinations.txt, but also printed in terminal
*/

#include <stdio.h>

void getCombinations (int SCORE, int currentScore, int i, int currentComb[5], FILE * OUTFILE) {
    int points[] = {8, 7, 6, 3, 2};

    // after recursing through 5 points options
    if (i == 5) {
        // if current score is right, print/write combinations
        if (currentScore == SCORE) {
            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n\t",
            currentComb[0], currentComb[1], currentComb[2], currentComb[3], currentComb[4]);

            fprintf(OUTFILE, "\t%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
            currentComb[0], currentComb[1], currentComb[2], currentComb[3], currentComb[4]);
        }
        return; // can stop now
    }

    // check each points option for each multiplier that will be less than or equal to score
    for (int multiplier = 0; multiplier * points[i] + currentScore <= SCORE; multiplier++) {
        currentComb[i] = multiplier;
        getCombinations(SCORE, currentScore + (multiplier * points[i]), i + 1, currentComb, OUTFILE);
    }
}

int main () {
    int SCORE;

    // open output file
    FILE * outputFile = fopen("scoreCombinations.txt", "w");
    if (outputFile == NULL) {
        printf("ERROR: Failed to open output file");
        return 1;
    }
    printf("! Note : output file will be ready after program stops.\n");

    // repeat until user wants to stop
    while (1) {
        // get score
        printf("\nEnter 0 or 1 to STOP\nEnter the NFL score: ");
        scanf("%i", &SCORE);

        // validate score
        if (SCORE < 0) {
            printf("Invalid score.\n");
            continue;
        } else if (SCORE == 0 || SCORE == 1) {
            printf("Stopping...");
            break;
        }

        // calculate/print/write combinations
        printf("Possible combinations of scoring plays:\n\t");
        fprintf(outputFile, "Score: %d\nPossible combinations of scoring plays:\n", SCORE);
        int combination[5] = {0, 0, 0, 0, 0};
        getCombinations(SCORE, 0, 0, combination, outputFile);
    }

    // close file to save
    fclose(outputFile);

    return 0;
}

