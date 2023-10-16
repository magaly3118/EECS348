/*
    Author: Magaly Camacho
	Creation Date: 10/11/2023
	Lab: 5
	Description: Sales problem program
    Input: salesData.txt
    Output: salesReport.txt, but also printed in terminal
*/

#include <stdio.h>

// function to check if given file was opened correctly 
int file_error(FILE * file, char name[]) {
    if (file == NULL) {
        printf("ERROR: Failed to open the %s file\n", name);
        return 1;
    }

    return 0;
}

int main () {
    // ARRAYS OF MONTHS
    char * MONTHS_TAB[] = {
        "January\t", "February", "March\t", "April\t", "May\t\t", "June\t", "July\t", 
        "August\t", "September", "October\t", "November", "December"
    };

    char * MONTHS[] = {
        "January", "February", "March", "April", "May", "June", "July", 
        "August", "September", "October", "November", "December"
    };

    // GET INPUT FILE
    FILE * inputFile = fopen("salesData.txt", "r");
    if (file_error(inputFile, "input") == 1) return 1;

    // SAVE SALES (READ THROUGH INPUT FILE)
    double sales[12];

    for (int i = 0; i < 12; i++) {
        if( fscanf(inputFile, "%lf", &sales[i]) != 1 ) {
            printf("ERROR: Failed to read line %i from input file\n", i);
            return 2;
        }
    }
     
    // CLOSE INPUT FILE
    fclose(inputFile);

    // GET OUTPUT FILE
    FILE * outputFile = fopen("salesReport.txt", "w");
    if (file_error(outputFile, "output") == 1) return 3;

    // MONTHLY SALES 
    fprintf(outputFile, "Monthly Sales Report:\n\tMONTH\t\tSALES\n");
    printf("Monthly Sales Report:\n\tMONTH\t\tSALES\n");

    for (int i = 0; i < 12; i++) {
        fprintf(outputFile, "\t%s\t$%.2lf\n", MONTHS_TAB[i], sales[i]);
        printf("\t%s\t$%.2lf\n", MONTHS_TAB[i], sales[i]);
    }

    // SALES SUMMARY
    double min = sales[0], max = sales[0], total = sales[0], average;
    int minMonth = 0, maxMonth = 0;

    // get summary data
    for (int i = 1; i < 12; i++) { // loop through sales and find min, max and total
        if (sales[i] < min) {
            min = sales[i];
            minMonth = i;
        } 
        if (sales[i] > max) { 
            max = sales[i];
            maxMonth = i;
        }
        total += sales[i]; 
    }
    average = total / 12;

    // print/write data
    fprintf(outputFile, "\nSales Summary:\n");
    fprintf(outputFile, "\tMinimum sales:\t$%.2lf\t(%s)\n", min, MONTHS[minMonth]);
    fprintf(outputFile, "\tMaximum sales:\t$%.2lf\t(%s)\n", max, MONTHS[maxMonth]);
    fprintf(outputFile, "\tAverage sales:\t$%.2lf\n", average);
    printf("\nSales Summary:\n");
    printf("\tMinimum sales:\t$%.2lf\t(%s)\n", min, MONTHS[minMonth]);
    printf("\tMaximum sales:\t$%.2lf\t(%s)\n", max, MONTHS[maxMonth]);
    printf("\tAverage sales:\t$%.2lf\n", average);

    // SIX MONTH MOVING AVERAGE REPORT
    fprintf(outputFile, "\nSix-Month Moving Average Report:\n");
    printf("\nSix-Month Moving Average Report:\n");
    for (int i = 0; i < 7; i++) {
        double sixMonthTotal = sales[i], sixMonthAverage;

        for (int j = 1; j < 6; j++) {
            sixMonthTotal += sales[i + j];
        }
        
        sixMonthAverage = sixMonthTotal / 6;
        fprintf(outputFile, "\t%s -\t%s\t$%.2lf\n", MONTHS_TAB[i], MONTHS_TAB[i+5], sixMonthAverage);
        printf("\t%s -\t%s\t$%.2lf\n", MONTHS_TAB[i], MONTHS_TAB[i+5], sixMonthAverage);
    }

    // SALES REPORT (HIGHEST TO LOWEST)
    // pass
    fprintf(outputFile, "\nSales Report (Highest to Lowest):\n\tMONTH\t\tSALES\n");
    printf("\nSales Report (Highest to Lowest):\n\tMONTH\t\tSALES\n");

    double prevMax = -1, currentMax = sales[0]; 
    int currentIndex = 0, prints = 0;

    for (int prints = 0; prints < 12; prints++) {
        for (int i = 0; i < 12; i++) {
            if (sales[i] > currentMax && (sales[i] < prevMax || prevMax == -1)) {
                currentMax = sales[i];
                currentIndex = i;
            }
        }
        
        fprintf(outputFile, "\t%s\t$%.2lf\n", MONTHS_TAB[currentIndex], currentMax);
        printf("\t%s\t$%.2lf\n", MONTHS_TAB[currentIndex], currentMax);
        
        prevMax = currentMax;
        currentMax = sales[0];
        currentIndex = 0;
    }

    // CLOSE OUTPUT FILE TO SAVE
    fclose(outputFile);

    return 0;

}
