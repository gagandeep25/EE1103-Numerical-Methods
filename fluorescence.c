/*************************
Date       : 30/10/2019
Purpose    : Analyzing fluorescence data.
Authors    : Santosh, Gagan Deep, Manikandan
Group      : 2A
Inputs     : No inputs required. (Make sure that the datafile is present in the folder of this program)
Outputs    : Text files containing the data of filtered date, FWHM at peaks, Mean of FWHMs, locations and values of peaks.


To Compile : cc fluorescence.c
To Execute : ./a.out
**************************/

#include<stdio.h>
#include<stdlib.h>

#define W 20
#define N 1116000
float median(float arr[] , int size)        //A function to calculate the median of values in a given array arr[]
{
    int i=0 , j=0 ;
    float ref=0, med=0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size-1;j++)
        {
		    if(arr[j]>arr[j+1])
		    {
		        ref=arr[j];
		        arr[j]=arr[j+1];
		        arr[j+1]=temp;
		    }
		}
    }

    if(size%2 == 0)
    {
        med=(arr[(size-1)/2]+arr[size/2])/2;
    }
    else
    {
        med=arr[n/2];
    }
    return med;
}
int main()
{
	FILE *fp=fopen("CompleteData_fsc_ssc_10um.txt","r");
	FILE *fp1=fopen("peakdata.txt","w+");
	FILE *fp2=fopen("filtereddata.txt","w+");

	float dat[W][2]={0}, fwhm[N/10]={0}, peakval[N/10], b[N/10]={0}, diff[N/10];
	int time[W]={0}, peaklocation[N/10], cell[N/10], a[N/10]={0}, dist[N/10];
	int i,k,j,h,c,t1,t2,k=-1,count=0,cellloc=0,peakc=0,cellnum=0,peaknum=0;
	float ma1,ma2,ba1,ba2,x1,x2,max1,max2,ti,tf,meandist=0,meanfwhm=0,median,sumarrivaltimes=0;
	for(i=0;i<N/W;i++)
       	{
       	    if(k<(W-1))
            {
                k++;
            }
 	        else                                    //Using a variable k to create a circular buffer in which the values are added from the front.
            {
                k=0;
            }
            ma1=0;ma2=0;ba1=0;ba2=0;
            for(k=0; k<W; k++)
            {
                fscanf(fp,"%f %f",&x1,&x2);
                ma1+=x1;                            //Finding the base averages and moving averages.
                ma2+=x2;
                count++;
            }
            time[k]=count;
            dat[k][0]=ma1/W; dat[k][1]=ma2/W;
            j=k-1;
            t2=0;t1=0;max1=0;max2=0;
            for(int b=0; b<W; b++)
            {
                if(j<(W-1))
                {
                    j++;
                }
                else
                {
                    j=0;
                }
                ba1 += (dat[j][0]);                         //Calculating the peak values, and storing them if they cross the threshold.
                ba2 += (dat[j][1]);                         //Both the location and the peak values have been stored.
                if(max1<dat[j][0])
                {
                    max1=dat[j][0];
                    t1=time[j];
                }
                if(max2<dat[j][1] && b==W/2)
                {
                    max2=dat[j][1];
                    t2=time[j];
                }
            }

            if((max2-(ba2/W))>10 && (t2-peakc)>30 )
            {
                peakc=t2;
                peaknum++;
                fprintf(fp1,"%d %f\n",peakc,max2);                   //Writing the peak values and locations of side scattered data to a file
                if((abs(t2-t1)<5))
                {
                    cellloc=(t1+t2)/2;
                    cell[cellnum]=cellloc;
                    cellnum++;                                      //Checking if there is a peak in forward scatter data corresponding to a
                }                                                   //peak in the side scatter data. If yes, then it will be counted as a cell.
            }
            fprintf(fp2,"%d %f %f\n",time[k],dat[k][1],dat[k][0]);          //Writing filtered data to a file
         }
     fclose(fp1); fclose(fp2);
	 FILE *fp3=fopen("peakdata.txt","r");
	 FILE *fp4=fopen("filtereddata.txt","r");
	 for(int i=0;i<N;i++)
	 {
        if(i%10==0)
        {
            fscanf(fp4,"%d %f %*f",&(a[i/10]),&b[i/10]);
        }
     }
     for(k=0;k<peaknum;k++)
     {
         fscanf(fp3,"%d %f",&(peaklocation[k]),&peakval[k]);
	 }
 	 fclose(fp3); fclose(fp4);
     for(k=0;k<peaknum;k++)
     {
        for(i=0;i<N;i++)
        {
            if(i%10==0)
            {
                if(a[i/10]==peaklocation[k])
                {
                    for(h=-3;h<0;h++)                               //Finding FWHM using interpolation of the data (Linear Interpolation).
                    {
                        if(b[(i/10)+h]<=(peakval[k]/2)<=b[(i/10)+1+h])
                        {
                            ti=a[(i/10)+h] + ((a[(i/10)+1+h]-a[(i/10)+h])/(b[(i/10)+1+h]-b[(i/10)+h]))*((peakval[k]/2)-b[(i/10)+h]);
                        }
                    }
                    for(h=0;h<3;h++)
                    {
                        if(b[(i/10)+h]<=(peakval[k]/2)<=b[(i/10)+1+h])
                        {
                            tf=a[(i/10)+h] + ((a[(i/10)+1+h]-a[(i/10)+h])/(b[(i/10)+1+h]-b[(i/10)+h]))*((peakval[k]/2)-b[(i/10)+h]);
                        }
                    }
                }
            }

		     if(0<(tf-ti) && (tf-ti)<50)
		   	{                                                               //Leaving out values that have huge error.
		   	    fwhm[k]=tf-ti;
		   	}
		     else
             {
                 fwhm[k]=(fwhm[k-1]*(k-1)/k);
             }
        }
	}

	FILE *fp5=fopen("FWHM.txt","w+");
	FILE *fp6=fopen("MeanFWHM.txt","w+");
 	for(k=0;k<peaknum;k++)
	{
        fprintf(fp5,"%d %f\n",peaklocation[k],fwhm[k]);     //Writing FWHM data to a file.
	}
	meanfwhm=fwhm[0];
	for(k=1;k<peaknum;k++)
	{
 		 dist[k-1]=peaklocation[k]-peaklocation[k-1];
  		 meanfwhm = (meanfwhm*(k) + fwhm[k])/(k+1);
  		 meandist= (meandist*(k-1)+dist[k-1])/(k);
 		 fprintf(fp6,"The mean-width of peaks for %d peaks is %f\n",k,meanfwhm);  //Writing the mean FWHM data to a file.
	}
	for(k=1;k<cellnum;k++)
	{
  		diff[k-1]=cell[k]-cell[k-1];
  		sumarrivaltimes += diff[k-1];
	}
	   //printf("The Final Report is (For number of points = %d ,(It can be changed in program)):\n",N);
       printf("The number of peaks observed is %d\n",peaknum);
	   printf("The number of cells observed is %d\n",cellnum);
       printf("The mean of peak arrival times is %f\n",meandist);
	   printf("The mean of cell arrival times is %f\n",sumarrivaltimes/(cellnum-1));
	   median=median(diff,cellnum);
	   printf("The median of cell arrival times is %f\n",median);
       printf("The mean of width of peaks for %d peaks is %f\n",peaknum,meanfwhm);
       //printf("\nThe locations of peaks and full width half maximas are stored in FLdata1.txt\n");
       //printf("The mean fullwidth half maxima for different number of peaks is stored in FLdata2.txt\n");
	   fclose(fp5); fclose(fp6);
}


