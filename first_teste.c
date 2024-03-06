#include <stdio.h>
#include "mpi.h" /* head necessário para rodar em paralelo */

#define M 4
int main(int argc, char **argv)
{
	int i, j, rank, size, ierr; /*rank: core que está realizando o processo; size: qt de cores; ierr: serve para finalizar a regiao paralela */
	int sendto, recvfrom; /* variáveis de envio e recebimento */
	int ourtag=1; /* tag de identificação da mensagem que será enviada */
	double sendmessage[M][M]; /* mensagem que será enviada */
	double getmessage[M][M];  /* variável que receberá a mensagem */

	MPI_Status rstatus; /* status para definir a liberação do buffer*/

	ierr = MPI_Init(&argc, &argv); /* iniciando a região paralela */
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &size); /* MPI_Comm_size diz a quantidade de cores que vão ser usados */
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* MPI_Comm_rank dá nome aos cores e MPI_COMM_WORLD é um comunicador que inclui todos os processos definidos pelo usuário */

	if(rank==0) /* deliberando o processo para o Master */
	{ sendto = 1; /* delimitando para qual core o master vai enviar a mensagem */

           for(i=0; i<M; i++)
	  {  for(j=0; j<M; j++)
	     {
               sendmessage[i][j]= 1;
               ierr = MPI_Send(sendmessage, M, MPI_DOUBLE, sendto, ourtag, MPI_COMM_WORLD);
	     }
           }
            printf("%d send message:   %d\t \n", rank, sendmessage);
	}

	else if(rank==1)
	{ recvfrom = 0; /* delimitando de qual core o rank 1 vai receber a mensagem */
	  ierr = MPI_Recv(getmessage, M, MPI_DOUBLE, recvfrom, ourtag, MPI_COMM_WORLD, &rstatus);
	  printf("%d: Got message <%d\t>\n", rank, getmessage);
	}

	ierr = MPI_Finalize();
	return 0;
}
