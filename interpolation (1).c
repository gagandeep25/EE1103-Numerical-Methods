/*****************
Purpose:Task 4
Authors:Gagan Deep,Santosh,Gautham
Date:06/09/2019
Inputs:None
Outputs:RMS Errors of different interpolations; Interpolated values for tan() function
**************************/

#include <stdio.h>
#include<math.h>

double lag1(float x,double a[],double b[], int r) //Function for calculating the Interpolated value using Lagrange polynomial for tan values
{
	  double lagr=0;

	  for(int i=0;i<=r;i++)
	  {
		 double s=1, t=1;

		 for(int j=0;j<=r;j++)
			if(j!=i)
			{
				s=s*(x-a[j]);              //Numerator of each term
				t=t*(a[i]-a[j]);           //Denominator of each term
			}
		 lagr+=((s/t)*b[i]);                       //Gives the value of Lagrange polynomial
	  }

	  return lagr;                                     //will return the interpolated value
}
double lag2(int x,double a[],double b[], int r) //Function for calculating the Interpolated value using Lagrange polynomial for given file
{
	  double lagr=0;

	  for(int i=0;i<=r;i++)                 
	  {
		 double s=1, t=1;

		 for(int j=0;j<=r;j++)
			if(j!=i)
			{
				s=s*(x-a[j]);               //Numerator of each term
				t=t*(a[i]-a[j]);            //Denominator of each term
	
		        }
		 lagr+=((s/t)*b[i]);                        //Gives the value of Lagrange polynomial
	  } 

	  return lagr;                                      //will return the interpolated value
}
double splinecoeff(double x[],double a[],int n,int p)//function for generating coefficients of cubic spline for given file
{

int i,j;
double  h[n], A[n], l[n + 1],
        u[n + 1], z[n + 1], c[n + 1], b[n], d[n];            //Different coefficients and intermediate coefficents to generate final coefficients
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

        int m =p/10;
        double value1;

        value1 = d[m]*pow((p-(10*m + 1)),3) + c[m]*pow((p-(10*m + 1)),2) + b[m]*(p-(10*m + 1)) + a[m];  //equation to return interpolated value
   
        return value1;                                                                                  //will return interpolated value

          
}
double spline(double x[],double a[],int n,double p)         //function for generating coefficients of cubic spline for tan values
{

int i,j;
double  h[n], A[n], l[n + 1],                               //Different coefficients and intermediate coefficents to generate final coefficient
        u[n + 1], z[n + 1], c[n + 1], b[n], d[n];
        //Step 1
        for (i = 0; i <= n - 1; ++i) h[i] = x[i + 1] - x[i];

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
             d[j] = (c[j + 1] - c[j]) / (3 * h[j]);}
       double value2;   
       int m=floor(p*10)-10;

       value2 =d[m]*pow((p-(x[m])),3) + c[m]*pow((p-(x[m])),2) + b[m]*(p-(x[m])) +a[m]; //equation to return interpolated value
   
       return value2;                                                                   //will return interpolated value 

          
}
int main()
{
    
    int n, i, j;
    int num=502; //num is total number of entries in given file
     n=num/10 +1;
     
    int k;
    double x[n + 1], a[n + 1],x1[11],y1[11];
    double arr[502][2];
    int e[502];


FILE *fptr1= fopen("out1_test0.csv","r");//opening the data file

        if(fptr1==NULL)
            printf("Error");
	
        for(int z=0;z<num;z++)
            arr[z][0] = z+1;
	
	for(int i=0;i<num;i++)
	{
            fscanf(fptr1,"%lf",&(arr[i][1]));//reads the data file
        }		
        printf("Part 1:\n"); 
        int count1=0;
        FILE *fptr2= fopen("downs.txt","w+");//opening the another file to write the downsampled data
        for(int i=0;i<num;i++)              
        {    
              count1++;
        
              if(count1%10==1)    //takes one of ten points for the value of i
              {
                  a[i/10]=arr[i][1];    //stores y values of downsampled points
                  x[i/10]=arr[i][0];    //stores x values of downsampled points
                  fprintf(fptr2,"%lf %lf\n",x[i/10],a[i/10]);//writes the data of downsampled points to the file to be plotted in gnuplot,Refer at the end
              }    
        }      
              double cspintval[502];        //stores the values obtained through interpolation
	      double rmserror,sum;          //variables of rms error
         
        for(int r=0;r<502;r++)
        {
	      cspintval[r]=splinecoeff(x,a,n,r+1);
              sum+=pow((cspintval[r]-arr[r][1]),2);
        }
              rmserror=sqrt(sum/(num-n));         //error is not calculated for points taken to interpolate,so denominator is num-n

        printf("%lf is the root mean square error by using cubic spline interpolated data\n", rmserror);//prints rms error for cubic spline

 //Lagrange polynomial is giving more error for interpoltion of 50 points so to get less error 11 points are interpolated here

      int r=num/50 +1; 
      double vl[502];       //stores values of data obtained from lagrange interpolation
      int count2=0;
      for(int i=0;i<num;i++)
      {    
           fscanf(fptr1,"%lf",&(arr[i][1]));       //reads the data file
           count2++;
       
           if(count2%50==1)                       //takes 1 of every 50 points
           {
               y1[i/50]=arr[i][1];            //gives coressponding y values
               x1[i/50]=arr[i][0];            //gives coressponding x values
             
           }    
      }    
     double powerp1[502];                        //different variables to calculate rms error
     double suml=0;
     double p1;
     double erl;
     for(int o=0;o<num;o++)
     {
          vl[o] = lag2(o+1,x1,y1,r);    //gives the values through lagrange interpolation
     }
           
     for(int t=0;t<num;t++)
     {
	  p1=arr[t][1] - vl[t];
	  powerp1[t] = pow(p1,2);
	  suml+=powerp1[t];
     } 
     erl=sqrt(suml/(num-r));                       //error is not calculated for points taken to interpolate,so denominator is num-r
     printf("%lf is the root mean square error by using lagrange interpolated data\n\n",erl);//prints rms error for lagrange interpolation
     fclose(fptr1);                                //closes file1
     fclose(fptr2);                                //closes file2
     printf("Part 2:\n"); 
     double xtan[4],ytan[4];                       //arrays to store x ,coressponding tanx values

     for(int s=0;s<4;s++)
     {
         xtan[s]=1+s*0.1;
         ytan[s]=tan(xtan[s]);
     }

     double tanA,tanB;                          //variables that coresspond to cubic spline
     tanA=spline(xtan,ytan,4,1.15);             //tan values are to be obtained for 1.15 and 1.35
     tanB=spline(xtan,ytan,4,1.35);
     printf("The value of tan(1.15) using cubic spline interpolation is %f\n",tanA);
     printf("The value of tan(1.35) using cubic spline interpolation is %f\n",tanB);
     double tanC,tanD;
     tanC=lag1(1.15,xtan,ytan,4);                //variables that coresspond to lagrange interpolation
     tanD=lag1(1.35,xtan,ytan,4);                //tan values are to be obtained for 1.15 and 1.35
     printf("The value of tan(1.15) using cubic spline interpolation is %f\n",tanC);
     printf("The value of tan(1.35) using cubic spline interpolation is %f\n",tanD);  
  
     return 0;
}
//Set of gnuplot commands:
//set terminal pdf
//set output 'data.pdf'
//set xrange [0:505]
//set yrange [0:0.04]
//set xlabel 'X----->'
//set ylabel 'Y----->'
//set title 'Plot Of Downsampled Data'
//plot 'downs.txt' w lp
//q
//This creates the output data.pdf
