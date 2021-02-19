#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define SIZE 3
#define RANGE 1000

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
//void multiply(int mat1[][N], int mat2[][N], int res[][N])
void multiply(double* mat1, double* mat2, double* res, int N)
{
        int i, j, k;
        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        //res[i][j] = 0;
                        *(res + i*N + j)=0;
                        for (k = 0; k < N; k++)
                                //res[i][j] += mat1[i][k] * mat2[k][j];
                                *(res + i*N + j) += *(mat1 + i*N + k) * *(mat2 + k*N + j);
                }
        }
}

int main()
{
        int sizes[3]={100,1000,5000};
	long micro_secs[3]={0,0,0};
	int i=0;
	int j=0;
	int z=0;
        for (z=0; z<SIZE; z++){
                int N=sizes[z];
                struct timeval start, end;
                double *mat2 = (double *)malloc(N * N * sizeof(double));
                double *mat1 = (double *)malloc(N * N * sizeof(double));

                if (mat1 == NULL || mat2 == NULL)
                {
                        fprintf(stderr, "Out of memory");
                        exit(0);
                 }

                for(i = 0; i < N; i++) {
                        for(j = 0; j < N; j++) {
                                *(mat1 + i*N + j) =(double)rand()/(double)(RAND_MAX)*(double)RANGE;
                        }
                }

                for(i = 0; i < N; i++) {
                        for(j = 0; j < N; j++) {
                                *(mat2 + i*N + j) =(double)rand()/(double)(RAND_MAX)*(double)RANGE;
                        }
                }

                //int res[N][N]; // To store result
                double *res = (double *)malloc(N * N * sizeof(double));

		gettimeofday(&start, NULL);
                multiply(mat1, mat2, res,N);
                gettimeofday(&end, NULL);
                long seconds = (end.tv_sec - start.tv_sec);
                long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

                /*printf("Result matrix is \n");
                for (i = 0; i < N; i++) {
                        for (j = 0; j < N; j++)
                                //printf("%d ", res[i][j]);
                                printf("%lf ", (res + i*N)[j]);
                        printf("\n");
                }*/
                free(mat1);
                free(mat2);
                free(res);
                printf("Time elpased is %ld seconds and %ld micros\n", seconds, micros);
		micro_secs[z]=micros;
        }

	FILE * fp;

   	/* open the file for writing*/
   	fp = fopen ("times_micros.txt","w");

   	/* write 10 lines of text into the file stream*/
   	for(i = 0; i < SIZE; i++){
      		fprintf (fp, "Batch %d: %d\n",i,micro_secs[i]);
   	}
 
   	/* close the file*/  
   	fclose (fp);
   	return 0;
}
