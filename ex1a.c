/*
 * Ex #1a:
 The father defines an array of one hundred thousand cells.Then the parent 
fills the array so that it is sorted. He does this by inserting into cell #0 a
random value in the range between 0 and 10 (including 0, not including 10), 
and for each additional cell the value that was in the previous cell and 
another random value in the range 0..9 will be inserted. The father then gives
birth to two children. Each child grills a million times a number between zero
and a million (including 0 and not including a million), and searches for it in
the array. Child A searches for the value serial search, child B searches for
binary search.. Each child measures how long it took him to complete the task.
 * Written by: Rotem Kashani, Mahmood Jazmawy
 * Id: 209073352, 211345277
 * Login: rotemkash, Mahmoodja
 * Input: Through the arguments vector name of a file, as well as a natural
value to be transferred to: srand.
* Output: The child will output to the file: the letter s or the letter b,
whether he searched serially or binary, how many values ​​(from the dictionary of 
values ​​that is the grill) were found in the array, how long it took to complete 
the task. At the end of the above, the father has a file of twenty lines.
The father calculates and displays two numbers (on one line, with a space 
between them): how long on average did the ten children who performed a serial
search run, how long on average did the ten children who performed a binary 
search ran. Finally, the father presents in a separate line another figure 
(third): how long it took him to run from the moment he started, 
until he finished.
 */
//=================== INCLUDES ===========================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

//====================== CONSTS ===========================
#define ARR_LEN 100000
#define MILL 1000000
#define NUM_OF_CHIL 10

//========================== PROTOTYPES ============================
void fill_array(int arr[]);

int series_search(const int arr[ARR_LEN], int num_to_search);

int doFirstChild(int arr[ARR_LEN], FILE *outFile);

int doSecondChild(int arr[ARR_LEN], FILE *outFile);

int binary_search(const int arr[ARR_LEN], int num_to_search);


//==================== MAIN =============================

int main(int argc, char *argv[]) {
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);

    if (argc != 3) {
        fprintf(stderr, "Wrong number of arguments!!");
        return EXIT_FAILURE;
    }

    FILE *outFile = fopen(argv[1], "w");
    if (outFile == NULL) {
        fprintf(stderr, "CANNOT OPEN FILE!");
        exit(EXIT_FAILURE);
    }

    srand(strtol(argv[2], NULL, 10));
    int veryBigArray[ARR_LEN];

    pid_t child_1, child_2;
    int sChildTime = 0, bChildTime = 0, fatherTime;
    int sChildAvg = 0, bChildAvg = 0;


    for (int i = 0; i < 10; ++i) {
        // re-fill the array
        fill_array(veryBigArray);

        child_1 = fork();
        if (child_1 == 0) {
            sChildTime += doFirstChild(veryBigArray, outFile);
            exit(sChildTime); // sends the time to the father
        }

        child_2 = fork();
        if (child_2 == 0) {
            bChildTime += doSecondChild(veryBigArray, outFile);
            exit(bChildTime); // sends the time to the father
        }

        // get the exit status of each child
        waitpid(child_1, &sChildTime, 0);
        waitpid(child_2, &bChildTime, 0);

        sChildAvg += WEXITSTATUS(sChildTime); //add all the times together
        sChildAvg += WEXITSTATUS(bChildTime);
    }


    // calculate the average and print it to the file
    sChildAvg = sChildAvg / NUM_OF_CHIL;
    bChildAvg = bChildAvg / NUM_OF_CHIL;
    fprintf(outFile, "%d %d\n", sChildAvg, bChildAvg);


    gettimeofday(&t1, NULL);
    fatherTime = (int) ((double) (t1.tv_usec - t0.tv_usec) / 1000000 +
                        (double) (t1.tv_sec - t0.tv_sec));
    // print the father's time in the file
    fprintf(outFile, "%d\n", fatherTime);
    
    fclose(outFile);

    return EXIT_SUCCESS;
}


/**
 * This function runs the first child's functionality.
 * it receives the array and the file. it generate 10 Million random numbers
 * then it searches each number in the big array(using primitive search method).
 * if it finds the current number it adds one to the variable that
 * hold the number of found numbers. then it returns that number.
 */
int doFirstChild(int arr[ARR_LEN], FILE *outFile) {
    int rand_num, found_times = 0;
    struct timeval t0, t1;
    int task_time;

    gettimeofday(&t0, NULL);
    // create the numbers and search for them
    for (int i = 0; i < MILL; ++i) {
        rand_num = rand() % MILL;
        if (series_search(arr, rand_num) == 1) {
            found_times++;
        }
    }
    gettimeofday(&t1, NULL);
    task_time = (int) ((double) (t1.tv_usec - t0.tv_usec) / 1000000 +
                       (double) (t1.tv_sec - t0.tv_sec));
    fprintf(outFile, "%s %d %d\n", "s", found_times, task_time);

    return task_time;
}


/**
 * This function runs the second child's functionality.
 * it receives the array and the file. it generate 10 Million random numbers
 * then it searches each number in the big array(using binary search method).
 * if it finds the current number it adds one to the variable that
 * hold the number of found numbers. it prints the proper data
 * to the file then it returns that number.
 */
int doSecondChild(int arr[ARR_LEN], FILE *outFile) {
    int rand_num, found_times = 0;
    struct timeval t0, t1;
    int task_time;

    gettimeofday(&t0, NULL);

    for (int i = 0; i < MILL; ++i) {
        rand_num = rand() % MILL;
        if (binary_search(arr, rand_num) == 1) {
            found_times++;
        }
    }
    gettimeofday(&t1, NULL);
    task_time = (int) ((double) (t1.tv_usec - t0.tv_usec) / 1000000 +
                       (double) (t1.tv_sec - t0.tv_sec));
    fprintf(outFile, "%s %d %d\n", "b", found_times, task_time);

    return task_time;
}


/**
 * this is the function that receives an array and fills it
 * with the million values
 */
void fill_array(int arr[]) {
    int prev_val = 0;
    for (int i = 0; i < ARR_LEN; ++i) {
        arr[i] = prev_val + rand() % 10;
        prev_val = arr[i];
    }
}


/**
 * This function receives an array and a number.
 * then it searches the number in the array using primitive search.
 * it goes cell by cell searching for the number.
 * returns 1 if it found it, 0 otherwise
 */
int series_search(const int arr[ARR_LEN], int num_to_search) {
    for (int i = 0; i < ARR_LEN; ++i) {
        // no need to search we reached a number that's
        // bigger and the arr is sorted
        if (arr[i] > num_to_search) {
            return 0;
        }
        if (arr[i] == num_to_search) {
            return 1; // num found
        }
    }
    return 0; // num not found
}


/**
 * This function receives an array and a number.
 * then it searches the number in the array using binary search.
 * it goes cell by cell searching for the number.
 * returns 1 if it found it, 0 otherwise
 */
int binary_search(const int arr[ARR_LEN], int num_to_search) {
    int left = 0, right = ARR_LEN - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == num_to_search) {
            return 1; // num found
        } else if (arr[mid] < num_to_search) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0; // num not found
}
