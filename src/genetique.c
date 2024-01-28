#include "../include/genetique.h"
int **matrice = NULL;
BenchmarkParameters params;

BenchmarkParameters readBenchmarkParameters() {
  FILE *file = fopen("benchmark.txt", "r");
  if (file == NULL) {
    perror("Erreur lors de l'ouverture du fichier de benchmark");
    exit(1);
  }

  // BenchmarkParameters params;
  fscanf(file, "TailleIndividu %d\n", &params.tailleIndividu);
  fscanf(file, "TailleEnsemble %d\n", &params.tailleEnsemble);
  fscanf(file, "TaillePopulation %d\n", &params.populationSize);

  // Allouer de la mémoire pour matriceEnsembles et la remplir
  params.matriceEnsembles = malloc(params.tailleIndividu * sizeof(int *));

  for (int i = 0; i < params.tailleIndividu; i++) {
    params.matriceEnsembles[i] =
        (int *)malloc(params.tailleEnsemble * sizeof(int));

    for (int j = 0; j < params.tailleEnsemble; j++) {
      fscanf(file, "%d", &params.matriceEnsembles[i][j]);
    }
  }
  fclose(file);
  return params;
}

void print_tab(int *tab, int taille) {
  for (int i = 0; i < taille; ++i) {
    if (i != taille - 1) {
      printf("%d | ", tab[i]);
    } else {
      printf("%d\n", tab[i]);
    }
  }
}

void print_tab2D(int **tab, int x, int y) {
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      printf("%d |", tab[i][j]);
    }
    printf("\n");
  }
}

int *create_tab(int taille) {
  int *tableau = malloc(sizeof(int) * taille);
  if (tableau == NULL) {
    fprintf(stderr, "Échec de l'allocation de mémoire dans create_tab\n");
    exit(1);
  }
  return tableau;
}

void init_tab(int taille, int *tab) {
  for (int i = 0; i < taille; ++i) {
    tab[i] = i + 1;
  }
}

int **create_tab_2d(int x, int y) {
  int **tableau = malloc(sizeof(int *) * x);
  if (tableau == NULL) {
    fprintf(stderr, "Échec de l'allocation de mémoire dans create_tab_2d (1ère "
                    "dimension)\n");
    exit(1);
  }
  for (int i = 0; i < x; ++i) {
    tableau[i] = malloc(sizeof(int) * y);
    if (tableau[i] == NULL) {
      fprintf(stderr, "Échec de l'allocation de mémoire dans create_tab_2d "
                      "(2ème dimension)\n");
      exit(1);
    }
  }
  return tableau;
}

void afficher_res_format(int **population, int taille_pop) {
  printf("   -  A  B  C  D  E  F  -\n");
  for (int i = 0; i < taille_pop; i++) {
    printf("* %02d: ", i);
    for (int j = 0; j < params.tailleIndividu; j++) {
      if (population[i][j] == 1) {
        printf("X  ");
      } else {
        printf("   ");
      }
    }
    printf("\n");
  }
}

int *vectorize(int *sous_ensemble, int taille) {
  int *vecteur = calloc(params.tailleEnsemble, sizeof(int));
  if (vecteur == NULL) {
    fprintf(stderr, "Échec de l'allocation de mémoire dans vectorize\n");
    exit(1);
  }
  for (int i = 0; i < taille; ++i) {
    vecteur[sous_ensemble[i] - 1] = 1;
  }
  return vecteur;
}

int *create_individu() {
  int *individu = malloc(sizeof(int) * params.tailleIndividu);
  if (individu == NULL) {
    fprintf(stderr, "Échec de l'allocation de mémoire dans create_individu\n");
    exit(1);
  }
  for (int i = 0; i < params.tailleIndividu; ++i) {
    individu[i] = rand() % 2;
  }
  return individu;
}

int *create_child(int *tab1, int *tab2) {
  int *child = malloc(sizeof(int) * params.tailleIndividu);
  if (child == NULL) {
    fprintf(stderr, "Échec de l'allocation de mémoire dans create_child\n");
    exit(1);
  }
  int i;
  for (i = 0; i < 3; ++i) {
    child[i] = tab1[i];
  }

  for (i = 3; i < params.tailleIndividu; ++i) {
    child[i] = tab2[i];
  }
  return child;
}

int **mutation_child(int **tab, int taille) {

  for (int i = 0; i < taille; i++) {
    if ((rand() % 10) + 1 <= PROB_MUT) {
      for (int j = 0; j < params.tailleIndividu; j++) {
        if ((rand() % 10) + 1 <= PROB_NB_MUT) {
          if (tab[i][j] == 0) {
            tab[i][j] = 1;
          } else {
            tab[i][j] = 0;
          }
        }
      }
    }
  }
  return tab;
}

bool is_solution(int *tab, int taille) {
  int *solution = calloc(params.tailleEnsemble, sizeof(int));
  for (int i = 0; i < params.tailleIndividu; ++i) {
    if (tab[i] == 1) {
      // Nous allons récuperer l'ensemble correspondant a cette indice et
      // parcourir le tableau
      for (int j = 0; j < params.tailleEnsemble; j++) {
        if (matrice[i][j] == 1) {
          solution[j] = 1;
        }
      }
    }
  }
  // On vérifie si l'ensemble est bien une solution ou non
  for (int i = 0; i < params.tailleEnsemble; ++i) {
    if (solution[i] == 0) {
      return false;
    }
  }
  return true;
}

int *score(int **population, int taille_pop) {
  int *scores = malloc(sizeof(int) * taille_pop);
  if (scores == NULL) {
    fprintf(stderr, "Échec de l'allocation de mémoire pour les scores\n");
    exit(1);
  }

  for (int i = 0; i < taille_pop; i++) {
    if (is_solution(population[i], params.tailleIndividu)) {
      // Compter le nombre de zéros dans l'individu
      int score = 0;
      for (int j = 0; j < params.tailleIndividu; j++) {
        if (population[i][j] == 0) {
          score++;
        }
      }
      scores[i] = score;
    } else {
      // Si ce n'est pas une solution, attribuer un score bas (INT_MIN)
      scores[i] = INT_MIN;
    }
  }

  return scores;
}

void genetique() {
  int i;
  int taille_pop2 = params.populationSize * 2;

  int **parents = malloc(sizeof(int *) * params.populationSize);
  int **enfants = malloc(sizeof(int *) * params.populationSize);
  int **select = malloc(sizeof(int *) * taille_pop2);
  int *tab_score = malloc(sizeof(int) * taille_pop2);

  // Initialisation de la population parentale
  for (int j = 0; j < params.populationSize; j++) {
    parents[j] = create_individu();
  }

  i = 0;
  while (i < X) {
    // Générer les enfants et appliquer des mutations
    for (int i = 0; i < params.populationSize; i += 2) {
      enfants[i] = create_child(parents[i], parents[i + 1]);
      enfants[i + 1] = create_child(parents[i + 1], parents[i]);
    }

    enfants = mutation_child(enfants, params.populationSize);

    // Le tableau select (taille 40) reçoit les enfants et les parents
    for (int j = 0; j < params.populationSize; ++j) {
      select[j] = enfants[j];
    }
    for (int j = params.populationSize; j < taille_pop2; ++j) {
      select[j] = parents[j - params.populationSize];
    }

    // Calcul des scores pour la population
    tab_score = score(select, taille_pop2);

    // Trier la population en fonction des scores (tri à bulles)
    for (int i = 0; i < taille_pop2 - 1; i++) {
      int swapped = 0;
      for (int j = 0; j < taille_pop2 - i - 1; j++) {
        if (tab_score[j] < tab_score[j + 1]) {
          // Échanger les scores
          int temp = tab_score[j];
          tab_score[j] = tab_score[j + 1];
          tab_score[j + 1] = temp;
          // Échanger les individus dans la population
          int *tmp = select[j];
          select[j] = select[j + 1];
          select[j + 1] = tmp;
          swapped = 1;
        }
      }
      if (swapped == 0) {
        break;
      }
    }

    // Conserver les meilleurs individus (20 premiers)
    int **meilleurs_individus = malloc(sizeof(int *) * params.populationSize);
    for (int j = 0; j < params.populationSize; j++) {
      meilleurs_individus[j] = malloc(sizeof(int) * params.tailleIndividu);
      memcpy(meilleurs_individus[j], select[j],
             sizeof(int) * params.tailleIndividu);
    }

    // Libérer la mémoire de la population parentale
    for (int j = 0; j < params.populationSize; j++) {
      free(parents[j]);
    }
    free(parents);

    // Mettre à jour la population parentale avec les meilleurs individus
    parents = meilleurs_individus;

    ++i;
  }

  // Afficher les résultats
  afficher_res_format(parents, params.populationSize);

  // Libérer la mémoire
  for (int i = 0; i < params.populationSize; ++i) {
    free(parents[i]);
    free(enfants[i]);
  }
  free(parents);
  free(enfants);
  free(select);
  free(tab_score);
}
