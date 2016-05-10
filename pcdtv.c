#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "mex.h"

double B[512][512];
double U[512][512];

void pcdtv(double B[][512], double U[][512],const int m, const int n, const double lambda){
  int i=0,j=0,l,k,t,s;
  double b,u[5],temp[5],temps;
  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      U[i][j]=B[i][j];

  for(l=2;l<101;l++){
    for(k=1;k<20001;k++){
     /* srand((unsigned)time(NULL));*/
      t=rand()%(m-2)+1;
      s=rand()%(n-2)+1;
      b=B[t][s];
      u[0]=b;
      u[1]=U[t+1][s];
      u[2]=U[t-1][s];
      u[3]=U[t][s+1];
      u[4]=U[t][s-1];
      temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2])+fabs(b-u[3])+fabs(b-u[4]));
      temp[1]=(u[1]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[1]-u[3])+fabs(u[1]-u[4]));
      temp[2]=(u[2]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[2]-u[3])+fabs(u[2]-u[4]));
      temp[3]=(u[3]!=b)+lambda*(fabs(u[3]-u[1])+fabs(u[3]-u[2])+fabs(u[3]-u[4]));
      temp[4]=(u[4]!=b)+lambda*(fabs(u[4]-u[1])+fabs(u[4]-u[2])+fabs(u[4]-u[3]));
      temps=temp[0];
      j=0;
      for(i=1;i<5;i++){
        if(temp[i]<temps){
          temps=temp[i];
          j=i;
        }
      }
      U[t][s]=u[j];
      if(k%50==0){
        /* minimize the first row*/
        b=B[0][s];
        u[0]=b;
        u[1]=U[0][s-1];
        u[2]=U[1][s];
        u[3]=U[0][s+1];
        temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2])+fabs(b-u[3]));
        temp[1]=(u[1]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[1]-u[3]));
        temp[2]=(u[2]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[2]-u[3]));
        temp[3]=(u[3]!=b)+lambda*(fabs(u[3]-u[1])+fabs(u[3]-u[2]));
        temps=temp[0];
        j=0;
        for(i=1;i<4;i++){
          if(temp[i]<temps){
            temps=temp[i];
            j=i;
          }
        }
        U[0][s]=u[j];
        /*minimize the last row*/
        b=B[m-1][s];
        u[0]=b;
        u[1]=U[m-1][s-1];
        u[2]=U[m-2][s];
        u[3]=U[m-1][s+1];
        temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2])+fabs(b-u[3]));
        temp[1]=(u[1]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[1]-u[3]));
        temp[2]=(u[2]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[2]-u[3]));
        temp[3]=(u[3]!=b)+lambda*(fabs(u[3]-u[1])+fabs(u[3]-u[2]));
        temps=temp[0];
        j=0;
        for(i=1;i<4;i++){
          if(temp[i]<temps){
            temps=temp[i];
            j=i;
          }
        }
        U[m-1][s]=u[j];
        /*minimize the first column */
        b=B[t][0];
        u[0]=b;
        u[1]=U[t-1][0];
        u[2]=U[t][1];
        u[3]=U[t+1][0];
        temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2])+fabs(b-u[3]));
        temp[1]=(u[1]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[1]-u[3]));
        temp[2]=(u[2]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[2]-u[3]));
        temp[3]=(u[3]!=b)+lambda*(fabs(u[3]-u[1])+fabs(u[3]-u[2]));
        temps=temp[0];
        j=0;
        for(i=1;i<4;i++){
          if(temp[i]<temps){
            temps=temp[i];
            j=i;
          }
        }
        U[t][0]=u[j];
        /* minimize the last column */
        b=B[t][n-1];
        u[0]=b;
        u[1]=U[t-1][n-1];
        u[2]=U[t][n-2];
        u[3]=U[t+1][n-1];
        temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2])+fabs(b-u[3]));
        temp[1]=(u[1]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[1]-u[3]));
        temp[2]=(u[2]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[2]-u[3]));
        temp[3]=(u[3]!=b)+lambda*(fabs(u[3]-u[1])+fabs(u[3]-u[2]));
        temps=temp[0];
        j=0;
        for(i=1;i<4;i++){
          if(temp[i]<temps){
            temps=temp[i];
            j=i;
          }
        }
        U[t][n-1]=u[j];
      }
    }

    /* minimize four corner */
    b=B[0][0];
    u[0]=b;
    u[1]=U[0][1];
    u[2]=U[1][0];
    temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2]));
    temp[1]=(u[1]!=b)+lambda*fabs(u[1]-u[2]);
    temp[2]=(u[2]!=b)+lambda*fabs(u[1]-u[2]);
    temps=temp[0];
    j=0;
    for(i=1;i<3;i++){
      if(temp[i]<temps){
        temps=temp[i];
        j=i;
      }
    }
    U[0][0]=u[j];

    b=B[m-1][0];
    u[0]=b;
    u[1]=U[m-1][1];
    u[2]=U[m-2][0];
    temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2]));
    temp[1]=(u[1]!=b)+lambda*fabs(u[1]-u[2]);
    temp[2]=(u[2]!=b)+lambda*fabs(u[1]-u[2]);
    temps=temp[0];
    j=0;
    for(i=1;i<3;i++){
      if(temp[i]<temps){
        temps=temp[i];
        j=i;
      }
    }
    U[m-1][0]=u[j];

    b=B[0][n-1];
    u[0]=b;
    u[1]=U[1][n-1];
    u[2]=U[0][n-2];
    temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2]));
    temp[1]=(u[1]!=b)+lambda*fabs(u[1]-u[2]);
    temp[2]=(u[2]!=b)+lambda*fabs(u[1]-u[2]);
    temps=temp[0];
    j=0;
    for(i=1;i<3;i++){
      if(temp[i]<temps){
        temps=temp[i];
        j=i;
      }
    }
    U[0][n-1]=u[j];

    b=B[m-1][n-1];
    u[0]=b;
    u[1]=U[m-2][n-1];
    u[2]=U[m-1][n-2];
    temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2]));
    temp[1]=(u[1]!=b)+lambda*fabs(u[1]-u[2]);
    temp[2]=(u[2]!=b)+lambda*fabs(u[1]-u[2]);
    temps=temp[0];
    j=0;
    for(i=1;i<3;i++){
      if(temp[i]<temps){
        temps=temp[i];
        j=i;
      }
    }
    U[m-1][n-1]=u[j];

  }
}









void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    double lambda;              /* input scalar */
    double *inMatrix;               /* input matrix */
    size_t m,n;                   /* size of matrix */
    int i,j,index;
    double *outMatrix;              /* output matrix */
    /* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","Two output required.");
    }
    /* make sure the first input argument is scalar */
    if( !mxIsDouble(prhs[0]) || 
         mxIsComplex(prhs[0]) ||
         mxGetNumberOfElements(prhs[0])!=1 ) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notScalar","Input multiplier must be a scalar.");
    }

    /* make sure the second input argument is type double */
    if( !mxIsDouble(prhs[1]) ||
         mxIsComplex(prhs[1])) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type double.");
    }


    /* get the value of the scalar input  */
   lambda = mxGetScalar(prhs[0]);

    /* create a pointer to the real data in the input matrix  */
    inMatrix = mxGetPr(prhs[1]);

    /* get dimensions of the input matrix */
    m = mxGetM(prhs[1]);
    n = mxGetN(prhs[1]);
    index=0;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            B[i][j]=inMatrix[index++];
    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix((mwSize)m,(mwSize)n,mxREAL);
    /* get a pointer to the real data in the output matrix */
    outMatrix=mxGetPr(plhs[0]);

    /* call the computational routine */
    pcdtv(B,U,(mwSize)m,(mwSize)n,lambda);
    index=0;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            outMatrix[index++]=U[i][j];
}
