#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define true 1
#define false 0

/*
 * Version 0.0.1
 *
 * Capabilities:
 *  1 - Reads data from txt file.
 *  2 - Sorts data set.
 *  3 - Calculates mean (Population).
 *  4 - Calculates median.
 *  5 - Calculates standard deviation (Population).
 *  6 - Calculates variance (Population).
 *  7 - Opens a new file, prints the sorted version of data set into this new file and prints each result.
 * */

// Functions.
void calc_mean(double *mean, double const *array, int size);
void calc_median(double *median, double const *array, int size);
void calc_dev_var(double const *array, double mean, double *deviation, double *variance, int size);
void bubble_sort(double *array, int size);
void swap(double *a, double *b);
void write_log(double const *array, double mean, double median, double deviation, double varience, int size);

int main(void){
    // Brief information.
    printf("\n\nHi, welcome to the statistiCs program!\nThis program has been written purely for educational\npurposes and does not offer any professional results.\nTherefore, it is not recommended for business use.\n\nIn short, statistiCs does the following calculations:\n\t1) Mean\n\t2) Median\n\t3) Standart deviation\n\t4) Standart variance\n\nAnd sorts the dataset.\nNOTE: It only works with finite discrete datasets!\nYou need to input a txt file name located in the same directory as the program.\n\n");
    char cFlag;


    while(true){
        printf("\nTo continue, type 'c'.\nTo quit, type 'q'\n:");
        scanf(" %c",&cFlag);


        // Quit.
        if(cFlag == 'q'){
            printf("Goodbye.\n");
            return 0;
        }

        // Continue.
        else if(cFlag == 'c'){
            while(true){
                // Sample array declaration with dynamic memory allocation.
                int iSize,i=0;
                printf("How many samples do you have in your data set?\n:");
                scanf("%d",&iSize);
                double *dSampleArray = malloc(sizeof(double)*iSize);


                // File name input.
                char sFileName[50];
                printf("Enter the file name:");
                fscanf(stdin,"%s",&sFileName);
                getchar();
                FILE *file_in = fopen(sFileName, "r");


                // File not found.
                if(file_in == NULL){
                    printf("File not found.\n");
                }

                // File exists.
                else{
                    // Array insertion.
                    char sCopy[20]; // Copy string.
                    double dMean=0, dMedian=0, dDev=0, dVar=0;
                    for(i=0; i<iSize; i++){
                        if(fgets(sCopy,20,file_in) != NULL){
                            sscanf(sCopy,"%lf",&dSampleArray[i]);
                            //printf("%lf\n",dSampleArray[i]); DEBUG
                        }
                    }

                    // Function calls.
                    bubble_sort(dSampleArray,iSize);
                    calc_mean(&dMean,dSampleArray,iSize);
                    calc_median(&dMedian,dSampleArray,iSize);
                    calc_dev_var(dSampleArray,dMean,&dDev,&dVar,iSize);

                    // Output.
                    printf("\nMean: %lf\nMedian: %lf\nStandart dev: %lf\nVariance: %lf\n\n",dMean,dMedian,dDev,dVar);
                    write_log(dSampleArray,dMean,dMedian,dDev,dVar,iSize);
                    free(dSampleArray);
                    fclose(file_in);
                }
                break;
            }
        }

        // Invalid input.
        else{
            printf("Invalid input.\n");
        }
    }
}


// To use under bubble sort.
void swap(double *a, double *b){
    double dTemp = *a;
    *a = *b;
    *b = dTemp;
}


// Sorting.
void bubble_sort(double *array, int size){
    int i,j;
    double dTemp;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(array[i] < array[j]){
                swap(&array[i],&array[j]);
            }
        }
    }
}


// Mean calculator.
void calc_mean(double *mean, double const *array, int size){
    int i=0;
    for(i=0; i<size; i++){
        *mean = *mean + array[i];
    }
    *mean = *mean / (double)i;
}


// Median calculator.
void calc_median(double *median, double const *array, int size){
    // Even & Odd comparison.
    switch(size%2){
        // Even.
        case 0:
            *median=(array[size/2]+array[(size/2)+1])/2;
            break;

        // Odd.
        default:
            *median=array[(size+1)/2];
            break;
    }
}


// Since the variance is the square of the deviation,
// it will be more practical to calculate these two results
// under the same function.
void calc_dev_var(double const *array, double mean, double *deviation, double *variance, int size){
    int i=0;
    double dTemp=0, dTemp2=0;
    for(i=0; i<size; i++){
        *variance = *variance + ((array[i]-mean)*(array[i]-mean))/size;
    }
    *deviation = sqrt(*variance);
}


// For log files.
void write_log(double const *array, double mean, double median, double deviation, double varience, int size){
    // Required for log file details.
    char sLogName[50];
    printf("Enter the log file name\n:");
    scanf("%s",&sLogName);
    time_t sLogTime;
    time(&sLogTime);

    FILE *file_log = fopen(sLogName,"w+");
    fprintf(file_log,"Date&time: %s\n\nResults:\nMean: %lf\nMedian: %lf\nStd dev: %lf\nVariance: %lf\nNumber of data collected: %d\n\nSorted data:\n", ctime(&sLogTime),mean,median,deviation,varience,size);
    int i=0;
    for(i=0; i<size; i++){
        fprintf(file_log,"%lf\n",array[i]);
    }
    fclose(file_log);
}