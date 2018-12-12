#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <sys/time.h>
#include <stdlib.h>

#define N1 100000
#define M1 1000
#define N2 200000
#define M2 2000
#define N3 300000
#define M3 3000
#define N4 400000
#define M4 4000
#define N5 500000
#define M5 5000

void calctimediff (struct timeval tv1,struct timeval tv2)
{
    long secs = tv2.tv_sec - tv1.tv_sec;
    long msecs = tv2.tv_usec - tv1.tv_usec;
    if (msecs < 0) { msecs += 1000000; secs -= 1; }
    printf("%ld.%06ld,", secs, msecs);
}

void dovxv (const int n)
{
    double *a = malloc(sizeof(double) * n);
    double *b = malloc(sizeof(double) * n);

    for (int i =0; i<n; i++)
    {
        a[i] = (rand()%19 - 2.48) * 7.12431;
        b[i] = (rand()%14 + 1.34) * 22.2342;
    }
    double result =0.0;
    gsl_vector_view A = gsl_vector_view_array(a, n);
    gsl_vector_view B = gsl_vector_view_array(b, n);

    struct timeval tv1, tv2;
    gettimeofday(&tv1, 0);
    gsl_blas_ddot(&A.vector, &B.vector, &result);
    gettimeofday(&tv2, 0);
    calctimediff(tv1, tv2);

    free(a);
    free(b);
}


void domxv (const int m)
{
    double *c = malloc(sizeof(double) * m*m);
    double *d = malloc(sizeof(double) * m);
    double *e = malloc(sizeof(double) * m);

    for (int i=0;i<m*m;i++)
    {
        c[i] = (rand()%23 + 1.439) * 1.233425;
    }
    for (int i=0;i<m;i++)
    {
        d[i] = 0.0;
    }
    for (int i=0;i<m;i++)
    {
        e[i] = (rand()%23 + 12.34439) * 1.235;
    }

    gsl_vector_view E = gsl_vector_view_array(e, m);
    gsl_matrix_view C = gsl_matrix_view_array(c, m, m);
    gsl_vector_view D = gsl_vector_view_array(d, m);

    struct timeval tv1, tv2;
    gettimeofday(&tv1, 0);
    gsl_blas_dgemv(CblasNoTrans, 1.0, &C.matrix, &E.vector, 0.0, &D.vector);
    gettimeofday(&tv2, 0);
    calctimediff(tv1, tv2);
    free(c);
    free(d);
    free(e);
}

int main (void)
{

    for (int i = 1; i < 6; i++) {
       for(int j=1;j<11;j++) {
            printf("%d,", j);
            dovxv(i * 10000000);
            printf("%d,", i * 10000000);
            printf("1");
            printf("\n");
        }
    }
  /*  for (int i = 1; i < 6; i++) {
        for(int j=1;j<11;j++) {
            printf("%d,", j);
            domxv(i * 2000);
            printf("%d,", i * 2000);
            printf("2");
            printf("\n");
        }
    } */
    return 0;
}
