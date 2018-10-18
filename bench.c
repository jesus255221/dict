#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bench.h"
#include "bloom.h"

#define DICT_FILE "cities.txt"
#define WORDMAX 256


double tvgetf()
{
    struct timespec ts;
    double sec;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    sec = ts.tv_nsec;
    sec /= 1e9;
    sec += ts.tv_sec;

    return sec;
}

int bench_test(const tst_node *root, char *out_file, const int max)
{
    char prefix[4] = "";
    char word[WORDMAX] = "";
    char **sgl;
    FILE *fp = fopen(out_file, "w");
    FILE *dict = fopen(DICT_FILE, "r");
    int idx = 0, sidx = 0;
    double t1, t2;

    if (!fp || !dict) {
        if (fp) {
            fprintf(stderr, "error: file open failed in '%s'.\n", DICT_FILE);
            fclose(fp);
        }
        if (dict) {
            fprintf(stderr, "error: file open failed in '%s'.\n", out_file);
            fclose(dict);
        }
        return 1;
    }

    sgl = (char **) malloc(sizeof(char *) * max);
    while (fscanf(dict, "%s", word) != EOF) {
        if (strlen(word) < 4)
            continue;
        strncpy(prefix, word, 3);
        prefix[3] = '\0';
        t1 = tvgetf();
        tst_search_prefix(root, prefix, sgl, &sidx, max);
        t2 = tvgetf();
        fprintf(fp, "%d %f sec\n", idx, (t2 - t1) * 1000000);
        idx++;
    }

    fclose(fp);
    fclose(dict);
    return 0;
}

int find_bench_test(const tst_node *root, char *out_file, bloom_t bloom)
{
    FILE *fp = fopen(out_file, "w");
    FILE *dict = fopen(DICT_FILE, "r");
    char word[WORDMAX] = "";
    int idx = 0;
    double t1, t2, t3, t4;
    // clock_t start_1,start_2,end_1,end_2;

    if (!fp || !dict) {
        if (fp) {
            fprintf(stderr, "error: file open failed in '%s'.\n", DICT_FILE);
            fclose(fp);
        }
        if (dict) {
            fprintf(stderr, "error: file open failed in '%s'.\n", out_file);
            fclose(dict);
        }
        return 1;
    }

    while (fscanf(dict, "%s", word) != EOF) {
        // printf("%s\n",word);
        // size_t len = strlen(word);
        // word[len] = '\0';
        // if (len && word[len - 1] == '\n')
        //    word[--len] = 0;
        t1 = tvgetf();
        tst_search(root, word);
        t2 = tvgetf();
        t3 = tvgetf();
        bloom_test(bloom, word);
        t4 = tvgetf();
        fprintf(fp, "%d %f %f nsec\n", idx, (t2 - t1) * 1000000,
                (t4 - t3) * 1000000);
        idx++;
    }

    fclose(fp);
    fclose(dict);
    return 0;
}
