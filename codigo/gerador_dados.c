#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char* paths[] = {
    "../dados/pequeno.bin",
    "../dados/medio.bin",
    "../dados/grande.bin"
};

const int sizes[] = {
    18000,  // Pequeno
    90000, // Medio
    210000 // Grande
};

void generate(const char* path,int file_size){
    FILE *file = fopen(path,"wb");
    if (file == NULL){
        return;
    }
    int *data = malloc(file_size * sizeof(int));
    if (data == NULL){
        return;
    }
    srand(time(NULL));
    for (int i = 0; i < file_size; i++){
        data[i] = rand() % 1000000;
    }

    size_t binary_data = fwrite(data, sizeof(int), file_size, file);

    if (binary_data != file_size){
        fclose(file);
        free(data);
        return;
    }

    fclose(file);
    free(data);
}

int main(){
    generate(paths[0],sizes[0]);
    generate(paths[1],sizes[1]);
    generate(paths[2],sizes[2]);
    return 0;
}