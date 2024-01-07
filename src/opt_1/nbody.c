#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Définition d'un type pour représenter une particule
typedef float              f32;
typedef double             f64;
typedef unsigned long long u64;

// Structure représentant une particule
typedef struct particle_s {
  f32 x, y, z;   // Positions de la particule dans l'espace
  f32 vx, vy, vz; // Vitesses de la particule dans chaque direction
} particle_t;

// Initialisation des positions et vitesses des particules
void init(particle_t *p, u64 n)
{
  for (u64 i = 0; i < n; i++)
  {
    u64 r1 = (u64)rand();
    u64 r2 = (u64)rand();
    f32 sign = (r1 > r2) ? 1 : -1;

    p[i].x = sign * (f32)rand() / (f32)RAND_MAX;
    p[i].y = (f32)rand() / (f32)RAND_MAX;
    p[i].z = sign * (f32)rand() / (f32)RAND_MAX;

    p[i].vx = (f32)rand() / (f32)RAND_MAX;
    p[i].vy = sign * (f32)rand() / (f32)RAND_MAX;
    p[i].vz = (f32)rand() / (f32)RAND_MAX;
  }
}

// Fonction pour déplacer les particules en fonction des interactions gravitationnelles
void move_particles(particle_t *p, const f32 dt, u64 n)
{
  const f32 softening = 1e-20;

  // Pour toutes les particules, calculer les forces nettes
  #pragma omp parallel for
  for (u64 i = 0; i < n; i++)
  {
    f32 fx = 0.0;
    f32 fy = 0.0;
    f32 fz = 0.0;

    // Calculer la force nette
    #pragma omp parallel for reduction(+:fx, fy, fz)
    for (u64 j = 0; j < n; j++)
    {
      if (i != j)  // Éviter l'auto-interaction
      {
        const f32 dx = p[j].x - p[i].x;
        const f32 dy = p[j].y - p[i].y;
        const f32 dz = p[j].z - p[i].z;

        const f32 d_2 = (dx * dx) + (dy * dy) + (dz * dz) + softening;
        const f32 d_3_over_2 = 1.0 / sqrt(d_2 * d_2 * d_2);

        fx += dx * d_3_over_2;
        fy += dy * d_3_over_2;
        fz += dz * d_3_over_2;
      }
    }

    // Mettre à jour les vitesses des particules en utilisant la force nette précédemment calculée
    p[i].vx += dt * fx;
    p[i].vy += dt * fy;
    p[i].vz += dt * fz;
  }

  // Mettre à jour les positions des particules
  #pragma omp parallel for
  for (u64 i = 0; i < n; i++)
  {
    p[i].x += dt * p[i].vx;
    p[i].y += dt * p[i].vy;
    p[i].z += dt * p[i].vz;
  }
}

// Fonction principale
int main(int argc, char **argv)
{
  // Nombre de particules à simuler (peut être spécifié en ligne de commande)
  const u64 n = (argc > 1) ? atoll(argv[1]) : 16384;

  // Nombre d'itérations de la simulation
  const u64 steps = 13;

  // Pas de temps
  const f32 dt = 0.01;

  // Variables pour mesurer les performances
  f64 rate = 0.0, drate = 0.0;

  // Nombre d'itérations à ignorer pour le chauffage (warm-up)
  const u64 warmup = 3;

  // Allouer de la mémoire pour les particules
  particle_t *p = malloc(sizeof(particle_t) * n);

  // Calculer et afficher la taille totale de la mémoire allouée
  const u64 s = sizeof(particle_t) * n;
  printf("\n\033[1mTaille totale de la mémoire allouée:\033[0m %llu B, %llu KiB, %llu MiB\n\n", s, s >> 10, s >> 20);

  // Afficher l'en-tête du tableau de performances
  printf("\033[1m%5s %10s %10s %8s\033[0m\n", "Itération", "Temps, s", "Interactions/s", "GFLOP/s");

  // Boucle principale de la simulation
  for (u64 i = 0; i < steps; i++)
  {
    // Mesurer le temps de calcul
    const f64 start = omp_get_wtime();
    move_particles(p, dt, n);
    const f64 end = omp_get_wtime();

    // Calculer le nombre d'interactions par seconde
    const f32 h1 = (f32)(n) * (f32)(n);
    const f32 interactions_per_sec = h1 / (end - start);

    // Calculer le nombre de GFLOPs par seconde
    const f32 h2 = (17.0 * h1 + 6.0 * (f32)n + 6.0 * (f32)n) * 1e-9;
    const f32 gflops_per_sec = h2 / (end - start);

    // Ne pas tenir compte des itérations de chauffage (warm-up) dans les calculs de performance
    if (i >= warmup)
    {
      rate += gflops_per_sec;
      drate += gflops_per_sec * gflops_per_sec;
    }

    // Afficher les résultats de l'itération actuelle
    printf("%5llu %10.3e %10.3e %8.1f %s\n",
           i,
           (end - start),
           interactions_per_sec,
           gflops_per_sec,
           (i < warmup) ? "(Chauffage)" : "");
    fflush(stdout);
  }

  // Calculer la moyenne des performances en GFLOPs/s
  rate /= (f64)(steps - warmup);

  // Calculer l'écart-type des performances en GFLOPs/s
  drate = sqrt(drate / (f64)(steps - warmup) - (rate * rate));

  // Afficher les résultats finaux de performance
  printf("-----------------------------------------------------\n");
  printf("\033[1m%s %4s \033[42m%10.1lf +- %.1lf GFLOP/s\033[0m\n",
         "Performance moyenne:", "", rate, drate);
  printf("-----------------------------------------------------\n");

  // Libérer la mémoire allouée
  free(p);

  // Terminer le programme
  return 0;
}
