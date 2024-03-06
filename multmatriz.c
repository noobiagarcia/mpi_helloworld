#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define M 8

int main(int argc, char **argv)
{   int rank, size, ierr, i, j, k;
    int tag=1;
    double **matrizA, **matrizB, **matrizC, soma;
    double **msgsend, **msgrcv;
     MPI_Status rstatus;

     matrizA = (double**)malloc(M * sizeof(double*));
     matrizB = (double**)malloc(M * sizeof(double*));
     matrizC = (double**)malloc(M * sizeof(double*));

    msgsend =(double**)malloc(M * sizeof(double*));
    msgrcv = (double**)malloc(M * sizeof(double*));
    for(i=0;i<M;i++)
    {
	matrizA[i] = (double*)malloc(M * sizeof(double*));
	matrizB[i] = (double*)malloc(M * sizeof(double*));
	matrizC[i] = (double*)malloc(M * sizeof(double*));
        msgsend[i] =(double*)malloc(M * sizeof(double*));
        msgrcv[i] = (double*)malloc(M * sizeof(double*));

    }

   ierr = MPI_Init(&argc, &argv);
   ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);
   ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   if(rank == 0)
   {
     for(i=0; i<M; i++)
     {	for(j=0; j<M; j++)
        {
             matrizB[i][j] = 2;
             /*matrizA[i][j] = 1;*/
	     msgsend[i][j] = matrizB[i][j];
	}

	ierr = MPI_Send(&msgsend, 8, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
     }
      /*for(i=1; i<size; i++)
	ierr = MPI_Send(&msgsend, 8, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);*/
   }
   else if(rank == 1)
   {
      /*ierr= MPI_Recv(&msgrcv, 8, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &rstatus);*/

     /*for(i=0; i<M; i++)
     {  for(j=0; j<M; i++)*/
	    ierr= MPI_Recv(&msgrcv, 8, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &rstatus);
	    printf("%d\t  %d ", msgrcv, rank);

   }

   ierr = MPI_Finalize();
   return 0;
}
