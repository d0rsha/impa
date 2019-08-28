#include <cstdio>
#include <cmath>

#define MAXN (1<<19)

int val[MAXN];

int step(int start, int end, int &nodes) {
    if (start == end) {
        int val_curr = val[start];
        return val[start];
    }
    int bit_frame = log2(end - start + 1);
    int half = log2(end - start + 1) > 0 ? log2(end - start + 1) - 1 : 0;
    int left = step(start, start + half, nodes);
    int right = step(end - half, end, nodes);

    if (left == right) 
    {
        nodes -= 2;
        return right;
    }
    else 
    {
        return -1;
    }
}

int main() {
    int n, nodes;

    printf("(1<<0) == %d , (1<<1) == %d\n", (1<<0), (1<<1));

    scanf("%d", &n);
    for (int i = 0; i < (1<<n); ++i) {
        int d, v;
        scanf("%d", &d);
        val[i] = d;
    }


    nodes = (1<<n) - 1;
    step(0, (1<<n)-1, nodes);
    printf("%d\n", nodes );
    return 0;
}
