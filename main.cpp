#include <stdio.h>
#include <inttypes.h>
#include <vector>

#define MAIN_MATRIX  0
#define ADDED_MATRIX 1

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
        int32_t size;
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
        }
};

int main()
{
    CBareisMatrix *bm = new CBareisMatrix;

    bm->add(1, 1, 32);
    bm->add(1, 2, 6);
    bm->add(1, 3, 6);
    bm->add(1, 4, 32);

    bm->add(2, 1, 65);
    bm->add(2, 2, 6);
    bm->add(2, 3, 45);
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

    bm->print(MAIN_MATRIX);
    bm->print(ADDED_MATRIX);
    bm->print_nums();

    bm->calc_bareis();

    delete bm;
    return 0;
}
