// Ejercicio 3: Integral por método de Riemann
// Autor: Juan Angel Carrera Soto
// 11/08/2023
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
    clock_t start, end;
    double cpu_time_used;
    if (argc != 3)
    {
        printf("Uso: %s a b\n", argv[0]);
        return 1;
    }
    start = clock();
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = 10000000;
    printf("Con n = %d trapezoides, nuestra aproximación de la integral de %.2f a %.2f para x^2 es = %.13f\n", n, a, b, trapezoides(f_x2, a, b, n));
    printf("Con n = %d trapezoides, nuestra aproximación de la integral de %.2f a %.2f para 2x^3 es = %.13f\n", n, a, b, trapezoides(f_2x3, a, b, n));
    printf("Con n = %d trapezoides, nuestra aproximación de la integral de %.2f a %.2f para sin(x) es = %.13f\n", n, a, b, trapezoides(f_sin, a, b, n));

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nEl programa tardó %f segundos en ejecutarse.\n", cpu_time_used);

    return 0;
}

// gcc -o riemann riemann.c -lm
// ./riemann 0 10
// ./riemann <a> <b>