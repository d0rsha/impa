#include <cstdio>

#define MAXN (1<<19)

int val[MAXN];
int n;

int step(int depth, int curr, int &nodes) {
    if (depth == n) {
        nodes = 1;
        int val_curr = val[curr];
        return val[curr];
    }

    int left_nodes, right_nodes;
    int left_val = step(depth + 1, curr, left_nodes);
    int right_val = step(depth + 1, curr | (1 << depth), right_nodes);
    if ((left_val | right_val) == 3) {
        // left subtree and right subtree have different values, cannot be merged.
        nodes = left_nodes + right_nodes + 1;
    } else {
        nodes = 1;
    }
    return (left_val | right_val);
}

int main() {
    

    return 0;
}