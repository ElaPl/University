#include<cstdio>
#include <cstdlib>

using namespace std;

int power[10] = {1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607};

struct field {
    int number_of_flowers;
    long long int flowers_collected;
};
long long int maksimum(long long int a, long long int b) {
    if (a > b) return a;
    else return b;
}
void down_move (field** meadow, int k, int w, int i) {
    //printf("MOVE DOWN\n");
    long long int collected = 0;
    int temporary = (i+2)%4;
    collected = meadow[i][1].flowers_collected + power[meadow[temporary][0].number_of_flowers];
    if (collected > meadow[temporary][0].flowers_collected) meadow[temporary][0].flowers_collected = collected;
    collected = meadow[i][k-2].flowers_collected + power[meadow[temporary][k-1].number_of_flowers];
    if (collected > meadow[temporary][k-1].flowers_collected) meadow[temporary][k-1].flowers_collected = collected;
    for (int j = 1; j < k-1; j++) {
        collected = maksimum(meadow[i][j-1].flowers_collected, meadow[i][j+1].flowers_collected) + power[meadow[temporary][j].number_of_flowers];
        if (collected > meadow[temporary][j].flowers_collected) {
            meadow[temporary][j].flowers_collected = collected;
        }
    }
}

void back_move(field** meadow, int k, int w, int i) {
    //printf("MOVE BACK\n");
    long long int collected = 0;
    int temporary;
    if (i - 1 < 0)
        temporary = ((i-1)%4)+4;
    else
        temporary = (i-1)%4;
   // printf("TEMPORARY :  %d\n", temporary);
    if (k == 3) {
        collected = meadow[i][2].flowers_collected + power[meadow[temporary][0].number_of_flowers];
        if (collected > meadow[temporary][0].flowers_collected)
            meadow[temporary][0].flowers_collected = collected;
        collected = meadow[i][0].flowers_collected + power[meadow[temporary][2].number_of_flowers];
        if (collected > meadow[temporary][2].flowers_collected)
            meadow[temporary][2].flowers_collected = collected;
    }
    else {
        for (int m = 0; m < 2; m++) {
            collected = meadow[i][m+2].flowers_collected + power[meadow[temporary][m].number_of_flowers];
            if (collected > meadow[temporary][m].flowers_collected)
                meadow[temporary][m].flowers_collected = collected;
            collected = meadow[i][k-3-m].flowers_collected + power[meadow[temporary][k-1-m].number_of_flowers];
            if (collected > meadow[temporary][k-1-m].flowers_collected)
                meadow[temporary][k-1-m].flowers_collected = collected;
        }
        for (int m = 2; m < k-2; m++) {
            collected = maksimum(meadow[i][m-2].flowers_collected, meadow[i][m+2].flowers_collected) + power[meadow[temporary][m].number_of_flowers];
            if (collected > meadow[temporary][m].flowers_collected)
                meadow[temporary][m].flowers_collected = collected;
        }
    }
}

void write(field** meadow, int w, int k) {
   //printf("TABLICA NUMBER OF FLOWERS\n");
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d ", meadow[i][j].number_of_flowers);
        }
        printf("\n");
    }
}

void write_max(field** meadow, int w, int k) {
    //printf("TABLICA FLOWER COLLECTED\n");
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < k; j++) {
            printf("%lld ", meadow[i][j].flowers_collected);
        }
        printf("\n");
    }
}
long long int take_max(field* tab, int k) {
    long long int maximum = tab[0].flowers_collected;
       for (int i = 1; i < k; i++) {
        if (tab[i].flowers_collected > maximum)
            maximum = tab[i].flowers_collected;
    }
    return maximum;
}

int main() {
    int w,k;
    int pt = 1;
    scanf("%d%d", &w, &k);
    char sign;
    int rest = 0, rest2 = 0;
    field **meadow = new field *[4];
    scanf("%c", &sign);
    if (w == 3) {
        for (int i = 0; i < 3; i++) {
            meadow[i] = new field[k];
            for (int j = 0; j < k; j++) {
                scanf("%c", &sign);
                meadow[i][j].number_of_flowers = (int)sign - 48;
                meadow[i][j].flowers_collected = 0;
            }
        scanf("%c", &sign);
        }
        for (int i = 0; i < k; i++) {
            meadow[0][i].flowers_collected = power[meadow[0][i].number_of_flowers];
        }
        down_move(meadow,k,w,0);
    }
    else {
        for (int i = 0; i < 4; i++) {
            meadow[i] = new field[k];
            for (int j = 0; j < k; j++) {
                scanf("%c", &sign);
                meadow[i][j].number_of_flowers = (int)sign - 48;
                meadow[i][j].flowers_collected = 0;
            }
            scanf("%c", &sign);
        }
        for (int i = 0; i < k; i++) {
            meadow[0][i].flowers_collected = power[meadow[0][i].number_of_flowers];
        }
        down_move(meadow,k,w,0);
        if (w == 4) {
            back_move(meadow, k, w, 2);
            down_move(meadow, k, w, 1);
        }
        else if (w > 4) {
            int i = 2;
            rest2 = i%4;
            while((i + 1) < (w - 1)) {
                rest2 = i%4;
                rest = (i+2) % 4;
                delete[] meadow[rest];
                meadow[rest] = new field[k];

                for (int j = 0; j < k; j++) {
                    scanf("%c", &sign);
                    meadow[rest][j].number_of_flowers = (int)sign - 48;
                    meadow[rest][j].flowers_collected = 0;
                }
                scanf("%c", &sign);
                back_move(meadow, k, w, rest2);
                down_move(meadow, k, w, (i-1)%4);
                down_move(meadow, k, w, rest2);
                i++;
                }
            rest2 = i%4;
            back_move(meadow, k, w, rest2);
            down_move(meadow, k, w, (i-1)%4);
            down_move(meadow, k, w, rest2);
            i++;
            rest2 = i%4;
            back_move(meadow, k, w, rest2);
            down_move(meadow, k, w, (i-1)%4);
        }
    }
    printf("%lld\n", take_max(meadow[(w-1)%4], k));
    return 0;
}


