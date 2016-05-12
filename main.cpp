#include <stdio.h>
#include <inttypes.h>

#define A 4
#define B 8

int32_t matrix [A][B] = {{7, 1, 2, 8, 1, 0, 0, 0},
                         {6, 7, 8, 9, 0, 1, 0, 0},
                         {5, 5, 6, 7, 0, 0, 1, 0},
                         {7, 1, 2, 3, 0, 0, 0, 1}
                         };

int32_t
get_item(int32_t i, int32_t j)
{
    return matrix[i][j];
}

int32_t
set_item(int32_t i, int32_t j, int32_t val)
{
    matrix[i][j] = val;
}

void
copy_matrix(int32_t dst[A][B], int32_t src[A][B])
{
    int32_t i, j;
    for (i = 0; i < A; i++) {
        for (j = 0; j < B; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

void print(int32_t m[A][B]);

int32_t bareis1(int32_t m[A][B], int32_t p, int32_t index)
{
    int32_t tmp[A][B];
    int32_t i, j;
    
    //i = 1; j = 0;
    for (i = 0; i < A; i++) {
        for (j = 0; j < B; j++) {
            if (i != index) {
                tmp[i][j] = (m[index][index] * m[i][j] - 
                            m[i][index] * m[index][j]) / p;
            }
        }
    }

    for (i = 0; i < B; i++) {
        tmp[index][i] = m[index][i];
    }
    copy_matrix(matrix, tmp);
    return m[index][index];
}

/*void
bareis()
{
    int32_t i, ti, tj, p = 1;

    for (i = 0; i < 4; i++) {
        int32_t tmp[4][4] = {0};
        for (ti = 0; ti < 4; ti++) {
            for (tj = 0; tj < 4; tj++) {
                if (ti != i) {
                    int32_t val = (get_item(i, i) * get_item(ti, tj) - 
                              get_item(ti, i) * get_item(i, tj)) / p;
                    tmp[ti][tj] = val;
                }
            }
        }

        p = get_item(i, i);
        
        for (tj = 0; tj < 4; tj++) {
            tmp[i][tj] = matrix[i][tj];
        }

        copy_matrix(matrix, tmp);
        print(matrix);
    }

    return;
}*/

void print(int32_t m[A][B])
{
    int32_t i, j;
    for (i = 0; i < A; i ++) {
        for (j = 0; j < B; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int
main()
{
    //bareis();
    //bareis1(matrix, 7, 1);
    print(matrix);

    int32_t i = 0, p = 1;

    while (i < A) {
        p = bareis1(matrix, p, i);
        print(matrix);
        i++;
    }

    return;
}
