# Performance-Analysis-Computer-Architecture

Ce `Makefile` est utilisé pour compiler, exécuter et effectuer des analyses de performance sur un programme de simulation N-Body. Voici une explication du contenu de ce `Makefile` :

1. **Compilateurs et options de compilation**:
   - `CC=gcc`: Définit le compilateur GCC.
   - `CL=clang`: Définit le compilateur Clang.
   - `CFLAGS=-march=native -g3`: Options de compilation communes, spécifiant l'architecture native et incluant des informations de débogage.

2. **Options d'optimisation**:
   - `OFLAGS`, `2FLAGS`, `3FLAGS`, `fastFLAGS`: Différents niveaux d'optimisation pour GCC, spécifiant respectivement les options `-O0`, `-O2`, `-O3` et `-Ofast` avec OpenMP activé.

3. **Liste des exécutables**:
   - `EXECS`: Liste des exécutables générés pour différentes configurations de compilation.

4. **Cibles principales**:
   - `all`: Cible par défaut qui compile tous les exécutables spécifiés dans `EXECS`.
   - `max_performance`: Alloue les performances maximales à tous les cœurs CPU à l'aide de `cpupower`.
   - `allocate`: Lance les exécutables sur différents cœurs CPU à l'aide de `taskset`.
   - `execute`: Utilise `perf` pour enregistrer et rapporter les performances des exécutables.

5. **Compilations individuelles**:
   - `nbody3D_1_GCC_O0` à `nbody3D_1_CLANG_Ofast`: Cibles individuelles pour chaque configuration de compilation. Chaque cible utilise une configuration spécifique du compilateur, des options de compilation et des optimisations.

6. **Nettoyage**:
   - `clean`: Supprime les fichiers temporaires, les fichiers générés par la compilation, et les fichiers de rapports de performances.

7. **Analyses de performance**:
   - `execute`: Enregistre les performances à l'aide de `perf` pour chaque configuration de compilation.

8. **Exécution en parallèle**:
   - `allocate`: Exécute chaque configuration de compilation sur un cœur de CPU spécifique.

9. **Performance maximale**:
   - `max_performance`: Configure les CPU pour fonctionner à la fréquence maximale.

10. **Nettoyage**:
    - `clean`: Supprime les fichiers générés pendant la compilation et l'exécution.

Pour exécuter notre programme : 

**S'assurer à ce que les performances de la machine soit maximales**: 
    - Via la commande make max_performance

**Dérouler l'analyse de performance en mode root, notamment pour la commande perf**

    - sudo -s 

**S'assurer à ce que la variable d'environnement pour le perf est à -1 pour de meilleurs résultats** : 

**Exécuter le programme et retrouver les résultats dans les fichiers  compilateur_nom_du_programme_execution_output.txt et une évaluation de perf dans le fichier compilateur_nom_du_programme_execution_report.txt** 

    - make  
    - make execute 
    
