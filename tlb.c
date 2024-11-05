#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Default values for page size and number of pages
    int PAGESIZE = 4;  // Size of one page in bytes
    int NUMPAGES = 4;  // Default number of pages
    long int iterations = 1000000; // Adjust this for how long you want to run the test

    // Parse command line arguments if provided
    if (argc == 4) {        
        PAGESIZE = atoi(argv[1]);
        NUMPAGES = atoi(argv[2]);
        iterations = atoi(argv[3]);
    }

    // Allocate an array large enough to hold the number of pages
    int totalSize = NUMPAGES * PAGESIZE / sizeof(int); // Total number of integers in the array
    int *a = malloc(totalSize * sizeof(int));  // Dynamic allocation of the array

    // Initialize the array
    for (int i = 0; i < totalSize; i++) {
        a[i] = 0;  // Initialize the array to 0
    }

    // Calculate the jump size (number of integers per page)
    int jump = PAGESIZE / sizeof(int);

    // Timing the access
    clock_t start, end;
    double cpu_time_used;    

    start = clock(); // Start timing

    // Access the array based on NUMPAGES and jump
    for (int j = 0; j < iterations; j++) {
        for (int i = 0; i < NUMPAGES * jump; i += jump) {
            a[i] += 1; // Access and modify the array
        }
    }

    end = clock(); // End timing

    // Calculate elapsed time in seconds
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print results
    printf("PAGESIZE: %d bytes\n", PAGESIZE);
    printf("NUMPAGES: %d\n", NUMPAGES);
    printf("Time taken for %ld iterations: %f seconds\n", iterations, cpu_time_used);

    // Clean up
    free(a);  // Free the dynamically allocated array
    return 0; 
}
