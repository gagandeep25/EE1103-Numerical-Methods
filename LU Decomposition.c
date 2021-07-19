/*
Date    : 18/09/2019
Authors : Santosh, Gagan Deep, Manikandan
Group   : 10
Purpose : Task 4a
Inputs  : No input required, the equations to be solved are already fed to the program.
Outputs : The matrices [L], [U], [A] by multiplying [L] & [U], intermediate matrix [Y] and the solution matrix [X].
*/

#include<stdio.h>
#include<conio.h>
void main()
{
    float A[20][20]= {0},L[20][20]= {0}, U[20][20], res[20][20]; // Defines arrays necessary for matrices
    float B[20]= {0}, X[20]= {0},Y[20]= {0}; // Defines arrays necessary for matrices
    int i,j,k,n=3;
    A[0][0]=3; A[0][1]=-0.1; A[0][2]=-0.2;    //Giving Input for the Matrix (The Coefficients)
    A[1][0]=0.1; A[1][1]=7; A[1][2]=-0.3;
    A[2][0]=0.3;A[2][1]=-0.2; A[2][2]=10;

    B[0]=7.85; B[1]=-19.3; B[2]=71.4;  // Giving Input for the Matrix (The Final Value)
    for(j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
        {
            if(i<=j)
            {
                U[i][j]=A[i][j]; // Giving Values for Parts of [U],[L]
                for(k=0; k<i-1; k++)
                    U[i][j]-=L[i][k]*U[k][j];
                if(i==j)
                    L[i][j]=1;
                else
                    L[i][j]=0;
            }
            else
            {
                L[i][j]=A[i][j];  // Giving Values for Parts of [U],[L]
                for(k=0; k<=j-1; k++)
                    L[i][j]-=L[i][k]*U[k][j];
                L[i][j]/=U[j][j];
                U[i][j]=0;
            }
        }
    }
    printf("[L]: \n");  // Printing the Matrix [L]
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",L[i][j]);
        printf("\n");
    }
    printf("\n\n[U]: \n"); // Printing the Matrix [U]
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",U[i][j]);
        printf("\n");
    }
    printf("\n\n[A] by Multiplication of [L] and [U]: \n");
    for (i = 0; i < n; i++) // Finding [A] back for verification
    {
        for (j = 0; j < n; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < n; k++)
                res[i][j] += L[i][k]*U[k][j];
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%9.3f ", res[i][j]);
        }
        printf("\n");
    }
    for(i=0; i<n; i++)
    {
        Y[i]=B[i];
        for(j=0; j<i; j++)
        {
            Y[i]-=L[i][j]*Y[j];
        }
    }
    printf("\n\n[Y]: \n");       // Printing Matrix [Y]
    for(i=0; i<n; i++)
    {
        printf("%9.3f",Y[i]);
    }
    for(i=n-1; i>=0; i--)
    {
        X[i]= Y[i];
        for(j=i+1; j<n; j++)
        {
            X[i]-=U[i][j]*X[j];
        }
        X[i]/=U[i][i];
    }
    printf("\n\n[X]: \n");     // Printing Matrix [X]
    for(i=0; i<n; i++)
    {
        printf("%9.3f",X[i]);
    }
}
