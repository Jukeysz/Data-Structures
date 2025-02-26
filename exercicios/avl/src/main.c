#include <stdio.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} node;

// balancing FB:
// negative: RSD
// positive: RSE

int height(node *root) {
    int iEsq, iDir;

    if (root == NULL) {
        return 0;
    }

    iEsq = height(root->left);
    iDir = height(root->right);

    // adds one for each stack trace, and always increment with the max
    // between left and right
    if (iEsq > iDir) {
        return 1 + iEsq;
    } else {
        return 1 + iDir;
    }
}

int Fb(node *root) {
    return height(root->left) - height(root->right);
}

void RSE(node **root) {
    node *aux = (*root)->right;

    (*root)->right = aux->left;
    aux->left = (*root);
    (*root) = aux;
}

void RSD(node **root) {
    node *aux = (*root)->left;

    (*root)->left = aux->right;
    aux->right = (*root);
    (*root) = aux;
}

int balanceLeft(node **root) {
    int fbe = Fb((*root)->left);

    if (fbe > 0) {
        RSD(root);
        return 1;
    } else if (fbe < 0) {
        RSE(&(*root)->left);
        RSD(root);
        return 1;
    }
    return 0;
}

int balanceRight(node **root) {
    int fbr = Fb((*root)->right);

    if (fbr < 0) {
        RSE(root);
        return 1;
    } else if (fbr > 0) {
        RSD(&(*root)->left);
        RSE(root);
        return 1;
    }

    return 0;
}

int balance(node **root) {
    int fb = Fb(*root);

    if (fb > 1) {
        balanceLeft(root);
    } else if (fb < -1) {
        balanceRight(root);
    } else {
        return 0;
    }
}

int insert(node **root, int *x) {
    if (root == NULL) {
        node *n = malloc(sizeof(node));
        n->left = NULL;
        n->right = NULL;
        n->val = *x;
        (*root) = n;
        return 1;
    } else if ((*root)->val > *x) {
        if (insert(&(*root)->left, x)) {
            if (balance(root)) {
                return 0;
            } else {
                return 1;
            }
        }
    } else if ((*root)->val < *x) {
        if (insert(&(*root)->right, x)) {
            if (balance(root)) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    } else {
        return 0; // the value already exists
    }
}

int main(int argc, char const *argv[])
{
    
}
