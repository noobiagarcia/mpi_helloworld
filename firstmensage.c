#include <stdio.h>
#include "mpi.h" /* head necessário para rodar em paralelo */

int main(int argc, char **argv)
{
	int rank, size, ierr; /*rank: core que está realizando o processo; size: qt de cores; ierr: serve para finalizar a regiao paralela */
	int sendto, recvfrom; /* variáveis de envio e recebimento */
	int ourtag=1; /* tag de identificação da mensagem que será enviada */
	char sendmessage[]="hello"; /* mensagem que será enviada */
	char getmessage[6];  /* variável que receberá a mensagem */

	MPI_Status rstatus; /* status para definir a liberação do buffer*/

	ierr = MPI_Init(&argc, &argv); /* iniciando a região paralela */
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &size); /* MPI_Comm_size diz a quantidade de cores que vão ser usados */
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* MPI_Comm_rank dá nome aos cores e MPI_COMM_WORLD é um comunicador que inclui todos os processos definidos pelo usuário */

	if(rank==0) /* deliberando o processo para o Master */
	{ sendto = 1; /* delimitando para qual core o master vai enviar a mensagem */
	  ierr = MPI_Ssend(sendmessage, 6, MPI_CHAR, sendto, ourtag, MPI_COMM_WORLD);
	  printf("%d: send message <%s>\n", rank, sendmessage);
	}
	else if(rank==1)
	{ recvfrom = 0; /* delimitando de qual core o rank 1 vai receber a mensagem */
	  ierr = MPI_Recv(getmessage, 6, MPI_CHAR, recvfrom, ourtag, MPI_COMM_WORLD, &rstatus);
	  printf("%d: Got message <%s>\n", rank, getmessage);
	}

	ierr = MPI_Finalize();
	return 0;
}
