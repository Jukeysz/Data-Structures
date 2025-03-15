int compare(const void *a, const void *b) {
    int a_val = *((int*)a);
    int b_val = *((int*)b);

    return a_val - b_val;
}

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    int output = 0;
    int jobs[profitSize][2];
    // [0] is  difficulty and [1] is profit

    for (int i = 0; i < profitSize; i++) {
        jobs[i][0] = difficulty[i];
        jobs[i][1] = profit[i];
    }

    qsort(jobs, profitSize, sizeof(jobs[0]), compare);

    
    for (int i = 0; i < workerSize; i++) {
        int max = 0;

        for (int j = 0; j < difficultySize; j++) {
            if (jobs[j][0] > worker[i]) {
                break;
            }
            if (jobs[j][1] > max) {
                max = jobs[j][1];
            }
        }

        output += max;
    }

    return output;
}