/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 // most frequent subtree sum
 // given a node, calculate its subtree sum and place into a global array
 // do it for every children

 // by the end, iterate over the global array and return the one that 
 // appears most frequently, but how do I return more than a single one?

 #include <stdlib.h>

 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

 typedef struct hash {
    int symbol;
    int occurance;
 } hash;

// could I simply use arr as the hashing array and do the checking inside the recursion?
 int helper(struct TreeNode* root, int* arr, int* ind) {
    if (root == NULL) {
        return 0;
    }

    int leftSum = helper(root->left, arr, ind);
    int rightSum = helper(root->right, arr, ind);

    int sum = root->val + leftSum + rightSum;

    arr[(*ind)++] = sum;
    return sum;
 } 

 hash *findMostFrequent(int *arr, int ind, int *cnt) {
    // add occurancies to the returned array if it does not exist and increment the
    // occurance property

    // so, I have to iterate over the global array
    // if I find a new symbol, add realloc hash and add symbol
    // if the symbol already exists, find the position and increment occurance
    *cnt = 0;
    hash *returned = NULL;

    for (int i = 0; i < ind; i++) {
        int found = 0;

        for (int j = 0; j < *cnt; j++) {
            if (returned[j].symbol == arr[i]) {
                returned[j].occurance++;
                found = 1;
                break;
            }
        }

        if (!found) {
            (*cnt)++;
            hash *temp = realloc(returned, sizeof(hash) * (*cnt));
            if (temp == NULL) {
                free(returned);
                return NULL;
            }
            returned = temp;
            returned[(*cnt) - 1].symbol = arr[i];
            returned[(*cnt) - 1].occurance = 1;
        }
    }
    return returned;
 }

int* findFrequentTreeSum(struct TreeNode* root, int* returnSize) {
    int *globalArr = (int*)malloc(sizeof(int) * 10000);
    int ind = 0;
    int cnt = 0;

    helper(root, globalArr, &ind);
    hash *final = findMostFrequent(globalArr, ind, &cnt);

    // finalCnt is for the length of the return array
    // end is the return array itself
    // max is the max number of occurance of the symbols
    int max = -999;
    int *end = NULL;
    int finalCnt = 0;

    // find the max occurance value
    for (int i = 0; i < cnt; i++) {
        if (final[i].occurance > max) {
            max = final[i].occurance;
        }
    }

    // find the symbols that match this occurance value
    for (int i = 0; i < cnt; i++) {
        if (final[i].occurance == max) {
            finalCnt++;
            int *temp = realloc(end, sizeof(int) * finalCnt);
            end = temp;
            end[finalCnt - 1] = final[i].symbol;
        }
    }

    free(globalArr);
    free(final);

    *returnSize = finalCnt;
    return end;
}