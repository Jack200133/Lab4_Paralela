#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>

double f_x2(double x)
{
    return x * x;
}

double f_2x3(double x)
{
    return 2 * pow(x, 3);
}

double f_sin(double x)
{
    return sin(x);
}

double trapezoides(double (*func)(double), double a, double b, int n)
{
    double h = (b - a) / n;
    double suma = func(a) / 2.0;
    for (int i = 1; i < n; i++)
    {
        suma += func(a + i * h);
    }
    suma += func(b) / 2.0;
    return suma * h;
}

int main(int argc, char *argv[])
{
    double start, end;
    int my_rank, comm_sz;
    double local_a, local_b;
    double local_integral;
    double total_integral;

    MPI_Init(&argc, &argv);
    start = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (argc != 3)
    {
        printf("Uso: %s a b\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = 10000000;
    int local_n = n / comm_sz;

    local_a = a + my_rank * local_n * (b - a) / n;
    local_b = local_a + local_n * (b - a) / n;

    local_integral = trapezoides(f_x2, local_a, local_b, local_n);

    MPI_Reduce(&local_integral, &total_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        printf("Con n = %d trapezoides, nuestra aproximación de la integral de %.2f a %.2f para x^2 es = %.13f\n", n, a, b, total_integral);
    }

    local_integral = trapezoides(f_2x3, local_a, local_b, local_n);
    MPI_Reduce(&local_integral, &total_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        printf("Con n = %d trapezoides, nuestra aproximación de la integral de %.2f a %.2f para 2x^3 es = %.13f\n", n, a, b, total_integral);
    }

    local_integral = trapezoides(f_sin, local_a, local_b, local_n);
    MPI_Reduce(&local_integral, &total_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        printf("Con n = %d trapezoides, nuestra aproximación de la integral de %.2f a %.2f para sin(x) es = %.13f\n", n, a, b, total_integral);
    }
    end = MPI_Wtime();
    if (my_rank == 0)
    {
        printf("El programa MPI tardó %f segundos en ejecutarse.\n", end - start);
    }

    MPI_Finalize();
    return 0;
}

// mpicc -o riemann_mpi riemann_mpi.c -lm
// mpirun -np 4 ./riemann_mpi 0 115
// mpirun -np 4 ./riemann_mpi < a > < b >