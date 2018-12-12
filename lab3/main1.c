#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <sys/time.h>
#include <stdlib.h>


void calctimediff (struct timeval tv1,struct timeval tv2)
{
    long secs = tv2.tv_sec - tv1.tv_sec;
    long msecs = tv2.tv_usec - tv1.tv_usec;
    if (msecs < 0) { msecs += 1000000; secs -= 1; }
    printf("%ld.%06ld;", secs, msecs);
}

void donaive (const int n)
{
    double a[n][n];
    double b[n][n];
    double c[n][n];


    for (int i =0; i<n; i++)
    {
        for(int j=0;j<n;j++) {
            a[i][j] = (rand() % 19 - 2.48) * 7.12431;
            b[i][j] = (rand() % 14 + 1.34) * 22.2342;
            c[i][j] = 0.0;
        }
    }

    struct timeval tv1, tv2;
    gettimeofday(&tv1, 0);
    for(int j=0; j<n;j++) {
        for(int k=0; k<n;k++) {
            for (int i = 0; i<n; i++)
            {
                c[i][j] = c[i][j] + a[i][k]*b[k][j];
            }
        }
    }
    gettimeofday(&tv2, 0);
    calctimediff(tv1, tv2);
}


void dobetter (const int n)
{
    double a[n][n];
    double b[n][n];
    double c[n][n];


    for (int i =0; i<n; i++)
    {
        for(int j=0;j<n;j++) {
            a[i][j] = (rand() % 19 - 2.48) * 7.12431;
            b[i][j] = (rand() % 14 + 1.34) * 22.2342;
            c[i][j] = 0.0;
        }
    }

    struct timeval tv1, tv2;
    gettimeofday(&tv1, 0);
    for(int i=0; i<n;i++) {
        for(int k=0; k<n;k++) {
            for (int j = 0; j<n; j++)
            {
                c[i][j] = c[i][j] + a[i][k]*b[k][j];
            }
        }
    }
    gettimeofday(&tv2, 0);
    calctimediff(tv1, tv2);
}

void doblas (const int n)
{
    double a[n*n];
    double b[n*n];
    double c[n*n];
    for (int i =0; i<n*n; i++)
    {
            a[i] = (rand() % 19 - 2.48) * 7.12431;
            b[i] = (rand() % 14 + 1.34) * 22.2342;
            c[i] = 0.0;
    }

    gsl_matrix_view A = gsl_matrix_view_array(a, n, n);
    gsl_matrix_view B = gsl_matrix_view_array(b, n, n);
    gsl_matrix_view C = gsl_matrix_view_array(c, n, n);

    struct timeval tv1, tv2;
    gettimeofday(&tv1, 0);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &A.matrix, &B.matrix, 0.0, &C.matrix);
    gettimeofday(&tv2, 0);
    calctimediff(tv1, tv2);

}

int main (void)
{
    for (int i =0;i<10;i++)
    {
        donaive(100);
        donaive(200);
        donaive(300);
        donaive(400);
        donaive(500);
        dobetter(100);
        dobetter(200);
        dobetter(300);
        dobetter(400);
        dobetter(500);
        doblas(100);
        doblas(200);
        doblas(300);
        doblas(400);
        doblas(500);
        printf("1");
        printf("\n");
    }
    return 0;
}
