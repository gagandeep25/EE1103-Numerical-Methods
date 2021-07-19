/*******
Date    : 22/09/2019
Authors : Gagan Deep, Santosh, Manikandan. (Group 2A)
Purpose : Cubic Spline interpolation using LU Decomposition method.
Inputs  : Number of data points and corresponding x,y values.
Outputs : The equations obtained after interpolation
********/

#include<stdio.h>
#include<math.h>

void lu_decomp(int m, int n, double a[m][n], double X[n-1])//Function of LU decomposition of set of linear equations;a[m][n] contains both the coefficients and constant terms.
 {
      double A[n][n],L[n][n], U[n][n];//A[n][n] is an array consisting of coefficients of variables;L[n][n] coressponds to lower diagonal matrix,U[n][n] is an array coressponding to upper diagonal matrix
      double B[n],Y[n];              //B[n] is an array of constant terms
      int i,j,k;
      for(i=0;i<m;i++)             //Taking out constant terms from a[m][n]
      {
           B[i]=a[i][n-1];
      }
      for(i=0;i<m;i++)             //Taking out coefficients from a[m][n]
      {
          for(j=0;j<n-1;j++)
          {
              A[i][j]=a[i][j];
          }
      }
      for(j=0; j<m; j++)           //Generation of both lower and upper diagonal matrices
      {
          for(i=0; i<m; i++)
          {
             if(i<=j)
             {
                  U[i][j]=A[i][j];
                  for(k=0; k<i-1; k++)
                       U[i][j]-=L[i][k]*U[k][j];
                  if(i==j)
                       L[i][j]=1;
                  else
                       L[i][j]=0;
             }
           else
             {
                  L[i][j]=A[i][j];
                  for(k=0; k<=j-1; k++)
                       L[i][j]-=L[i][k]*U[k][j];
                       L[i][j]/=U[j][j];
                       U[i][j]=0;
             }
          }
      }
      for(i=0; i<m; i++)              //Generation of intermediate variable Y
      {
           Y[i]=B[i];
           for(j=0; j<i; j++)
           {
                Y[i]-=L[i][j]*Y[j];
           }
      }
      for(i=m-1; i>=0; i--)            //Gives the values of variables involved
      {
           X[i]= Y[i];
           for(j=i+1; j<m; j++)
           {
                X[i]-=U[i][j]*X[j];
           }
           X[i]/=U[i][i];
      }


 }
/********************
Cubic Spline coefficients calculator
Function that calculates the values of ai, bi, ci, and di's for the cubic splines:
ai(x-xi)^3+bi(x-xi)^2+ci(x-xi)+di
********************/
void cSCoeffCalc(int n, double h[n], double sig[n+1], double y[n+1], double a[n], double b[n], double c[n], double d[n]){
    int i;
    for(i=0;i<n;i++){
        d[i]=y[i];
        b[i]=sig[i]/2.0;
        a[i]=(sig[i+1]-sig[i])/(h[i]*6.0);
        c[i]=(y[i+1]-y[i])/h[i]-h[i]*(2*sig[i]+sig[i+1])/6.0;
    }
}
/********************
Function to generate the tridiagonal augmented matrix
for cubic spline for equidistant data-points
Parameters:
n: no. of data-points
h: array storing the succesive interval widths
a: matrix that will hold the generated augmented matrix
y: array containing the y-axis data-points
********************/
void tridiag(int n, double h[n], double a[n-1][n], double y[n+1]){
    int i;
    for(i=0;i<n-1;i++){
        a[i][i]=2*(h[i]+h[i+1]);
    }
    for(i=0;i<n-2;i++){
        a[i][i+1]=h[i+1];
        a[i+1][i]=h[i+1];
    }
    for(i=1;i<n;i++){
        a[i-1][n-1]=(y[i+1]-y[i])*6/(double)h[i]-(y[i]-y[i-1])*6/(double)h[i-1];
    }
}
/*******
Function that prints the elements of a matrix row-wise
Parameters: rows(m),columns(n),matrix[m][n]
*******/
void printMatrix(int m, int n, double matrix[m][n]){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%.2lf\t",matrix[i][j]);
        }
        printf("\n");
    }
}
/*******
Function that copies the elements of a matrix to another matrix
Parameters: rows(m),columns(n),matrix1[m][n] , matrix2[m][n]
*******/
void copyMatrix(int m, int n, double matrix1[m][n], double matrix2[m][n]){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            matrix2[i][j]=matrix1[i][j];
        }
    }
}
int main(){
    int m,i;
    printf("Enter the no. of data-points:\n");
    scanf("%d",&m);
    int n=m-1;  //Now (n+1) is the total no. of data-points, following our convention
    double x[n+1]; //array to store the x-axis points
    double y[n+1]; //array to store the y-axis points
    double h[n];   ////array to store the successive interval widths
    printf("Enter the x-axis values:\n");
    for(i=0;i<n+1;i++){
        scanf("%lf",&x[i]);
    }
    printf("Enter the y-axis values:\n");
    for(i=0;i<n+1;i++){
        scanf("%lf",&y[i]);
    }
    for(i=0;i<n;i++){
        h[i]=x[i+1]-x[i];
    }
    double a[n]; //array to store the ai's
    double b[n]; //array to store the bi's
    double c[n]; //array to store the ci's
    double d[n]; //array to store the di's
    double sig[n+1]; //array to store Si's
    double sigTemp[n-1]; //array to store the Si's except S0 and Sn
    sig[0]=0;
    sig[n]=0;
    double tri[n-1][n]; //matrix to store the tridiagonal system of equations that will solve for Si's
    tridiag(n,h,tri,y); //to initialize tri[n-1][n]
    printf("The tridiagonal system for the Natural spline is:\n\n");
    printMatrix(n-1,n,tri);
    //Perform LU Decomposition
    lu_decomp(n-1, n, tri, sigTemp);
    for(i=1;i<n;i++){
        sig[i]=sigTemp[i-1];
    }
    //Print the values of Si's
    for(i=0;i<n+1;i++){
        printf("\nSig[%d] = %.2lf\n",i,sig[i]);
    }
    //calculate the values of ai's, bi's, ci's, and di's
    cSCoeffCalc(n,h,sig,y,a,b,c,d);
    printf("The equations of cubic interpolation polynomials between the successive intervals are:\n\n");
    for(i=0;i<n;i++){
        printf("P%d(x) b/w [%.2lf,%.2lf] = %.2lf*(x-%.2lf)^3+%.2lf*(x-%.2lf)^2+%.2lf*(x-%.2lf)+%.2lf\n",i,x[i],x[i+1],a[i],x[i],b[i],x[i],c[i],x[i],d[i]);
    }



}
