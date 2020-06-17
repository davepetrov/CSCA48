#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES

int status[3] = {0, 0, 0}; // AC, WA, TTL

void boolEqual(bool result, bool expect, int index, char * message) {
    bool passed = result == expect;
    if (result == expect) 
        status[0]++;
    else 
        status[1]++;
    status[2]++;
    printf("Test #%d %s. ", index, (passed) ? "Passed" : "Failed");
    if (!passed)
        printf("Expected: %s, got: %s. %s ***", (expect == 1) ? "false" : "true", (result == 1) ? "false" : "true", message);
    printf("\n");
}

void intEqual(int result, int expect, int index, char * message) {
    bool passed = result == expect;
    if (passed) 
        status[0]++;
    else 
        status[1]++;
    status[2]++;
    printf("Test #%d %s. ", index, (passed) ? "Passed" : "Failed");
    if (!passed)
        printf("Expected: %d, got: %d. %s ***", expect, result, message);
    printf("\n");
}

void floatEqual(double result, double expect, int index, char * message) {
    bool passed = result == expect;
    if (passed) 
        status[0]++;
    else 
        status[1]++;
    status[2]++;
    printf("Test #%d %s. ", index, (passed) ? "Passed" : "Failed");
    if (!passed)
        printf("Expected: %lf, got: %lf. %s ***", expect, result, message);
    printf("\n");
}

void charEqual(char result, char expect, int index, char * message) {
    bool passed = result == expect;
    if (passed) 
        status[0]++;
    else 
        status[1]++;
    status[2]++;
    printf("Test #%d %s. ", index, (passed) ? "Passed" : "Failed");
    if (!passed)
        printf("Expected: %c, got: %c. %s ***", expect, result, message);
    printf("\n");
}

void stringEqual(char * result, char * expect, int index, char * message) {
    bool passed = strcmp(result, expect) == 0;
    if (passed) 
        status[0]++;
    else 
        status[1]++;
    status[2]++;
    printf("Test #%d %s. ", index, (passed) ? "Passed" : "Failed");
    if (!passed)
        printf("Expected: %s, got: %s. %s ***", expect, result, message);
    printf("\n");
}

void pointerEqual(void * result, void * expect, int index, char * message) {
    bool passed = result == expect;
    if (passed) 
        status[0]++;
    else 
        status[1]++;
    status[2]++;
    printf("Test #%d %s. ", index, (passed) ? "Passed" : "Failed");
    if (!passed)
        printf("Expected: %p, got: %p. %s ***", expect, result, message);
    printf("\n");
}

void printResult() {
    printf("\n");
    printf("--------------- Results ---------------\n");
    printf("Passed: %d, Failed: %d, Total: %d\n", status[0], status[1], status[2]);
}