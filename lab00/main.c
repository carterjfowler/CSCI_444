#include <stdio.h>
#include <stdlib.h>

struct interleavedData {
    int iData;
    float fData;
    char cData;
};

struct arrayData {
    int* i_array;
    float* f_array;
    char* c_array;
};

void standard(int num) {
    fprintf( stdout, "Num is %d\n", num );
}

void external(int num) {
    FILE *file = fopen("output2.txt", "a" );
    fprintf(file, "%d\n", num);
    fclose(file);
}

void doubleMe(int num) {
    fprintf( stdout, "Num is %d\n", num * 2 );
}

void writeToStream( void (*f)(int), int n ) {
    f(n);
}

int main() {
    fprintf(stdout, "Hello C World!\n");

    float piApprox = 22.0f / 7.0f;
    float radius = 4.5f;
    float area = piApprox * radius * radius;

//    Our value of PI is 3.143.
//    A circle with radius 4.5” has an area of 63.64 sq. in.
    fprintf(stdout, "Our value of PI is %0.3f. \nA circle with radius %0.1f\" has an area of %0.2f sp. in.\n",
            piApprox, radius, area);


    float x = 0.0f, y = 0.0f, z = 0.0f, avg = 0.0f;
    FILE * pFile = fopen("input.csv","r");
    fscanf(pFile, "%f,%f,%f", &x, &y, &z);
    avg = (x + y + z) / 3.0f;
//    Read in 1.0 and 3.0 and 4.5 which averages 2.8.
    fprintf(stdout, "Read in %0.1f and %0.1f and %0.1f which averages %0.1f.\n", x, y, z, avg);
    fclose(pFile);


    int data1Size = 0;
    pFile = fopen("data1.txt", "r");
    fscanf(pFile, "%i\n", &data1Size);
    struct interleavedData* data1 = (struct interleavedData*)malloc(data1Size * sizeof(struct interleavedData));
    for (int j = 0; j < data1Size; ++j) {
        int iTemp;
        float fTemp;
        char cTemp;
        fscanf(pFile, "%i,%f,%c", &iTemp, &fTemp, &cTemp);
        data1[j].iData = iTemp;
        data1[j].fData = fTemp;
        data1[j].cData = cTemp;
    }
    int data2Size = 0;
    pFile = fopen("data2.txt", "r");
    fscanf(pFile, "%i\n", &data2Size);
    struct arrayData data2;
    data2.i_array = (int*)malloc(data2Size * sizeof(int));
    data2.f_array = (float*)malloc(data2Size * sizeof(float));
    data2.c_array = (char*)malloc(data2Size * sizeof(char));
    for (int j = 0; j < data2Size; ++j) {
        int iTemp;
        float fTemp;
        char cTemp;
        fscanf(pFile, "%i,%f,%c", &iTemp, &fTemp, &cTemp);
        data2.i_array[j] = iTemp;
        data2.f_array[j] = fTemp;
        data2.c_array[j] = cTemp;
    }

    fprintf(stdout, "Data1 size: %i\n", data1Size);
    for (int j = 0; j < data1Size; ++j) {
        fprintf(stdout, "%i, %0.1f, %c\n", data1[j].iData, data1[j].fData, data1[j].cData);
    }
    free(data1);
    fprintf(stdout, "Data2 size: %i\n", data2Size);
    for (int j = 0; j < data2Size; ++j) {
        fprintf(stdout, "%i, %0.1f, %c\n", data2.i_array[j], data2.f_array[j], data2.c_array[j]);
    }

    standard(5);
    fprintf( stdout, "The standard function is stored at 0x%p\n", standard );

    writeToStream( standard, 5 );
    writeToStream( external, 5 );
    writeToStream( doubleMe, 5 );

    return 0;
}
