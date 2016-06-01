#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <math.h>




double * read_file(const char * filepath, int *neurons) 
{
	FILE * fp = fopen(filepath, "r");
	assert(fp > 0);
	
	int num = fscanf(fp, "%d", neurons);
	assert(num == 1);
	
	int size = pow(*neurons, 2);
	double *data = malloc((sizeof *data) * size);
	assert (data != NULL);

	for (int i=0; i<size; ++i) {
		num = fscanf(fp, "%lf", &data[i]);
		if (num != 1)
			goto cleanup;
	}


	fclose(fp);
	return data;

cleanup:
	fprintf(stderr, "Error reading file\n");
	fclose(fp);
	free(data);
	return NULL;
}

void print_matrix(int n, double *arr)
{
	if (!arr) return;

	for (int i = 0; i < n*n; ++i) {
		if (i % n == 0) printf("\n");	
		printf("%.2f ", arr[i]);
	}

	printf("\n");
}

void print_vector(int n, double *arr)
{
	if (!arr) return;

	for (int i = 0; i < n; ++i) {
		printf("%.2f ", arr[i]);
	}

	printf("\n");
}


double sigmoid(double z)
{
	return (1/(1-exp(-z)));
}

double dot(int size, double *a, double *b)
{
	double sum = 0.0;
	for (int i = 0; i < size; ++i) {
		sum += a[i] * b[i];
	}
	return sum;
}

void feed(int size, double *weights, 
		double * outputs, double (*activate)(double))
{
	for (int i = 0; i < size; ++i)
		outputs[i] = dot(size, weights + (i*size), outputs);
}

int main(int argc, char *argv[])
{
	
	char *filepath = NULL;

	int c = getopt(argc, argv, "i:");
	if  (c == 'i')
		filepath = optarg;
	else {
		fprintf(stderr, "Unknown option -%c\n", optopt);
		exit(EXIT_FAILURE);
	}

	printf("filename = %s\n", filepath);

	int size;	
	double *weights = read_file(filepath, &size);
	printf("Neurons : %d\n", size);

	double outputs[size];
	for (int i = 0; i < size; ++i) {
		outputs[i] = (double)rand() / (double)RAND_MAX;
	}

	feed(size, weights, outputs, sigmoid);

	print_matrix(size, weights);
	printf("===================\n");
	print_vector(size, outputs);
	
	free(weights);
	return 0;
}



