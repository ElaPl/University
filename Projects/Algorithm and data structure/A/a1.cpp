#include <cstdio>

using namespace std;

void swap_elements(long long int &a,long long int &b) {
    long long int temp = a;
    a = b;
    b = temp;
}

void quicksort(long long int **arr, long long int left, long long int right) {
    long long int i = left, j = right, pivot = arr[0][(left + right)/2];
    while (i <= j) {
        while (arr[0][i] < pivot) i++;
        while (arr[0][j] > pivot) j--;
        if (i <= j) {
            swap_elements(arr[0][i], arr[0][j]);
            swap_elements(arr[1][i], arr[1][j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        quicksort(arr, left, j);
    }
    if (right > i) {
        quicksort(arr, i, right);
    }
}
int main() {
    long long int num_of_elem, nd, d;
    scanf("%lld", &num_of_elem);
    long long int **tab = new long long int *[2];
    for(int i = 0; i < 2; i++)
        tab[i] = new long long int [num_of_elem];
    for (long long int i = 0; i < num_of_elem; i++) {
        scanf("%lld%lld", &d, &nd);
        while (d % 2 == 0) {
            d /= 2;
            nd *= 2;
        }
        tab[0][i] = d;
        tab[1][i] = nd;
    }
    quicksort(tab, 0, num_of_elem - 1);
    long long int first = tab[0][0], counter = tab[1][0];
    long long int num_of_cords = 0;
    for (long long int i = 1; i < num_of_elem; i++) {
        if (tab[0][i] == first) {
            counter += tab[1][i];
        }
        else {
            while (counter != 0) {
                if (counter % 2 == 1) {
                    counter -= 1;
                    num_of_cords++;
                }
                counter /= 2;
            }
            first = tab[0][i];
            counter = tab[1][i];
        }
    }
    while (counter != 0) {
        if (counter % 2 == 1) {
            counter -= 1;
            num_of_cords++;
        }
        counter /= 2;
    }
    printf("%lld\n", num_of_cords);
}
