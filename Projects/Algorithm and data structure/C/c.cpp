#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <vector>
#include <cstring>
using namespace std;

struct point {
    long long int x,y;
    bool operator< (const point &p) const  // takiego operatora wymaga funkcja sort z biblioteki algorithms
    {
      if (x<p.x) return true;
      if (x>p.x) return false;
      return y<p.y;
    }
};

struct triangle {
    point p1, p2, p3;
    double perimeter;
    triangle(point pt1, point pt2, point pt3, double pe) : p1(pt1), p2(pt2), p3(pt3), perimeter(pe) {}
};

void print(point p) {
    printf("%lld %lld\n", p.x, p.y);
}

void print_result(triangle t) {
    print(t.p1);
    print(t.p2);
    print(t.p3);
}

int compare_by_x(const void* p1, const void *p2) {
    point* point1 = (point *)p1;
    point* point2 = (point *)p2;
    if ((point1->x) < (point2->x)) return -1;
    if ((point1->x) == (point2->x)) return 0;
    if ((point1->x) > (point2->x)) return 1;
    return 0;
}


void sort_three_by_Y (point* arr_y, int left) {
    if (arr_y[left].y > arr_y[left+1].y) swap(arr_y[left], arr_y[left+1]);
    if (arr_y[left].y > arr_y[left+2].y) swap(arr_y[left], arr_y[left+2]);
    if (arr_y[left+1].y > arr_y[left+2].y) swap(arr_y[left+1], arr_y[left+2]);
}

double distance(point p1, point p2) {
    long long a = (p1.x - p2.x) * (p1.x - p2.x);
    long long b = (p1.y - p2.y) * (p1.y - p2.y);
    return sqrt(a + b);
}

double count_perimeter(point p1, point p2, point p3) {
    double perimeter = 0;
    perimeter += distance(p1,p2);
    perimeter += distance(p2,p3);
    perimeter += distance(p3,p1);
    return perimeter;
}


int create_left_array(point* arr_y, int first, int last, point* arr, int min_x) {
    int counter = 0;
    for (int i = first; i <= last; i++) {
        if (arr_y[i].x >= min_x) {
            arr[counter++] = arr_y[i];
        }
    }
    return counter;
}

int create_right_array(point* arr_y, int first, int last, point* arr, int max_x) {
    int counter = 0;
    for (int i = first; i <= last; i++) {
        if (arr_y[i].x <= max_x) {
            arr[counter++] = arr_y[i];
        }
    }
    return counter;
}


void merge_sort(point* arr, int first, int middle, int last) { //middle+1
    const int num = last - first + 1;
    point* tab = new point[num]; // tworze tablice pomocnicza
    int first2 = 0;
    int middle2 = middle - first;
    int last2 = last - first;

    int f = first;
    for (int i = 0; i <= last2; i++) {
        tab[i] = arr[f++];
    }
   // memcpy(tab, arr+(first*sizeof(point)), sizeof(point)*num);

    f = first;
    int m2 = middle2;
    for (int i = 0; i <= last2; i++) {
       // printf("first2 %d , middle2 %d\n", first2, middle2);
        if (first2 < m2) {
            if (middle2 <= last2) {

                if(tab[first2].y < tab[middle2].y) {
                    arr[f++] = tab[first2++];
                } else {
                    arr[f++] = tab[middle2++];
                }
            } else {
                arr[f++] = tab[first2++];
            }
        } else {
            arr[f++] = tab[middle2++];
        }
    }
    delete[] tab;
}

triangle find_min_triangle(point* arr1, point* arr2, triangle t, int size_arr1, int size_arr2) {
    triangle min_triangle = t;
    int first = 0;
    int p;
    if (min_triangle.perimeter == DBL_MAX) {
        p = INT_MAX;
    }
    else {
        p = (long long int)((min_triangle.perimeter)/2.0) + 1;
    }
    for (int i = 0; i < size_arr1; i++) {
        long long int max_y = arr1[i].y + p;
        long long int min_y = arr1[i].y - p;
        while(arr2[first].y < min_y && first < size_arr2) {
            first++;
        }
        for (int j = first; j < size_arr2-1 && arr2[j+1].y < max_y; j++) {
            for (int k = j+1; k < size_arr2 && arr2[k].y < max_y; k++) {
                double perimeter = count_perimeter(arr1[i], arr2[j], arr2[k]);
                if (perimeter < min_triangle.perimeter) {
                    triangle t1(arr1[i], arr2[j], arr2[k], perimeter);
                    min_triangle = t1;
                }
            }
        }
    }
    return min_triangle;
}
void print (point* p, int l, int r, int i) {
    printf("TABLICA %d\n", i);
    for (int i = l; i <=r; i++) {
        print(p[i]);
        //printf("%lld %lld\n", p->x, p->y);
    }
}
triangle calc(point* arr_x, int left, int right, point* arr_y) {
    int n = right - left + 1;
    if (n == 3) {
        sort_three_by_Y(arr_y, left);
        double p = count_perimeter(arr_x[left], arr_x[left+1], arr_x[left+2]);
        triangle t1(arr_x[left], arr_x[left+1], arr_x[left+2], p);
        return t1;
    }
    if (n == 2) {
        if (arr_x[left].y > arr_x[right].y) {
            swap(arr_y[left], arr_y[right]);
        }
        point p;
        p.x = 0;
        p.y = 0;
        triangle t1(p, p, p, DBL_MAX);
        return t1;
    }
    else {
        int middle = (left + right) / 2;
        triangle t1 = calc(arr_x, left, middle, arr_y);
        triangle t2 = calc(arr_x, middle + 1, right, arr_y);
        triangle min_triangle = t2;
        if (t1.perimeter < t2.perimeter) min_triangle = t1;
        long long int max_x, min_x;

        if (min_triangle.perimeter == DBL_MAX) {
            max_x = INT_MAX;
            min_x = INT_MIN;
        }
        else {
            long long int d = (int)((min_triangle.perimeter)/2.0) + 1;
            max_x = arr_x[middle + 1].x + d;
            min_x = arr_x[middle + 1].x - d;
        }
        point* arrL = new point[middle - left + 1];
        point* arrR = new point[right - middle];
        int size_arrL = create_left_array(arr_y, left, middle, arrL, min_x);
        int size_arrR = create_right_array(arr_y, middle+1, right, arrR, max_x);
        if (size_arrL != 0) {
            min_triangle = find_min_triangle(arrL, arrR, min_triangle, size_arrL, size_arrR);
            min_triangle = find_min_triangle(arrR, arrL, min_triangle, size_arrR, size_arrL);

        }

       // print(arr_y, left, middle, 1);
       // print(arr_y, middle+1, right,2);
        merge_sort(arr_y, left, middle + 1, right);
       // print(arr_y, left, right,3);

        delete[] arrL;
        delete[] arrR;
        return min_triangle;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    point *points_table = new point[n];
    point *points_table2 = new point[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", &(points_table[i].x), &(points_table[i].y));
    }
    sort(points_table, points_table+n);  //nlogn

    memcpy(points_table2, points_table, n*sizeof(point)); //n
    //print(points_table2, 0, n-1, 0);
    triangle t = calc(points_table, 0, n-1, points_table2);
    print_result(t);

    delete[] points_table;

    return 0;
}
