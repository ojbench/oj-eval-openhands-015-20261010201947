#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_int(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

int main() {
    const char* data_file = "data.txt";
    int n;
    if (scanf("%d", &n) != 1) return 0;
    char cmd[10];
    for (int i = 0; i < n; ++i) {
        if (scanf("%s", cmd) != 1) break;
        if (strcmp(cmd, "insert") == 0) {
            char idx[65]; int val;
            scanf("%s %d", idx, &val);
            // Check for duplicate
            int exists = 0;
            FILE* fin = fopen(data_file, "r");
            if (fin) {
                char cur_idx[65]; long long cur_val;
                while (fscanf(fin, "%s %lld", cur_idx, &cur_val) == 2) {
                    if (strcmp(cur_idx, idx) == 0 && cur_val == val) { exists = 1; break; }
                }
                fclose(fin);
            }
            if (!exists) {
                FILE* fout = fopen(data_file, "a");
                if (fout) {
                    fprintf(fout, "%s %d\n", idx, val);
                    fclose(fout);
                }
            }
        } else if (strcmp(cmd, "delete") == 0) {
            char idx[65]; int val;
            scanf("%s %d", idx, &val);
            FILE* fin = fopen(data_file, "r");
            FILE* fout = fopen("data_tmp.txt", "w");
            if (fin && fout) {
                char cur_idx[65]; long long cur_val;
                while (fscanf(fin, "%s %lld", cur_idx, &cur_val) == 2) {
                    if (!(strcmp(cur_idx, idx) == 0 && cur_val == val)) {
                        fprintf(fout, "%s %lld\n", cur_idx, cur_val);
                    }
                }
            }
            if (fin) fclose(fin);
            if (fout) fclose(fout);
            rename("data_tmp.txt", data_file);
        } else if (strcmp(cmd, "find") == 0) {
            char idx[65];
            scanf("%s", idx);
            static int values[100000];
            size_t cnt = 0;
            FILE* fin = fopen(data_file, "r");
            if (fin) {
                char cur_idx[65]; long long cur_val;
                while (fscanf(fin, "%s %lld", cur_idx, &cur_val) == 2) {
                    if (strcmp(cur_idx, idx) == 0) {
                        if (cnt < 100000) {
                            values[cnt++] = (int)cur_val;
                        }
                    }
                }
                fclose(fin);
            }
            if (cnt == 0) {
                printf("null\n");
            } else {
                qsort(values, cnt, sizeof(int), compare_int);
                // output unique
                int last = values[0];
                printf("%d", last);
                for (size_t i = 1; i < cnt; ++i) {
                    if (values[i] != last) {
                        printf(" %d", values[i]);
                        last = values[i];
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}
