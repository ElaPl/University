#include <iostream>
#include <algorithm>

using namespace std;


struct point {
    int x,y;
    long long int carrots;
    long long int carrot_on_way;
    int length_of_way;
    point* prev;
    bool operator <(const point &p) const {
        if (x < p.x) return true;
        if (x > p.x) return false;
        return y < p.y;
    };
};

struct node {
    int min_y, max_y;
    struct point* best_point;
};

void print_table(point *points_table, long long int k) {
    for (long long int i = 0; i < k ; i++) {
        printf("%d %d %lld\n", (points_table[i].x), (points_table[i].y), (points_table[i].carrots));
    }
}

int find_max_y(point* tab, int n) {
    int max = tab[0].y;
    for (int i = 1; i < n; i++) {
        if (tab[i].y > max) {
            max = tab[i].y;
        }
    }
    return max;
}
int upper_power_of_two(int n ) {
    int ans = 1;
    while ( ans<=n ) {
        ans <<= 1;
    }
    return ans;
}

node* create_tree(int max) {
    node* tree = new node[max];
    int it = 0;
    for (int i = max>>1; i < max; i++) {
        tree[i].min_y = tree[i].max_y = (it++);
        tree[i].best_point = NULL;
    }
    for (int i = max>>2; i >0; i >>= 1) {
        for (int j = i; j < 2 * i; j++) {
            tree[j].min_y = tree[2 * j].min_y;
            tree[j].max_y = tree[2 * j + 1].max_y;
            tree[j].best_point = NULL;
        }
    }
    return tree;
}

struct point* max_point(struct point *p1, struct point *p2) {
    if (p1 == NULL) return p2;
    if (p2 == NULL) return p1;
    if ((p1->carrot_on_way) >= (p2->carrot_on_way)) return p1;
    return p2;
}

struct point* search_max(int y, node* tree, struct point* maxc, int i, int size_of_tree) {
    if (2*i >= size_of_tree) {
        return max_point(tree[i].best_point, maxc);
    }
    if (y <= tree[2*i].max_y) {
        return (search_max(y, tree, maxc, 2*i, size_of_tree));
    }
    else {
        maxc = max_point(tree[2*i].best_point, maxc);
        return (search_max(y, tree, maxc, 2*i+1, size_of_tree));
    }
}

void add_point(struct point* p, node* tree, int size_of_tree, int i) {
    tree[i].best_point = max_point(p, tree[i].best_point);
    if (2 * i <= size_of_tree - 1) {
        if (p->y <= tree[2*i].max_y ) {
            add_point(p, tree, size_of_tree, 2 * i);
        }
        else {
            add_point(p, tree, size_of_tree, 2 * i + 1);
        }
    }
}

struct point* get_back_way(point* p) {
    point *best_way = new point[p->length_of_way-1];
    for (int i = (p->length_of_way) - 2; i >= 0 ; i--) {
        best_way[i] = *p;
        p = p->prev;
    }
    return best_way;
}

int main() {
    long long int n, m;
    int k;
    scanf("%lld%lld%d", &n, &m, &k);
    k+=1;
    point *points_table = new point[k];
    points_table[0].x = 0;
    points_table[0].y = 0;
    points_table[0].prev = &points_table[0];
    points_table[0].carrot_on_way = 0;
    points_table[0].carrots = 1;
    for (int i = 1; i < k; i++) {
        scanf("%d%d%lld", &(points_table[i].x), &(points_table[i].y), &(points_table[i].carrots));
    }
    sort(points_table,points_table+k);
     printf("SORT\n");
     print_table(points_table, k);

    int max_y = find_max_y(points_table, k);

    int N = upper_power_of_two(max_y);

    node* tree = create_tree(N<<1);

    //printf("Utworzono drzewo przedzialowe o rozmiarze = %lld, tzn. 0 <= y <= %lld\n",N<<1, N-1);

    //printf("%lld %lld\n", tree[0].x, tree[0].y);

    for (int i = 0; i < k; i++) {
        point *maxc = new point();
        maxc = search_max(points_table[i].y, tree, maxc, 1, N<<1);
        points_table[i].prev = maxc;
        points_table[i].carrot_on_way += points_table[i].carrots + maxc->carrot_on_way;
        points_table[i].length_of_way = (maxc->length_of_way)+1;
        add_point(&points_table[i], tree, N<<1, 1);
    };


    printf("%lld\n%d\n", (tree[1].best_point->carrot_on_way) - 1L, (tree[1].best_point->length_of_way) - 1);
    point* best_way = get_back_way(tree[1].best_point);
    for (int i = 0; i < (tree[1].best_point->length_of_way) - 1 ; i++) {
        printf("%d %d\n", best_way[i].x, best_way[i].y);
    }
    return 0;
}