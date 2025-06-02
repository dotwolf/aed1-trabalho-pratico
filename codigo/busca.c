#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const char* written_paths[] = {
    "../dados/ordenado/pequeno.bin",
    "../dados/ordenado/medio.bin",
    "../dados/ordenado/grande.bin"
};
const int sizes[] = {
    18000,  // Pequeno
    90000, // Medio
    210000 // Grande
};

int linear_search(int v[], int size, int n, long long *comparisons){
    for (int i = 0; i < size; i++){
        (*comparisons)++;
        if (v[i] == n){
            return i;
        }
    }
    return -1;
}

int binary_search(int v[], int size, int n, long long *comparisons){
    int left = 0; int right = size-1;
    while (left <= right){
        int center = left + (right-left) / 2;
        (*comparisons)++;
        if (v[center] == n){
            return center;
        }
        if (v[center] < n){
            left = center+1;
        } else {
            right = center-1;
        }
    }
    return -1;
}

int main(){
    const int repetitions = 100000;

    for (int i = 0; i < 3; i++){
        int *data = malloc(sizes[i] * sizeof(int));
        if (data == NULL){
            return 1;
        }
        FILE *file = fopen(written_paths[i],"rb");
        if (file == NULL){
            return 1;
        }
        fread(data,sizes[i],sizeof(int),file);
        fclose(file);

        int target = data[sizes[i]-1]+1;

        long long seq_comparisons = 0;
        clock_t start = clock();
        int pos_seq;
        for (int j = 0; j < repetitions; j++){
            pos_seq = linear_search(data, sizes[i], target, &seq_comparisons);
        };
        clock_t end = clock();
        double time_seq = (double)(end - start) / CLOCKS_PER_SEC;

        long long bin_comparisons = 0;
        start = clock();
        int pos_bin;
        for (int j = 0; j < repetitions; j++){
            pos_bin = binary_search(data, sizes[i], target, &bin_comparisons);
        };
        end = clock();
        double time_bin = (double)(end - start) / CLOCKS_PER_SEC;
        
        free(data);
    
        printf("\nTamanho: %d\n", sizes[i]);
        printf("Alvo: %d\n", target);
        printf("Numero de repeticoes: %d\n", repetitions);
        printf("Busca sequencial: encontrou em %d, em %.5f segundos (%.3f microsegundos/repeticao); teve %lld comparacoes (%.2f por repeticao)\n", pos_seq, time_seq, time_seq/repetitions*1e6,seq_comparisons,(double)seq_comparisons/repetitions);
        printf("Busca binaria: encontrou em %d, em %.5f segundos (%.3f microsegundos/repeticao); teve %lld comparacoes (%.2f por repeticao)\n\n", pos_bin, time_bin, time_bin/repetitions*1e6,bin_comparisons,(double)bin_comparisons/repetitions);
    }
    return 0;
}