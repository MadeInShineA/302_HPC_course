# Exercice 4

Dans cet exercice, vous allez écrire un programme en C++ utilisant MPI pour répartir le calcul de la somme d’un tableau entre plusieurs processus. Le processeur de rang 0 commence par créer un tableau de nombres, qu’il divise en autant de parties qu’il y a de processus. Il envoie ensuite une partie du tableau à chaque processus à l’aide de **MPI_Scatter**.

Chaque processus reçoit sa portion du tableau, calcule la somme locale des éléments reçus, puis envoie cette somme au processeur de rang 0. Ce dernier utilise **MPI_Reduce** pour récupérer toutes les sommes locales et calculer la somme totale du tableau. Enfin, le résultat est affiché dans le terminal par le processus 0.

Option : Implémentez une variante pour laquelle tous les processeurs connaissant la somme totale à la fin du programme (**MPI_Allreduce**).