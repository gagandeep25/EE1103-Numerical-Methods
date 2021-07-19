#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 0.1
#define visc 0.00089
#define Kb 1.38*pow(10, -23)


double bprime(double T, double b, double D)
{
    return 2*Kb*T - (K*b)/(3*(M_PI)*visc*D);
}

int main(int argc, double *argv[])
{
    if(argc != 4)
    {
        printf("Enter the command as ./a.out_<particle size>_<temperature>_<number of steps>")
    }
}
