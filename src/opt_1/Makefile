CC=gcc
CL=clang

CFLAGS=-march=native -g3

OFLAGS=-O0 -fopenmp -fopt-info-all=nbody.gcc.optrpt
2FLAGS=-O2 -fopenmp -fopt-info-all=nbody.gcc.optrpt
3FLAGS=-O3 -fopenmp -fopt-info-all=nbody.gcc.optrpt
fastFLAGS=-Ofast -fopenmp -fopt-info-all=nbody.gcc.optrpt

EXECS=nbody3D_GCC_O0 nbody3D_GCC_O2 nbody3D_GCC_O3 nbody3D_GCC_Ofast nbody3D_CLANG_O0 nbody3D_CLANG_O2 nbody3D_CLANG_O3 nbody3D_CLANG_Ofast

all: $(EXECS)

max_performance : 
	sudo cpupower -c all frequency-set -g performance

allocate: 
	taskset -c 0 ./nbody3D_GCC_O0 &
	taskset -c 1 ./nbody3D_GCC_O2 &
	taskset -c 2 ./nbody3D_GCC_O3 &
	taskset -c 3 ./nbody3D_GCC_Ofast &
	taskset -c 4 ./nbody3D_CLANG_O0 &
	taskset -c 5 ./nbody3D_CLANG_O2 &
	taskset -c 6 ./nbody3D_CLANG_O3 &
	taskset -c 7 ./nbody3D_CLANG_Ofast &
	wait

execute: 
	perf record -g ./nbody3D_GCC_O0 > gcc_O0_execution_output.txt
	perf report > gcc_O0_execution_report.txt
	perf record -g ./nbody3D_GCC_O0 > gcc_O2_execution_output.txt
	perf report > gcc_O2_execution_report.txt
	perf record -g ./nbody3D_GCC_O0 > gcc_O3_execution_output.txt
	perf report > gcc_O3_execution_report.txt
	perf record -g ./nbody3D_GCC_O0 > gcc_Ofast_execution_output.txt
	perf report > gcc_Ofast_execution_report.txt

	perf record -g ./nbody3D_CLANG_O0 > clang_O0_execution_output.txt
	perf report > clang_O0_execution_report.txt
	perf record -g ./nbody3D_CLANG_O0 > clang_O2_execution_output.txt
	perf report > clang_O2_execution_report.txt
	perf record -g ./nbody3D_CLANG_O0 > clang_O3_execution_output.txt
	perf report > clang_O3_execution_report.txt
	perf record -g ./nbody3D_CLANG_O0 > clang_Ofast_execution_output.txt
	perf report > clang_Ofast_execution_report.txt

nbody3D_GCC_O0: nbody.c
	taskset -c 0 $(CC) $(CFLAGS) $(OFLAGS) $< -o $@ -lm

nbody3D_GCC_O2: nbody.c
	taskset -c 1 $(CC) $(CFLAGS) $(2FLAGS) $< -o $@ -lm

nbody3D_GCC_O3: nbody.c
	taskset -c 2 $(CC) $(CFLAGS) $(3FLAGS) $< -o $@ -lm

nbody3D_GCC_Ofast: nbody.c
	taskset -c 3 $(CC) $(CFLAGS) $(fastFLAGS) $< -o $@ -lm

nbody3D_CLANG_O0: nbody.c
	taskset -c 4 $(CL) $(CFLAGS) -O0 -fopenmp $< -o $@ -lm

nbody3D_CLANG_O2: nbody.c
	taskset -c 5 $(CL) $(CFLAGS) -O2 -fopenmp $< -o $@ -lm

nbody3D_CLANG_O3: nbody.c
	taskset -c 6 $(CL) $(CFLAGS) -O3 -fopenmp $< -o $@ -lm

nbody3D_CLANG_Ofast: nbody.c
	taskset -c 7 $(CL) $(CFLAGS) -Ofast -fopenmp $< -o $@ -lm

clean:
	rm -Rf *~ $(EXECS) *.optrpt