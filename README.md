# Problème du Set Cover et Algorithme Génétique

## Problème du Set Cover

Le Problème du Set Cover est un problème d'optimisation bien connu en informatique et en optimisation combinatoire. Étant donné un ensemble fini \( U \) et une collection de sous-ensembles \( S_i \) de \( U \), l'objectif est de trouver le nombre minimum de sous-ensembles dont l'union équivaut à l'ensemble entier \( U \).

### Énoncé du Problème

- **Entrée :** Un ensemble fini \( U \) et une collection de sous-ensembles \( S_i \) de \( U \).
- **Sortie :** Un sous-ensemble de taille minimale de \( S_i \) dont l'union couvre tous les éléments de \( U \).

## Algorithme Génétique

L'algorithme génétique est une méthode d'optimisation basée sur le processus évolutif naturel. Il utilise des concepts tels que la sélection, le croisement et la mutation pour évoluer une population d'individus vers une solution optimale.

### Aperçu de l'Algorithme

1. **Initialisation :** Créez une population initiale d'individus.
2. **Évaluation :** Évaluez la qualité de chaque individu en fonction de son aptitude au problème.
3. **Sélection :** Sélectionnez les individus les mieux adaptés pour le croisement.
4. **Croisement :** Croisez les paires sélectionnées pour créer une nouvelle génération.
5. **Mutation :** Appliquez des mutations à certains individus pour introduire de la diversité.
6. **Répétez :** Répétez les étapes 2-5 pour plusieurs générations.
   
### Structure du Benchmark

L'Algorithme récupère les informations de l'énoncé via un fichier .txt. 
Le benchmark est modifiable par l'utilisateur et peut être adapté aux besoins spécifiques du Problème du Set Cover.

## Utilisation

 Pour utiliser le projet, suivez ces étapes :

1. **Compilation :** Exécutez la commande `make` pour compiler le projet.
2. **Exécution :** Utilisez `./bin/main` pour lancer l'algorithme génétique.




