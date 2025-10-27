# Exercice 6

Dans cet exercice, vous allez écrire un programme en C++ utilisant MPI pour effectuer une collecte de données entre plusieurs processus. Chaque processus doit commencer par créer un tableau d'entiers aléatoires, dont la taille est de 1'000'000. Une fois le tableau créé, chaque processus calcule le maximum des valeurs qu’il contient.

Ensuite, tous les processus envoient leur valeur maximale au processus de rang 0 en utilisant la fonction MPI_Gather. Le processus 0 reçoit alors un tableau contenant les maximums de tous les autres processus, et l’affiche dans le terminal.