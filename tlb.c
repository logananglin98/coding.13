/*

1. The timer I used is precise down to 0.000001 seconds. Using 4096 as the page size and 100000000 as the number of iterations, I can get accurate results with only one page.

2. I believe I did this right, though my graph with Codespaces looks different from the way it looks in the chapter.

5. Adding a print statement after the loop may force the compiler to run the loop every time.

6. Setting the affinity for VSCode to 1 in Task Manager may accomplish this. Using pthread_setaffinity_np can be used in the code to accomplish the same thing. If the code is allowed to move, it may result in more TLB misses than if it were to stay on the same core because the TLB would have to be created again when a process is sent to a core it hasn't ran on. 

7. Commenting out the array initialization loop, getting the results, and then uncommenting to check the results again did not create any meaningful change.

*/

#include <stdlib.h>
#include <stdio.h>S
#include <time.h>

int main(int argc, char *argv[]) {
    // Default values for page size and number of pages
    int PAGESIZE = 4096;  // Size of one page in bytes
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
