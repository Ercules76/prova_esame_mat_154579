//
// Created by madagos on 5/19/17.
//

#ifndef PROVA_ESAME_UTILS_H
#define PROVA_ESAME_UTILS_H

#define ARRAYLENGTH(x) sizeof(x) / sizeof(*x)

void printStrAt(int, int, char*);
void printIntAt(int, int, int);
void inputStrAt(int, int, char*);
void fInputStrAt(int, int, char*);
void inputDataAt(int, int, char*, char*, char*);
void inputIntAt(int, int, int *);
void cursorAt(int, int);
void cls();
void box(int, int, int, int);
void separator(int, int, int);
void drawWall(int, int, int);
void clsRow(int, int, int);

#endif //PROVA_ESAME_UTILS_H
