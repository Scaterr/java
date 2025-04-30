#include<stdio.h>
#define MAX 100

typedef struct {
    int level, value, weight, items[MAX];
    float bound;
} Node;

int n, capacity, values[MAX], weights[MAX], maxvalues = 0, bestitems[MAX];

float computebound(Node u) {
    int wt = u.weight, pft = u.value, j = u.level + 1;
    
     
    while (j < n && wt + weights[j] <= capacity) {
        wt += weights[j];
        pft += values[j];
        j++;
    }

    
    if (j < n) {
        pft += (capacity - wt) * (float) values[j] / weights[j];
    }

    return pft;
}

void knapsack() {
    Node q[MAX * 10];
    int front = 0, rear = 0, i;
    Node u, v;
 
    for (i = 0; i < n; i++) u.items[i] = 0;
    u.level = -1;
    u.value = 0;
    u.weight = 0;
    u.bound = computebound(u);
    q[rear++] = u;
 
    while (front < rear) {
        u = q[front++];
 
        if (u.level == n - 1) continue;
 
        v = u;
        v.level = u.level + 1;
        v.items[v.level] = 1;
        v.value = u.value + values[v.level];
        v.weight = u.weight + weights[v.level];
        v.bound = computebound(v);
 
        if (v.weight <= capacity && v.value > maxvalues) {
            maxvalues = v.value;
            for (i = 0; i < n; i++) bestitems[i] = v.items[i];
        }

       
        if (v.bound > maxvalues) {
            q[rear++] = v;
        }
 
        v = u;
        v.level = u.level + 1;
        v.items[v.level] = 0;
        v.value = u.value;
        v.weight = u.weight;
        v.bound = computebound(v);


        if (v.bound > maxvalues) {
            q[rear++] = v;
        }
    }
}

int main() {
    int i;

    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter capacity of the knapsack: ");
    scanf("%d", &capacity);

    printf("Enter values and weights of the items:\n");
    for (i = 0; i < n; i++) {
        printf("Item %d value: ", i + 1);
        scanf("%d", &values[i]);
        printf("Item %d weight: ", i + 1);
        scanf("%d", &weights[i]);
    }

   
    knapsack();

    
    printf("\nMaximum value: %d\n", maxvalues);
    printf("Items included: ");
    for (i = 0; i < n; i++) {
        if (bestitems[i] == 1) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    return 0;
}
