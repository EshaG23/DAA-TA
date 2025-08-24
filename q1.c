#include <stdio.h>
#include <stdbool.h>
// Initialize: each element is its own parent
void initialize(int Arr[], int N) 
{
    for (int i = 0; i < N; i++)
        Arr[i] = i;
}
// Find: check if A and B belong to the same set
bool find(int Arr[], int A, int B) 
{
    return Arr[A] == Arr[B];
}
// Union: merge the set of A into the set of B
void unionSet(int Arr[], int N, int A, int B) 
{
    int TEMP = Arr[A];
    for (int i = 0; i < N; i++) 
    {
        if (Arr[i] == TEMP)
            Arr[i] = Arr[B];
    }
}
// Print all sets after current operation
void printSets(int Arr[], int N) 
{
    printf("Current Sets: ");
    for (int i = 0; i < N; i++) 
    {
        printf("{");
        int group = Arr[i];
        for (int j = 0; j < N; j++) 
        {
            if (Arr[j] == group)
                printf("%d ", j);
        }
        printf("} ");
    }
    printf("\n");
}
int main() 
{
    int N = 5;
    int Arr[N];
    // Step 1: Initialize
    initialize(Arr, N);
    printf("Initially:\n");
    printSets(Arr, N);
    // Step 2: Union(0,1)
    printf("\nPerform union(0,1)\n");
    unionSet(Arr, N, 0, 1);
    printSets(Arr, N);
    // Step 3: Union(2,3)
    printf("\nPerform union(2,3)\n");
    unionSet(Arr, N, 2, 3);
    printSets(Arr, N);
    // Step 4: Use find()
    printf("\nCheck find(0,1): %s\n", find(Arr,0,1) ? "Connected" : "Not Connected");
    printf("Check find(0,2): %s\n", find(Arr,0,2) ? "Connected" : "Not Connected");
    // Step 5: Union(1,3)
    printf("\nPerform union(1,3)\n");
    unionSet(Arr, N, 1, 3);
    printSets(Arr, N);
    // Step 6: Final Find
    printf("\nCheck find(0,3): %s\n", find(Arr,0,3) ? "Connected" : "Not Connected");
    return 0;
}
