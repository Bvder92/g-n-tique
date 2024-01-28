#ifndef GENETIQUE_H
#define SORT_H
#include "benchmark.h"
#include <limits.h> // Pour INT32_MIN
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Pour memcpy
#include <time.h>
#define PROB_MUT 3
#define PROB_NB_MUT 2
#define X 40

int s1[3];
int s2[2];
int s3[3];
int s4[3];
int s5[4];
int s6[2];

int **matrice;

BenchmarkParameters readBenchmarkParameters();

void print_tab(int *tab, int taille);

void print_tab2D(int **tab, int x, int y);

int *create_tab(int taille);

void init_tab(int taille, int *tab);

int **create_tab_2d(int x, int y);

void afficher_res_format(int **population, int taille_pop);

int *vectorize(int *sous_ensemble, int taille);

int *create_individu();

int *create_child(int *tab1, int *tab2);

int **mutation_child(int **tab, int taille);

bool is_solution(int *tab, int taille);

int *score(int **population, int taille_pop);

void genetique();

#endif
