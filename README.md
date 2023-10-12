# Instrucciones de compilacion y ejecucion

## Compilacion

### SEQ
``` bash
gcc -o riemann riemann.c -lm
./riemann <a> <b>
```
* Ejemplo:
``` bash
./riemann 0 10
```

### OMP
``` bash
gcc -o riemann_omp riemann_omp.c -lm -fopenmp
./riemann_omp <a> <b> <threads>
```

Ejemplo:
``` bash
./riemann_omp 0 10 4
```

### MPI
``` bash
mpicc -o riemann_mpi riemann_mpi.c -lm
mpirun -np <procesos> ./riemann_mpi <a> <b>
```

Ejemplo:
``` bash
mpirun -np 4 ./riemann_mpi 0 10
```
