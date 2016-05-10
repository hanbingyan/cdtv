#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "mex.h"
#include<pthread.h>


double B[512][512];
double out[512][512];

struct prob{
  double U[512][256];
  double lambda;
};

void *threadcd0(void *threadarg){
  struct prob *data;
  data=(struct prob*) threadarg;
  int i=0,j=0,l,k,t,s,m=512,n=256;
  double b,u[5],temp[5],temps;
  double lambda=data->lambda;
  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      data->U[i][j]=B[i][j];

  for(l=2;l<51;l++){
    for(k=1;k<20001;k++){
     /* srand((unsigned)time(Ndata->ULL));*/
      t=rand()%(m-2)+1;
      s=rand()%(n-2)+1;
      /* printf("thread 0 doing at data->U[%d][%d]\n",t,s); */
      b=B[t][s];
      u[0]=b;
      u[1]=data->U[t+1][s];
      u[2]=data->U[t-1][s];
      u[3]=data->U[t][s+1];
      u[4]=data->U[t][s-1];
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
      data->U[t][s]=u[j];
      if(k%50==0){
        /* minimize the first row*/
        b=B[0][s];
        u[0]=b;
        u[1]=data->U[0][s-1];
        u[2]=data->U[1][s];
        u[3]=data->U[0][s+1];
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
        data->U[0][s]=u[j];
        /*minimize the last row*/
        b=B[m-1][s];
        u[0]=b;
        u[1]=data->U[m-1][s-1];
        u[2]=data->U[m-2][s];
        u[3]=data->U[m-1][s+1];
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
        data->U[m-1][s]=u[j];
        /*minimize the first column */
        b=B[t][0];
        u[0]=b;
        u[1]=data->U[t-1][0];
        u[2]=data->U[t][1];
        u[3]=data->U[t+1][0];
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
        data->U[t][0]=u[j];
      }
    }
    /* minimize two corner */
    b=B[0][0];
    u[0]=b;
    u[1]=data->U[0][1];
    u[2]=data->U[1][0];
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
    data->U[0][0]=u[j];

    b=B[m-1][0];
    u[0]=b;
    u[1]=data->U[m-1][1];
    u[2]=data->U[m-2][0];
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
    data->U[m-1][0]=u[j];
  }
  pthread_exit(NULL);
}

void* threadcd1(void *threadarg){
  struct prob *data;
  data=(struct prob*) threadarg;
  double lambda=data->lambda;
  int i=0,j=0,l,k,t,s,m=512,n=256;
  double b,u[5],temp[5],temps;
  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      data->U[i][j]=B[i][j+256];


  for(l=2;l<51;l++){
    for(k=1;k<20001;k++){
     /* srand((unsigned)time(NULL));*/
      t=rand()%(m-2)+1;
      s=rand()%(n-2)+1;
      /* printf("pthread 1 doing at data->U[%d][%d]\n",t,s+256); */
      b=B[t][s+256];
      u[0]=b;
      u[1]=data->U[t+1][s];
      u[2]=data->U[t-1][s];
      u[3]=data->U[t][s+1];
      u[4]=data->U[t][s-1];
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
      data->U[t][s]=u[j];
      if(k%50==0){
       /*minimize the first row*/
        b=B[0][s+256];
        u[0]=b;
        u[1]=data->U[0][s-1];
        u[2]=data->U[1][s];
        u[3]=data->U[0][s+1];
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
        data->U[0][s]=u[j];
        /*minimize the last row */
        b=B[m-1][s+256];
        u[0]=b;
        u[1]=data->U[m-1][s-1];
        u[2]=data->U[m-2][s];
        u[3]=data->U[m-1][s+1];
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
        data->U[m-1][s]=u[j];

        /*minimize the last column*/
        b=B[t][n-1];
        u[0]=b;
        u[1]=data->U[t-1][n-1];
        u[2]=data->U[t][n-2];
        u[3]=data->U[t+1][n-1];
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
        data->U[t][n-1]=u[j];
      }
    }

    /* minimize two corner*/
    b=B[0][n-1];
    u[0]=b;
    u[1]=data->U[1][n-1];
    u[2]=data->U[0][n-2];
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
    data->U[0][n-1]=u[j];

    b=B[m-1][n-1];
    u[0]=b;
    u[1]=data->U[m-2][n-1];
    u[2]=data->U[m-1][n-2];
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
    data->U[m-1][n-1]=u[j];

  }
  pthread_exit(NULL);
}


void pcdtv2(double lambda){
  int i=0,j=0,l,k,t,s,rc;
  double b,u[5],temp[5],temps;
  void *status;
  struct prob prob0;
  struct prob prob1;
  prob0.lambda=lambda;
  prob1.lambda=lambda;
  pthread_t threads[2];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
  printf("creating thread 0\n");
  rc=pthread_create(&threads[0],&attr,threadcd0,(void *)&prob0);
  if(rc){
    printf("ERROR: return code from pthread_create() is %d\n",rc);
    exit(-1);
  }
  printf("creating thread 1\n");
  rc=pthread_create(&threads[1],&attr,threadcd1,(void *)&prob1);
  if(rc){
    printf("ERROR: return code from pthread_create() is %d\n",rc);
    exit(-1);
  }

  pthread_attr_destroy(&attr);

  rc=pthread_join(threads[0],&status);
  if(rc){
    printf("ERROR; return code from pthread_join() is %d\n", rc);
    exit(-1);
  }
  printf("Main: completed join with thread %d having a status of %ld\n",0,(long)status);

  rc=pthread_join(threads[1],&status);
  if(rc){
    printf("ERROR; return code from pthread_join() is %d\n", rc);
    exit(-1);
  }
  printf("Main: completed join with thread %d having a status of %ld\n",1,(long)status);

  for(i=0;i<512;i++)
    for(j=0;j<256;j++)
      out[i][j]=prob0.U[i][j];
  for(i=0;i<512;i++)
    for(j=256;j<512;j++)
      out[i][j]=prob1.U[i][j-256];
  
  for(l=1;l<31;l++){
    for(k=1;k<201;k++){
     /* srand((unsigned)time(NULL));*/
      t=rand()%(512-2)+1;
      s=rand()%2+255;
      b=B[t][s];
      u[0]=b;
      u[1]=out[t+1][s];
      u[2]=out[t-1][s];
      u[3]=out[t][s+1];
      u[4]=out[t][s-1];
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
      out[t][s]=u[j];
    }
    /* minimize four corner */
    if(k%50==0){
      b=B[0][s];
      u[0]=b;
      u[1]=out[1][s];
      u[2]=out[0][s-1];
      u[3]=out[0][s+1];
      temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2])+fabs(b-u[3])+fabs(b-u[4]));
      temp[1]=(u[1]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[1]-u[3])+fabs(u[1]-u[4]));
      temp[2]=(u[2]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[2]-u[3])+fabs(u[2]-u[4]));
      temp[3]=(u[3]!=b)+lambda*(fabs(u[3]-u[1])+fabs(u[3]-u[2])+fabs(u[3]-u[4]));
      temps=temp[0];
      j=0;
      for(i=1;i<4;i++){
        if(temp[i]<temps){
          temps=temp[i];
          j=i;
        }
      }
      out[0][s]=u[j];

      b=B[511][s];
      u[0]=b;
      u[1]=out[510][s];
      u[2]=out[511][s-1];
      u[3]=out[511][s+1];
      temp[0]=lambda*(fabs(b-u[1])+fabs(b-u[2])+fabs(b-u[3])+fabs(b-u[4]));
      temp[1]=(u[1]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[1]-u[3])+fabs(u[1]-u[4]));
      temp[2]=(u[2]!=b)+lambda*(fabs(u[1]-u[2])+fabs(u[2]-u[3])+fabs(u[2]-u[4]));
      temp[3]=(u[3]!=b)+lambda*(fabs(u[3]-u[1])+fabs(u[3]-u[2])+fabs(u[3]-u[4]));
      temps=temp[0];
      j=0;
      for(i=1;i<4;i++){
        if(temp[i]<temps){
          temps=temp[i];
          j=i;
        }
      }
      out[511][s]=u[j];
    }
  }
}



void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    double lambda;              /* input scalar */
    double *inMatrix;               /* 1xN input matrix */
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
    if( !mxIsDouble(prhs[0]) ||mxIsComplex(prhs[0]) ||  mxGetNumberOfElements(prhs[0])!=1 ) {
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
    pcdtv2(lambda);
    index=0;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            outMatrix[index++]=out[i][j];
}
