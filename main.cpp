#include <stdio.h>
#include <inttypes.h>
#include <vector>
#include <algorithm>

#define MAIN_MATRIX  0
#define ADDED_MATRIX 1

#define ROW 1
#define COLUMN 0

int32_t gcd(int32_t a, int32_t b)
{
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;

    while (a != 0 && b != 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }

    return a + b;
}

struct elem_t
{
    int32_t val,        // val - значение эелемента в исходной матрице
            added_val,  // значение в присоединённой единичной матрице
            div,        // div - на что его потом поделить
            i, j;       // индексы в матрице
};

class CBareisMatrix
{
    public:
        int32_t size, d;
        std::vector<elem_t> elems;

        void add(int32_t i, int32_t j, int32_t val)
        {
            elem_t e;
            e.i = i;
            e.j = j;
            e.val = val;
            e.div = 1;
            e.added_val = (i == j) ? 1 : 0;
            elems.push_back(e);
        }

        void create_added_matrix()
        {
            for (int32_t i = 1; i <= size; i++) {
                for (int32_t j = size + 1; j <= size * 2; j++) {
                    elem_t e;
                    e.i = i;
                    e.j = j;
                    e.val = (i == j - size) ? 1 : 0;
                    e.div = 1;
                    e.added_val = (i == j) ? 1 : 0;
                    elems.push_back(e);
                }
            }
        }

        void print_nums()
        {
            for (int32_t i = 0; i < elems.size(); i++)
                printf("%d%d ", elems[i].i, elems[i].j);
            printf("\n");
        }

        int32_t get_item(int32_t ii, int32_t jj)
        {
            for (int32_t i = 0; i < elems.size(); i++) {
                if (elems[i].i == ii && elems[i].j == jj) {
                    return elems[i].val;
                }
            }

            return -1;
        }

        int32_t set_item(int32_t ii, int32_t jj, 
                         int32_t matrix_type, int32_t val)
        {
            int32_t f = 0;

            if (ii > size || jj > size) {
                if (jj > size)
                    jj -= size;

                f = 1;
            }

            for (int32_t t = 0; t < elems.size(); t++) {
                if (elems[t].i == ii && elems[t].j == jj) {
                    (matrix_type == MAIN_MATRIX) 
                        ? elems[t].val = val 
                        : elems[t].added_val = val;
                    break;
                }
            }

            return 0;
        }

        void print(int32_t matrix_type)
        {
            if (matrix_type == MAIN_MATRIX) {
                for (int32_t i = 1; i < size + 1; i++) {
                    for (int32_t j = 1; j < size + 1; j++) {
                        printf("%d ", get_item(i, j));
                    }
                    printf("\n");
                }
                printf("\n");
            } else {
                 for (int32_t i = 1; i < size + 1; i++) {
                    for (int32_t j = size + 1; j <= size * 2; j++) {
                        printf("%d ", get_item(i, j));
                    }
                    printf("\n");
                }
                printf("\n");
            }
         }

        void print_reslut_matrix()
        {
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            for (int32_t i = 1; i < size + 1; i++) {
                for (int32_t j = size + 1; j <= size * 2; j++) {
                    int32_t _gcd = gcd(get_item(i, j), d);
                    printf("%d/%d| ", get_item(i, j) / _gcd, 
                                      d / _gcd);
                    //printf("%d ", get_item(i, j));
                }
                printf("\n");
            }
            printf("\n");
        }

        int32_t bareis1(int32_t index, int32_t p)
        {
            std::vector<elem_t> tmp(elems);
            int32_t ret = get_item(index, index);

            for (int32_t i = 1; i <= size; i++) {
                for (int32_t j = 1; j <= 2 * size; j++) {
                    if (i != index) {
                        int32_t flag    = 0,
                                new_val = (get_item(index, index) * get_item(i, j)
                                                -get_item(i, index) * get_item(index, j)) / p;
                        for (int32_t t = 0; t < tmp.size(); t++) {
                            if (tmp[t].i == i && tmp[t].j == j) {
                                    tmp[t].val = new_val;
                                break;
                            }
                        }
                    }
                }
            }

            elems = tmp;
            return ret;
        }

        void calc_bareis()
        {
            int32_t i = 1, p = 1;

            while (i <= size) {
                p = bareis1(i, p);
                print(MAIN_MATRIX);
                print(~MAIN_MATRIX);
                i++;
            }

            d = get_item(size, size);
        }

        int32_t nod_row_column(int32_t index, int32_t type)
        {
            switch (type) {
                case ROW:
                    {
                        int32_t *arr = new int[size];
                        int32_t max;
                        
                        for (int32_t j = 1; j <= size; j++) {
                            arr[j - 1] = get_item(index, j);
                        }

                        std::sort(arr, arr + size);

                        for (int tmp = 1; tmp <= arr[0]; ++tmp) {
                            int32_t b = 0;

                            for (int i = 0; i < size; ++i) {
                                if (arr[i] % tmp != 0) {
                                    b = 1;
                                    break;
                                }
                            }

                            if (!b) {
                                max = tmp;
                            }
                        }

                        delete [] arr;
                        return max;
                    }
                    break;
            }
        }
};

int main()
{
    CBareisMatrix *bm = new CBareisMatrix;

    bm->add(1, 1, 32);
    bm->add(1, 2, 6);
    bm->add(1, 3, 6);
    bm->add(1, 4, 32);

    bm->add(2, 1, 6);
    bm->add(2, 2, 6);
    bm->add(2, 3, 4);
    bm->add(2, 4, 24);

    bm->add(3, 1, 2);
    bm->add(3, 2, 75);
    bm->add(3, 3, 1);
    bm->add(3, 4, 43);

    bm->add(4, 1, 4);
    bm->add(4, 2, 7);
    bm->add(4, 3, 0);
    bm->add(4, 4, 34);

    bm->size = 4;
    bm->create_added_matrix();

    //printf("gcd 1 row: %d\n", bm->nod_row_column(3, ROW));

    bm->print(MAIN_MATRIX);
    bm->print(ADDED_MATRIX);
    //bm->print_nums();

    bm->calc_bareis();

    //printf("det: %d\n", bm->d);

    bm->print_reslut_matrix();

    //printf("gcd: %d\n", gcd(-5, -11));

    delete bm;
    return 0;
}
