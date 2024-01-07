#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

typedef float  f32;
typedef double f64;
typedef unsigned long long u64;

// Structure représentant une particule avec position et vitesse
typedef struct particle_s {
  f32 position[3]; // x, y, z
  f32 velocity[3]; // vx, vy, vz
} particle_t;

// Fonction d'initialisation des positions et vitesses des particules
void init(particle_t *p, u64 n) {
  for (u64 i = 0; i < n; i++) {
    u64 r1 = (u64)rand();
    u64 r2 = (u64)rand();
    f32 sign = (r1 > r2) ? 1 : -1;

    // Initialisation aléatoire des positions et vitesses
    p[i].position[0] = sign * (f32)rand() / (f32)RAND_MAX;
    p[i].position[1] = (f32)rand() / (f32)RAND_MAX;
    p[i].position[2] = sign * (f32)rand() / (f32)RAND_MAX;

    p[i].velocity[0] = (f32)rand() / (f32)RAND_MAX;
    p[i].velocity[1] = sign * (f32)rand() / (f32)RAND_MAX;
    p[i].velocity[2] = (f32)rand() / (f32)RAND_MAX;
  }
}

// Fonction pour déplacer les particules en fonction des interactions gravitationnelles
void move_particles(particle_t *p, const f32 dt, u64 n) {
  const f32 softening = 1e-20;

  // Allouer les tableaux dynamiquement une seule fois
  f32 **dx = malloc(n * sizeof(f32 *));
  f32 **dy = malloc(n * sizeof(f32 *));
  f32 **dz = malloc(n * sizeof(f32 *));
  f32 **d_2 = malloc(n * sizeof(f32 *));
  f32 **d_3_over_2 = malloc(n * sizeof(f32 *));

  for (u64 i = 0; i < n; i++) {
    dx[i] = malloc(n * sizeof(f32));
    dy[i] = malloc(n * sizeof(f32));
    dz[i] = malloc(n * sizeof(f32));
    d_2[i] = malloc(n * sizeof(f32));
    d_3_over_2[i] = malloc(n * sizeof(f32));
  }

  // Pré-calcule les valeurs
  for (u64 i = 0; i < n; i++) {
    for (u64 j = 0; j < n; j++) {
      dx[i][j] = p[j].position[0] - p[i].position[0];
      dy[i][j] = p[j].position[1] - p[i].position[1];
      dz[i][j] = p[j].position[2] - p[i].position[2];
      d_2[i][j] = (dx[i][j] * dx[i][j]) + (dy[i][j] * dy[i][j]) + (dz[i][j] * dz[i][j]) + softening;
      d_3_over_2[i][j] = 1.0 / sqrt(sqrt(d_2[i][j] * sqrt(d_2[i][j])));
    }
  }

  // Boucle déroulée avec blocking manuel
  const u64 blockSize = 4; // ajustez la taille du bloc selon votre architecture
  for (u64 i = 0; i < n; i += blockSize) {
    f32 *fx = malloc(blockSize * sizeof(f32));
    f32 *fy = malloc(blockSize * sizeof(f32));
    f32 *fz = malloc(blockSize * sizeof(f32));

    // Initialiser les tableaux à zéro
    #pragma omp simd
    for (u64 k = 0; k < blockSize; k++) {
      fx[k] = fy[k] = fz[k] = 0.0;
    }

    for (u64 j = 0; j < n; j++) {
      for (u64 k = 0; k < blockSize; k++) {
        if (i + k < n) {
          // Calcul des forces
          fx[k] += dx[j][i + k] * d_3_over_2[j][i + k];
          fy[k] += dy[j][i + k] * d_3_over_2[j][i + k];
          fz[k] += dz[j][i + k] * d_3_over_2[j][i + k];
        }
      }
    }

    // Mise à jour des vitesses et positions
    for (u64 k = 0; k < blockSize; k++) {
      if (i + k < n) {
        p[i + k].velocity[0] += dt * fx[k];
        p[i + k].velocity[1] += dt * fy[k];
        p[i + k].velocity[2] += dt * fz[k];

        p[i + k].position[0] += dt * p[i + k].velocity[0];
        p[i + k].position[1] += dt * p[i + k].velocity[1];
        p[i + k].position[2] += dt * p[i + k].velocity[2];
      }
    }

    // Libérer la mémoire des tableaux temporaires
    free(fx);
    free(fy);
    free(fz);
  }

  // Libérer la mémoire à la fin
  for (u64 i = 0; i < n; i++) {
    free(dx[i]);
    free(dy[i]);
    free(dz[i]);
    free(d_2[i]);
    free(d_3_over_2[i]);
  }

  free(dx);
  free(dy);
  free(dz);
  free(d_2);
  free(d_3_over_2);
}

// Fonction principale
int main(int argc, char **argv) {
  const u64 n = (argc > 1) ? atoll(argv[1]) : 16384;
  const u64 steps = 13;
  const f32 dt = 0.01;
  f64 rate = 0.0, drate = 0.0;
  const u64 warmup = 3;
  particle_t *p = malloc(sizeof(particle_t) * n);
  init(p, n);
  const u64 s = sizeof(particle_t) * n;

  printf("\n\033[1mTotal memory size:\033[0m %llu B, %llu KiB, %llu MiB\n\n", s, s >> 10, s >> 20);

  printf("\033[1m%5s %10s %10s %8s\033[0m\n", "Step", "Time, s", "Interact/s", "GFLOP/s");
  fflush(stdout);

  for (u64 i = 0; i < steps; i++) {
    const f64 start = omp_get_wtime();

    move_particles(p, dt, n);

    const f64 end = omp_get_wtime();

    const f32 h1 = (f32)(n) * (f32)(n);
    const f32 h2 = (17.0 * h1 + 6.0 * (f32)n + 6.0 * (f32)n) * 1e-9;

    if (i >= warmup) {
      rate += h2 / (f32)(end - start);
      drate += (h2 * h2) / (f32)((end - start) * (end - start));
    }

    printf("%5llu %10.3e %10.3e %8.1f %s\n",
           i,
           (end - start),
           h1 / (end - start),
           h2 / (end - start),
           (i < warmup) ? "(warm up)" : "");

    fflush(stdout);
  }

  rate /= (f64)(steps - warmup);
  drate = sqrt(drate / (f64)(steps - warmup) - (rate * rate));

  printf("-----------------------------------------------------\n");
  printf("\033[1m%s %4s \033[42m%10.1lf +- %.1lf GFLOP/s\033[0m\n",
         "Performance moyenne:", "", rate, drate);
  printf("-----------------------------------------------------\n");

  free(p);
  return 0;
}
