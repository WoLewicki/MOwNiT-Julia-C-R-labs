#include <stdio.h>
#include <gsl/gsl_ieee_utils.h>
#include <unistd.h>

int main() {
    float x = 2;
    for(int i=0; i<132; i++)
    {
        gsl_ieee_printf_float(&x);
        printf("\n");
        x = x/2;
    }
    return 0;
}