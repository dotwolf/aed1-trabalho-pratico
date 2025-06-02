#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const char* paths[] = {
    "../dados/pequeno.bin",
    "../dados/medio.bin",
    "../dados/grande.bin"
};

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

unsigned long long comparisons = 0;
unsigned long long swaps = 0;

void reset(){
    comparisons = 0;
    swaps = 0;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    swaps++;
}

void bubble_sort(int v[], int size){
    reset();
    for (int i = 0; i < size-1; i++){
        for (int j = 0; j < size-1-i; j++){
            comparisons++;
            if (v[j] > v[j+1]){
                swap(&v[j],&v[j+1]);
            }
        }
    }
}

void opt_bubble_sort(int v[], int size){
    reset();
    for (int i = 0; i < size-1; i++){
        int swapped = 0;
        for (int j = 0; j < size-1-i; j++){
            comparisons++;
            if (v[j] > v[j+1]){
                swap(&v[j],&v[j+1]);
                swapped = 1;
            }
        }
        if (swapped == 0){
            break;
        }
    }
}

void selection_sort(int v[], int size){
    reset();
    for (int i = 0; i < size-1; i++){
        int min = i;
        for (int j = i+1; j < size; j++){
            comparisons++;
            if (v[j] < v[min]){
                min = j;
            }
        }
        if (min != i){
            swap(&v[i],&v[min]);
        }
    }
}

void opt_selection_sort(int v[], int size){
    reset();
    int left = 0; int right = size-1;
    while (left < right){
        int min = left; int max = right;
        for (int i = left; i <= right; i++){
            comparisons+=2;
            if (v[i] < v[min]){
                min = i;
            }
            if (v[i] > v[max]){
                max = i;
            }
        }
        if (min != left){
            swap(&v[left],&v[min]);
            if (max == right){
                max = min;
            }
        }
        if (max != right){
            swap(&v[right],&v[max]);
        }
        left++; right--;
    }
}

void insertion_sort(int v[], int size){
    reset();
    for (int i = 1; i < size; i++){
        int key = v[i];
        int j = i-1;
        while ((j >= 0) && (comparisons++,v[j] > key)){
            v[j+1] = v[j];
            j--;
            swaps++;
        }
        v[j+1] = key;
    }
}

void copy_array(int a[], int b[], int size){
    for (int i = 0; i < size; i++){
        a[i] = b[i];
    }
}

int main(){
    for (int i = 0; i < 3; i++){
        int *data = malloc(sizes[i] * sizeof(int));
        int *temp_data = malloc(sizes[i] * sizeof(int));
        if (data == NULL || temp_data == NULL){
            return 1;
        }
        FILE *file = fopen(paths[i],"rb");
        if (file == NULL){
            free(data);
            free(temp_data);
            return 1;
        }

        fread(data, sizeof(int), sizes[i], file);
        fclose(file);

        printf("\nTamanho: %d\n", sizes[i]);
        
        ////////// BUBBLE SORT

        copy_array(temp_data,data,sizes[i]);
        clock_t start = clock();
        bubble_sort(temp_data,sizes[i]);
        clock_t end = clock();
        double time_bubble = (double)(end-start)/CLOCKS_PER_SEC;

        printf("Bubble Sort: ordenou em: %.5f segundos, com %lld comparacoes e %lld trocas\n", time_bubble,comparisons,swaps);

        ////////// OPTIMIZED BUBBLE SORT
        copy_array(temp_data,data,sizes[i]);
        start = clock();
        opt_bubble_sort(temp_data,sizes[i]);
        end = clock();
        double time_opt_bubble = (double)(end-start)/CLOCKS_PER_SEC;

        printf("Optimized Bubble Sort: ordenou em: %.5f segundos, com %lld comparacoes e %lld trocas\n", time_opt_bubble, comparisons,swaps);

        ////////// SELECTION SORT
        copy_array(temp_data,data,sizes[i]);
        start = clock();
        selection_sort(temp_data,sizes[i]);
        end = clock();
        double time_selection = (double)(end-start)/CLOCKS_PER_SEC;

        printf("Selection Sort: ordenou em: %.5f segundos, com %lld comparacoes e %lld trocas\n", time_selection, comparisons,swaps);

        ////////// OPTIMIZED (BIDIRECTIONAL) SELECTION SORT
        copy_array(temp_data,data,sizes[i]);
        start = clock();
        opt_selection_sort(temp_data,sizes[i]);
        end = clock();
        double time_opt_selection = (double)(end-start)/CLOCKS_PER_SEC;

        printf("Optimized (Bidirectional) Selection Sort: ordenou em: %.5f segundos, com %lld comparacoes e %lld trocas\n", time_opt_selection,comparisons,swaps);

        ////////// INSERTION SORT
        copy_array(temp_data,data,sizes[i]);
        start = clock();
        insertion_sort(temp_data,sizes[i]);
        end = clock();
        double time_insertion = (double)(end-start)/CLOCKS_PER_SEC;
        unsigned long long comp_insertion = comparisons;

        printf("Insertion Sort: ordenou em: %.5f segundos, com %lld comparacoes e %lld deslocamentos\n", time_insertion, comparisons,swaps);

        FILE *write_file = fopen(written_paths[i],"wb");
        if (write_file == NULL){
            free(data);
            free(temp_data);
            return 1;
        }
        fwrite(temp_data,sizeof(int),sizes[i],write_file);
        fclose(write_file);
        free(data);
        free(temp_data);
    }
    return 0;
}