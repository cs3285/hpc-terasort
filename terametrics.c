#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "terarec.h"

static long seeds[32] = {0L, 
				4160749568L, 
				4026531840L, 
				3892314112L,
				3758096384L,
				3623878656L,
				3489660928L,
				3355443200L,
				3221225472L,
				3087007744L,
				2952790016L,
				2818572288L,
				2684354560L,
				2550136832L,
				2415919104L,
				2281701376L,
				2147483648L,
				2013265920L,
				1879048192L,
				1744830464L,
				1610612736L,
				1476395008L,
				1342177280L,
				1207959552L,
				1073741824L,
				939524096L,
				805306368L,
				671088640L,
				536870912L,
				402653184L,
				268435456L,
				134217728L};

extern void terasort(terarec_t *local_data, int  local_len, 
				terarec_t *splits, int  splits_len,
				terarec_t **_sort_data, int  *_sort_len, long  *_sort_offset);

extern int teravalidate(terarec_t *local_data, int local_len);


#define USAGE \
"usage:\n"                                                                     \
"  terametrics [options]\n"                                                       \
"options:\n"                                                                   \
"  -c [count]          Recs per node (Default: 1000)\n"                         \
"  -s [filename]       Splits filename (Default: splits.dat)\n"                \
"  -h                  Show this help message\n"

int main (int argc, char *argv[]){
	MPI_Init (&argc, &argv);
	int P, rank;
	MPI_Comm_size (MPI_COMM_WORLD, &P);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	int local_len = 1000;
	int nsamples = 50;
	int c;

	while ((c = getopt (argc, argv, "hc:s:")) != -1){
		switch (c){
			case 'c':
				local_len = atoi(optarg);
				break;
			case 's':
				nsamples = atoi(optarg);
				break;
			case 'h':
				fprintf(stderr, USAGE);
				exit(EXIT_SUCCESS);
			default:
				fprintf(stderr, USAGE);
				exit(EXIT_FAILURE);
		}
	}

	teraMPICommitType();

	srand(seeds[rank % 32]);

	double t1 = MPI_Wtime();
	terarec_t *local_data = teraGenerate(rank * local_len, local_len);
	terarec_t *splits = terapartition(local_data, local_len, nsamples, P-1);

	double t2 = MPI_Wtime() - t1;

	MPI_Reduce(&t2, &t1, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if(rank == 0)
		printf("elapsed time : %f\n", t1);

	terarec_t *sort_data;
	int sort_len;
	long sort_offset;

	double start = MPI_Wtime();
	terasort(local_data, local_len, splits, P-1,
			&sort_data, &sort_len, &sort_offset);
	double elapsed = MPI_Wtime() - start;

	double max_time;
	MPI_Reduce(&elapsed, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if(rank == 0)
		printf("elapsed time : %f\n", max_time);

	int error_acc = teravalidate(sort_data, sort_len);

	if (rank == 0 && error_acc)
		fprintf(stderr, "Data not sorted.\n");	

	free(local_data);
	free(splits);
	free(sort_data);

	MPI_Finalize();

	return EXIT_SUCCESS;
}
