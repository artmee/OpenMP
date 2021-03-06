#include "column.h"
#include <omp.h>

int col_print(char *output, double *column, int size)
{
    FILE *fp;
    if ((fp = fopen(output, "w")) == NULL)
    {
        printf("Не удалось открыть файл \n");
        getchar();
        return -1;
    }

    for (int i = 0; i < size; ++i)
    {
        fprintf(fp, "%lf\n", column[i]);
    }

    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}

int col_set_zero(double *column, int size)
{

#pragma omp parallel for default(none) shared(column) private(size)
    for (int i = 0; i < size; ++i)
    {
        column[i] = 0;
    }

    return 0;
}

double col_dot_product(const double *left, const double *right, int size)
{
    double sum = 0;

#pragma omp parallel for default(none) shared(left, right, size) reduction(+ : sum)
    for (int i = 0; i < size; ++i)
    {
        sum += left[i] * right[i];
    }

    return sum;
}

int col_mult_by_numb(const double *column, double rate, double *result, int size)
{

#pragma omp parallel for default(none) shared(column, result, rate, size)
    for (int i = 0; i < size; ++i)
    {
        result[i] = column[i] * rate;
    }

    return 0;
}

double col_module(const double *column, int size)
{
    double sum = 0;

#pragma omp parallel for default(none) shared(column, size) reduction(+ : sum)
    for (int i = 0; i < size; ++i)
    {
        sum += column[i] * column[i];
    }

    return sqrt(sum);
}

double col_subtraction(const double *left, const double *right, double *result, int size)
{

#pragma omp parallel for default(none) shared(left, right, result, size)
    for (int i = 0; i < size; ++i)
    {
        result[i] = left[i] - right[i];
    }

    return 0;
}