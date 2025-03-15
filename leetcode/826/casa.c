int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    int output = 0;
    for (int i = 0; i < workerSize; i++) {
        // for this work, find the index of the job that has the highest difficulty
        int max = 0;
        // iterate over the list of jobs and find the most difficult job for the worker i
        for (int j = 0; j < difficultySize; j++) {
            if (profit[j] >= max && difficulty[j] <= worker[i]) {
                max = profit[j];
            }
        }
        output += max;
    }

    return output;
}