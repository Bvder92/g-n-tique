#include "../include/genetique.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  BenchmarkParameters params = readBenchmarkParameters();
  
  int tailleIndividu = params.tailleIndividu;
  int tailleEnsemble = params.tailleEnsemble;
  int taillePopulation = params.populationSize;
  
  matrice = (int **)malloc(sizeof(int *) * tailleIndividu);
  for (int i = 0; i < tailleIndividu; ++i) {
    matrice[i] = malloc(sizeof(int) * tailleEnsemble);
  }
  
  for (int i = 0; i < tailleIndividu; ++i) {
    memcpy(matrice[i], params.matriceEnsembles[i], tailleEnsemble * sizeof(int));
  }

  printf("Taille d'un individu : %d\n", tailleIndividu);
  printf("Taille d'un ensemble : %d\n", tailleEnsemble);
  printf("Taille de la population : %d\n", taillePopulation);
  printf("\n\n");

  genetique();

  return 0;
}
