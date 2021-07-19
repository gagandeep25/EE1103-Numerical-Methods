/*****************
Purpose:Task 5
Authors:Gagan Deep,Santosh,Gautham
Date:12/09/2019
Inputs:None
Outputs:Integrated values of different methods
**************************/
#include<stdio.h>
#include<ncurses.h>
#include<math.h>
#include<stdlib.h>

double f(double p)//function for function to integrate
{
   double value1;
   double arr[502][2];
   double x[52];
   double a[52];
   int num=502;
   int i,j;
   int n=num/10 +1;
   double  h[n], A[n], l[n + 1],
        u[n + 1], z[n + 1], c[n + 1], b[n], d[n];  //Different coefficients and intermediate coefficents to generate final coefficients

   FILE *fptr1= fopen("out1_test0.csv","r");//opening the data file

        if(fptr1==NULL)
            printf("Error");
	
        for(int z=0;z<num;z++)
            arr[z][0] = z+1;
	
	for(int i=0;i<num;i++)
	{
            fscanf(fptr1,"%lf",&(arr[i][1]));//reads the data file
        }		
       
        int count1=0;
        
        for(int i=0;i<num;i++)              
        {    
              count1++;
        
              if(count1%10==1)    //takes one of ten points for the value of i
              {
                  a[i/10]=arr[i][1];    //stores y values of downsampled points
                  x[i/10]=arr[i][0];    //stores x values of downsampled points
                
              } 
                
         }   
            
          
        //step1
        for (i = 0; i <= n - 1; ++i) 
             h[i] = x[i + 1] - x[i];       

        //Step 2 
        for (i = 1; i <= n - 1; ++i)
             A[i] = 3 * (a[i + 1] - a[i]) / h[i] - 3 * (a[i] - a[i - 1]) / h[i - 1];
 
        //Step 3
        l[0] = 1;
        u[0] = 0;
        z[0] = 0;

        //Step 4
        for (i = 1; i <= n - 1; ++i)
        {
             l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
             u[i] = h[i] / l[i];
             z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
   
        }

        //Step 5
        l[n] = 1;
        z[n] = 0;
        c[n] = 0;

        //Step 6
        for (j = n - 1; j >= 0; --j) 
        {
             c[j] = z[j] - u[j] * c[j + 1];
             b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
             d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
        }
        int m=(p/10);
         
        value1 = d[m]*pow((p-(10*m + 1)),3) + c[m]*pow((p-(10*m + 1)),2) + b[m]*(p-(10*m + 1)) + a[m];  //equation to return interpolated value
   
        return value1; 
        fclose(fptr1);
}

//function is cubic spline interpolation of downsampled points (51 points) of given 502 points 

//romberg integration
void dump_row(size_t i, double *R)
{
         printf("R[%2zu] = ", i);
         for(size_t j = 0; j <= i; ++j)
        {
         printf("%f ", R[j]);
        }
         printf("\n");
}

double romberg(double /*lower limit*/ a, double /*upper limit*/ b, size_t max_steps, double /*desired accuracy*/ acc)
  {
   double R1[max_steps], R2[max_steps]; //buffers
   double *Rp = &R1[0], *Rc = &R2[0]; //Rp is previous row, Rc is current row
   double h = (b-a); //step size
   Rp[0] = (f(a) + f(b))*h*.5; //first trapezoidal step

   dump_row(0, Rp);

   for(size_t i = 1; i < max_steps; ++i)
     {
      h /= 2.;
      double c = 0;
      size_t ep = 1 << (i-1); //2^(n-1)
      for(size_t j = 1; j <= ep; ++j)
      {
         c += f(a+(2*j-1)*h);
      }
      Rc[0] = h*c + .5*Rp[0]; //R(i,0)

      for(size_t j = 1; j <= i; ++j)
      {
         double n_k = pow(4, j);
         Rc[j] = (n_k*Rc[j-1] - Rp[j-1])/(n_k-1); //compute R(i,j)
      }

      //Dump ith column of R, R[i,i] is the best estimate so far
      dump_row(i, Rc);

      if(i > 1 && fabs(Rp[i-1]-Rc[i]) < acc){
         return Rc[i-1];
      }

      //swap Rn and Rc as we only need the last row
      double *rt = Rp;
      Rp = Rc;
      Rc = rt;

   }
   printf("the value of romberg integral is %f\n\n",Rp[max_steps-1]);
   return Rp[max_steps-1];                                                //return our best guess

}                                                                         //will return interpolated value

double int_simpson(double from, double to, double h) //function for simpson integration
{
   double n = (to - from) / h;       //h is step size                              
   double sum1 = 0.0;
   double sum2 = 0.0;
   int i;
 
   double x;
 
   for(i = 0;i < n;i++)
 {
      sum1 += f(from + h * i + h / 2.0);
 }
   for(i = 1;i < n;i++)
 {
      sum2 += f(from + h * i);
 }
   double val;
   val=(h / 6.0) * (f(from) + f(to) + 4.0 * sum1 + 2.0 * sum2);
   printf("the value of simpson integral is %f\n\n",val);
   return val;
  
}

double int_trapezium(double from, double to, double h) //function for trapezoid integration
{
     double n = (to - from) / h;        //h is step size
     double sum = f(from) + f(to);
     int i;
     for(i = 1;i < n;i++)
         sum += 2.0*f(from + i * h);
         printf("the value of trapezoid integral is %lf\n\n",h * sum / 2.0);
     return  h * sum / 2.0;
}  
double int_midrect(double from, double to, double h) //function for box integration
{
     double sum = 0.0, x;              //h is step size 
     for(x=from; x <= (to-h); x += h)
     {
        sum += f(x+h/2.0);
     }
     printf("the value of box integral is %lf\n\n",(h*sum));
     return h*sum;
}
    
int main()
{
   double a; //value of rombert integral
   double b; //value of simpson integral
   double c; //value of trapezium integral
   double d; //value of box integral

   a=romberg(0,502,10,1e-8); 
   b=int_simpson(0,502,8);//take h between preferably 5-10
   c=int_trapezium(0,502,4);//take h between preferably 4-10
   d=int_midrect(0,502,2);//take h between preferably  2-10

   printf("the error in simpson integral:%lf\n",b-a);//prints the error in simpson integral
   printf("the error in trapezium integral:%lf\n",c-a);//prints the error in trapezium integral
   printf("the error in box integral :%lf\n",d-a);//prints the error in box integral

}




























