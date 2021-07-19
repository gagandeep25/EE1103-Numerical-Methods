#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NMAX 9999

double f(double x, double y, double a, double b)
{
    return (a*x)-(b*x*y);
}
double g(double x, double y, double c, double d)
{
    return (d*x*y)-(c*y);
}

void main()
{
    double x[NMAX], y[NMAX], t[NMAX];
    double h=0.01;
    int a=1,b=2,c=3,d=4;
    FILE *fp;
    fp = fopen("lot.txt", "a+");
    t[0]=0, x[0]=0.1, y[0]=0.2;
    for(long int i=0;i<NMAX;i++)

       {

        x[i+1]=x[i]+(h*f(x[i],y[i],a,b));
        y[i+1]=y[i]+(h*g(x[i],y[i],c,d));
        t[i+1]=t[i]+h;
        fprintf(fp, "%lf\t%lf\t%lf\t\n",t[i], x[i],y[i]);
        }

    fclose(fp);

}

/** Plot the graph of x[i] vs t[i] and y[i] vs t[i] to get the time dependence of predator and prey.
    In order to get predator vs prey plot y[i] vs x[i]. **/
