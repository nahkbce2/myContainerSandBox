#include "mpi.h"
#include <stdio.h>
#include <math.h>

/* module load gcc */
/* module load mpich/ge/gcc/64/3.1 */
/* Compile me with 'mpicc -o cpi-parallel cpi-parallel.c' */
#include "MemoryChecker.h"

double f( double );
double f( double a )
{
    return (4.0 / (1.0 + a*a));
}

int main( int argc, char *argv[])
{
    int done = 0, n, rank, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Get_processor_name(processor_name,&namelen);

    Utilities::CheckMemory::MemoryChecker mc(rank);

    fprintf(stderr,"my Process %d on %s\n",
	    rank, processor_name);

    n = 0;
    while (!done)
    {
        if (rank == 0)
        {
/*
            printf("Enter the number of intervals: (0 quits) ");
            scanf("%d",&n);
*/
			if (n==0) n=1024*numprocs; else n=0;

			startwtime = MPI_Wtime();
        }
		
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
            h   = 1.0 / (double) n;
            sum = 0.0;
            for (i = rank + 1; i <= n; i += numprocs)
            {
                x = h * ((double)i - 0.5);
                sum += f(x);
            }
            mypi = h * sum;

            MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (rank == 0)
			{
                printf("pi is approximately %.16f, Error is %.16f\n",
                       pi, fabs(pi - PI25DT));
				endwtime = MPI_Wtime();
				printf("wall clock time = %f\n",
				endwtime-startwtime);
			}
        }
    }
    MPI_Finalize();

    return 0;
}