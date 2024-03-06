#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int my_rank;
	int size;
	MPI_Init(&argc, &argv); /* inicializando o ambiente paralelo */

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* MPI_Comm_rank dá nome aos cores e GRUPO:  MPI_COMM_WORLD é um comunicador que inclui todos os processos definidos pelo usuário */
	MPI_Comm_size(MPI_COMM_WORLD, &size); /* MPI_Comm_size diz a quantidade de cores que vão ser usados */

	printf("Hello word! I'm rank (processor number) %d of size %d\n", my_rank, size);

	if(my_rank == 0)
	  printf("that is all for now!\n");

	MPI_Finalize(); /* finalizando o ambiente paralelo */

}
