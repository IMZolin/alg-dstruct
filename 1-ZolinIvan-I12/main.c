#include"btree.h"

int main() {
    return TestSystem(stdin, stdout);
}

int TestSystem(FILE* in, FILE* out) {
    BTree tree = { BTREE_PARAM, NULL };
    btCreate(&tree);
    char buf[BUF_SIZE] = { 0 };
    char c = 0;
    int val = 0;
    while (fgets(buf, BUF_SIZE, in)) {
        sscanf(buf, "%c %d", &c, &val);
        switch (c) {
        case 'a':
            btInsert(&tree, val);
            break;
        case 'r':
            btDelete(&tree, val);
            break;
        case 'f':
            fprintf(out, "%s\n", btSearch(&tree, val) ? "yes" : "no");
            break;
        default:
            btDestroy(&tree);
            return 0;
        }
    }
    btDestroy(&tree);
    return 0;
}