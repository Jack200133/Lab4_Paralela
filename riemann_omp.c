// Ejercicio 4: Integral por método de Riemann con OpenMP
// Autor: Juan Angel Carrera Soto
// 11/08/2023
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
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
double trapezoides(double (*func)(double), double a, double b, int n, int threads)
{
    double h = (b - a) / n;
    double suma_global = 0.0;
#pragma omp parallel num_threads(threads)
    {
        int ID_thread = omp_get_thread_num();
        double n_local = n / threads;
        double a_local = a + (ID_thread * n_local * h);
        double b_local = a_local + (n_local * h);
        double suma_local = func(a_local) / 2.0;
        for (int i = 1; i < n_local; i++)
        {
            suma_local += func(a_local + i * h);
        }
        suma_local += func(b_local) / 2.0;
#pragma omp critical
        suma_global += suma_local;
    }
    return suma_global * h;
}
int main(int argc, char *argv[])
{
    double start, end;

    if (argc != 4)
    {
        printf("Uso: %s a b <cantidad de threads>\n", argv[0]);
        return 1;
    }
    start = omp_get_wtime();

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = 10000000;
    int threads = atoi(argv[3]);
    printf("Con n = %d trapezoides y %d threads, nuestra aproximación de la integral de %.2f a %.2f para x^2 es = %.13f\n", n, threads, a, b, trapezoides(f_x2, a, b, n, threads));
    printf("Con n = %d trapezoides y %d threads, nuestra aproximación de la integral de %.2f a %.2f para 2x ^ es = % .13f\n ", n, threads, a, b, trapezoides(f_2x3, a, b, n, threads));
    printf("Con n = %d trapezoides y %d threads, nuestra aproximación de la integral de %.2f a % .2f para sin(x) es = % .13f\n ", n, threads, a, b, trapezoides(f_sin, a, b, n, threads));

    end = omp_get_wtime();
    printf("El programa con OpenMP tardó %f segundos en ejecutarse.\n", end - start);

    return 0;
}

// gcc -o riemann_omp riemann_omp.c -lm -fopenmp
// ./riemann_omp 0 115 4
// ./riemann <a> <b> <threads>