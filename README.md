
# Gravitational Interactions Simulation using N-body Algorithm

This project provides a parallel implementation of the gravitational interactions simulation between particles using the N-body algorithm. The primary application of this simulation lies in astrophysical modeling to study the motion and interactions of celestial objects.

## Key Features

- **Optimized with OpenMP:** The code has been optimized using the OpenMP directive to efficiently leverage multi-core architectures, thereby enhancing the computational performance of gravitational interactions.

- **Performance Measurement:** The project includes performance measurement mechanisms, providing data such as execution time, interactions per second, and floating-point operations per second (GFLOP/s) to assess the effectiveness of the simulation.

- **Fine-Grained Result Analysis:** Fine-grained result analysis is conducted, including performance averaging, standard deviation, and other relevant measures to evaluate the robustness of the simulation.

- **Clear Result Presentation:** Results from each iteration of the simulation are presented clearly, facilitating easy understanding of performance evolution over time.

- **Memory Consumption Measurement:** The total size of the memory allocated for particle storage is calculated and displayed, offering an assessment of the program's impact on memory consumption.

## How to Use the Code

1. **Clone the Repository:** `git clone https://github.com/your_username/gravity-interactions-simulation.git`

2. **Compile the Code:** Use a compiler compatible with OpenMP to compile the code. For example, with GCC: `gcc -fopenmp main.c -o simulation`

3. **Run the Simulation:** `./simulation [number_of_particles]` (the number of particles is optional, default is 16384)

## Contribute

Any contributions are welcome! If you have optimization ideas, corrections, or additional features to introduce, feel free to open an issue or submit a pull request ! :) 


--- 

# Performance-Analysis-Computer-Architecture

This `Makefile` is used to compile, execute, and perform performance analysis on an N-Body simulation program. Here is an explanation of the contents of this `Makefile`:

1. **Compilers and Compilation Options**:
   - `CC=gcc`: Sets the GCC compiler.
   - `CL=clang`: Sets the Clang compiler.
   - `CFLAGS=-march=native -g3`: Common compilation options, specifying the native architecture and including debug information.

2. **Optimization Options**:
   - `OFLAGS`, `2FLAGS`, `3FLAGS`, `fastFLAGS`: Different optimization levels for GCC, specifying respectively the options `-O0`, `-O2`, `-O3`, and `-Ofast` with OpenMP enabled.

3. **List of Executables**:
   - `EXECS`: List of executables generated for different compilation configurations.

4. **Main Targets**:
   - `all`: Default target that compiles all executables specified in `EXECS`.
   - `max_performance`: Allocates maximum performance to all CPU cores using `cpupower`.
   - `allocate`: Launches executables on different CPU cores using `taskset`.
   - `execute`: Uses `perf` to record and report the performance of the executables.

5. **Individual Compilations**:
   - `nbody3D_1_GCC_O0` to `nbody3D_1_CLANG_Ofast`: Individual targets for each compilation configuration. Each target uses a specific compiler configuration, compilation options, and optimizations.

6. **Cleaning**:
   - `clean`: Removes temporary files, compilation-generated files, and performance report files.

7. **Performance Analysis**:
   - `execute`: Records performance using `perf` for each compilation configuration.

8. **Parallel Execution**:
   - `allocate`: Executes each compilation configuration on a specific CPU core.

9. **Maximum Performance**:
   - `max_performance`: Configures CPUs to operate at maximum frequency.

10. **Cleaning**:
    - `clean`: Deletes files generated during compilation and execution.

To run our program:

**Ensure that machine performance is maximized**:
   - Use the command `make max_performance`.

**Conduct performance analysis in root mode, especially for the `perf` command**:
   - `sudo -s`

**Ensure that the environment variable for `perf` is set to -1 for better results**:

**Run the program and find the results in the files `compiler_program_execution_output.txt`, and a `perf` evaluation in the file `compiler_program_execution_report.txt`**:
   - `make`
   - `make execute`

--- 

# Simulation des Interactions Gravitationnelles avec l'Algorithme N-corps

Ce projet propose une implémentation parallèle de la simulation des interactions gravitationnelles entre particules en utilisant l'algorithme N-corps. Cette simulation trouve son application principale dans la modélisation astrophysique pour étudier le mouvement et les interactions des objets célestes.

## Caractéristiques Principales

- **Optimisation avec OpenMP :** Le code a été optimisé à l'aide de la directive OpenMP pour exploiter efficacement les architectures multi-cœurs, améliorant ainsi les performances de calcul des interactions gravitationnelles.

- **Mesure des Performances :** Le projet inclut des mécanismes de mesure des performances, fournissant des données telles que le temps d'exécution, le nombre d'interactions par seconde, et les opérations en virgule flottante par seconde (GFLOP/s) pour évaluer l'efficacité de la simulation.

- **Analyse Fine des Résultats :** Une analyse fine des résultats est effectuée, avec une moyenne des performances, un écart-type, et d'autres mesures pertinentes pour évaluer la robustesse de la simulation.

- **Affichage Clair des Résultats :** Les résultats de chaque itération de la simulation sont présentés de manière claire, permettant une compréhension facile de l'évolution des performances au fil du temps.

- **Mesure de la Consommation Mémoire :** La taille totale de la mémoire allouée pour stocker les particules est calculée et affichée, offrant une évaluation de l'impact sur la consommation mémoire du programme.

## Comment Utiliser le Code

1. **Cloner le Répertoire :** `git clone https://github.com/votre_utilisateur/simulation-interactions-gravitationnelles.git`

2. **Compiler le Code :** Utilisez un compilateur compatible avec OpenMP pour compiler le code. Par exemple, avec GCC : `gcc -fopenmp main.c -o simulation`

3. **Exécuter la Simulation :** `./simulation [nombre_de_particules]` (le nombre de particules est facultatif, la valeur par défaut est 16384)

## Contribuer

Toute contribution est la bienvenue! Si vous avez des idées d'optimisation, des corrections ou des fonctionnalités à ajouter, n'hésitez pas à ouvrir une issue ou à soumettre une pull request :) 

---

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
    
