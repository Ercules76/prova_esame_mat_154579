//
// Created by Vittorio Pinti on 5/19/17.
//

#include <stdio.h>
#include <ctype.h>

void printStrAt(int r, int c, char *s) {
    printf("\033[%d;%dH%s", r, c, s);
}

void printIntAt(int r, int c, int n) {
    printf("\033[%d;%dH%d", r, c, n);
}

void inputStrAt(int r, int c, char *s) {
    printf("\033[%d;%dH",r, c);
    scanf("%s", s);
}

void fInputStrAt(int r, int c, char *s) {
    printf("\033[%d;%dH",r, c);
    fgets(s, 60, stdin);
}

void inputDataAt(int r, int c, char *day, char *month, char* year) {
    printf("\033[%d;%dH",r, c);
    scanf("%s%s%s", day, month, year);
}

void inputIntAt(int r, int c, int *n) {
    printf("\033[%d;%dH", r, c);
    scanf("%d", n);
}

void cursorAt(int r, int c) {
    printf("\033[%d;%dH", r, c);
}

void cls() {
    printf("\033[2J");
}

void clsRow(int r1, int c1, int c2) {
   int k;
    for(k = c1; k <= c2; k++)
        printf("\033[%d;%dH ",r1, k);
}

void separator(int r1, int c1, int c2) {
    int k;
    for(k = c1+1; k < c2; k++ )
        printf("\033[%d;%dH-", r1, k);
}

void drawWall(int r1, int r2, int c) {
    int k;
    for(k = r1; k < r2; k++) {
        printf("\033[%d;%dH|", k, c);
    }
}

void box(int r1, int c1, int r2, int c2) {
    int k;
    for(k = r1; k<=r2; k++) {
        printf("\033[%d;%dH!", k, c1);
        printf("\033[%d;%dH!", k, c2);
    }
    for(k = c1+1; k < c2; k++) {
        printf("\033[%d;%dH-", r1, k);
        printf("\033[%d;%dH-", r2, k);
    }
}
