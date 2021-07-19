/*
 Date    : 21 Sept 2019
 Authors : Santosh, Gagan Deep, Manikandan
 Group   : 2A
 Inputs  : No Inputs Required
 Outputs : The Linear equation depicting dependence of Surface Area on Height, Weight.
 */

#include<stdio.h>
#include<conio.h>
void main()     // Assuming the Surface Area is a linear function of Height and Weight
                // Hence solving three linear equations
{
    double A[20][20]= {0},L[20][20]= {0}, U[20][20], res[20][20]; // Defines arrays necessary for matrices
    double B[20]= {0}, X[20]= {0},Y[20]= {0}, H[9], W[9], SA[9]; // Defines arrays necessary for matrices
    int i,j,k,n=3;
    H[0]=182; H[1]=180; H[2]=179; H[3]=187; H[4]=189; H[5]=194; H[6]=195; H[7]=193; H[8]=200; //Giving data input to the program.
    W[0]=74; W[1]=88; W[2]=94; W[3]=78; W[4]=84; W[5]=98; W[6]=76; W[7]=86; W[8]=96;
    SA[0]=1.92; SA[1]=2.11; SA[2]=2.15; SA[3]=2.02; SA[4]=2.09; SA[5]=2.31; SA[6]=2.02; SA[7]=2.16; SA[8]=2.31;
    double sum_height=0, sum_weight=0, sum_area=0, sum_sqheight=0, sum_sqweight=0, sum_heightweight=0, sum_heightarea=0, sum_weightarea=0;
    double predictedvalue; // Defining Function to Estimate the value
    for(i=0;i<9;i++)
    {
        sum_height += H[i]; // Defining variables
        sum_weight += W[i];
        sum_area += SA[i];
        sum_sqheight += (H[i]*H[i]);
        sum_sqweight += (W[i]*W[i]);
        sum_heightweight += (H[i]*W[i]);
        sum_heightarea += (H[i]*SA[i]);
        sum_weightarea += (W[i]*SA[i]);
    }

    A[0][0]=9; A[0][1]=sum_height; A[0][2]=sum_weight;    //Using LU Decomposition to find the value of coefficients of linear regression equation.
    A[1][0]=sum_height; A[1][1]=sum_sqheight; A[1][2]=sum_heightweight;
    A[2][0]=sum_weight;A[2][1]=sum_heightweight; A[2][2]=sum_sqweight;

    B[0]=sum_area; B[1]=sum_heightarea; B[2]=sum_weightarea;  //Defining the Values
    for(j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
        {
            if(i<=j)  //Giving Values to Matrices L, U
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

    for(i=0; i<n; i++) // Finding Matrices Y, X
    {
        Y[i]=B[i];
        for(j=0; j<i; j++)
        {
            Y[i]-=L[i][j]*Y[j];
        }
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
    printf("The equation developed using the data is Surface Area = %lf + (%lf)(Height) + (%lf)(Weight)\n", X[0], X[1], X[2]); // Giving the Surface area dependence on Height, Weight as Linear Equation
    predictedvalue = X[0] + X[1]*190 + X[2]*80;
    printf("The estimated value of Surface Area is %lf\n", predictedvalue); //Giving The Predicted Value
}
