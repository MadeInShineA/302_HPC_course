# Exercice 1

Dans cet exercice, vous allez reprendre le tout premier programme du laboratoire (_Hello World_) et le modifier pour qu’il fonctionne avec MPI. L’objectif est d’afficher (Processor X - Hello World) dans le terminal en utilisant les fonctions de base de MPI.

Votre programme devra obligatoirement contenir au minimum les appels à MPI_Init et MPI_Finalize. Vous utiliserez également MPI_Comm_size pour connaître le nombre total de processus, et MPI_Comm_rank pour identifier le rang de chaque processus. Le programme sera lancé avec mpirun, ce qui permettra d’exécuter plusieurs instances en parallèle.

Que remarquez-vous ?

Exemple de résultat avec 6 processeurs:

Number of processors: 6\
Processor 0 - Hello World\
Processor 5 - Hello World\
Processor 1 - Hello World\
Processor 2 - Hello World\
Processor 3 - Hello World\
Processor 4 - Hello World