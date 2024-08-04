#include <stdio.h>
#include <math.h>

// Values of omega ---> global variable (as it needed to all funtion)
float wr[4] = {1, 0.707, 0, -0.707};   // real part of omega
float wi[4] = {0, -0.707, -1, -0.707}; // imginary part of omega

struct Complex
{
    float re;
    float im;
};
typedef struct Complex Complex;

void print_arr(float arrR[], float arrI[])
{
    printf("printing array\n");
    for (int i = 0; i < 8; i++)
    {
        if ((arrI[i]) < 0)
        {
            float value = -(arrI[i]);
            printf("%f - %f i\n", arrR[i], value);
        }
        else if (arrI[i] != 0)
        {
            printf("%f + %f i\n", arrR[i], arrI[i]);
        }
        else
        {
            printf("%f\n", arrR[i]);
        }
    }
}

void complex_multiplication(float ar, float ai, float br, float bi, float* r,float * i)
{
    // float r, i;
    // float arc = ar;
    // float aic = ai;
    *r = ar * br - ai * bi;
    *i = ai * br + ar * bi;
  
    
}

void stage_1(float input_arr[], float *output)
{
    float func_arr[8] = {input_arr[0], input_arr[4], input_arr[2], input_arr[6], input_arr[1], input_arr[5], input_arr[3], input_arr[7]};
    // print_arr(func_arr);
    output[0] = func_arr[0] + wr[0] * func_arr[1];
    output[1] = func_arr[0] - wr[0] * func_arr[1];
    output[2] = func_arr[2] + wr[0] * func_arr[3];
    output[3] = func_arr[2] - wr[0] * func_arr[3];
    output[4] = func_arr[4] + wr[0] * func_arr[5];
    output[5] = func_arr[4] - wr[0] * func_arr[5];
    output[6] = func_arr[6] + wr[0] * func_arr[7];
    output[7] = func_arr[6] - wr[0] * func_arr[7];
}

void stage_2(float arr[], float *outputR, float *outputI)
{
    outputR[0] = arr[0] + wr[0] * arr[2];
    outputR[1] = arr[1];
    outputI[1] = wi[2] * arr[3];
    outputR[2] = arr[0] - wr[0] * arr[2];
    outputR[3] = arr[1];
    outputI[3] = -wi[2] * arr[3];
    outputR[4] = arr[4] + wr[0] * arr[6];
    outputR[5] = arr[5];
    outputI[5] = wi[2] * arr[7];
    outputR[6] = arr[4] - wr[0] * arr[6];
    outputR[7] = arr[5];
    outputI[7] = -wi[2] * arr[7];
}

void stage_3(float arrR[], float arrI[], float *outputR, float *outputI)
{
    float r1, r2, i2, i1;
    complex_multiplication(arrR[5], arrI[5], wr[1], wi[1],&r1,&i1);
    complex_multiplication(arrR[7], arrI[7], wr[3], wi[3],&r2,&i2);
    // printf("%f,%f",r1,r2);
    outputR[0] = arrR[0] + wr[0] * arrR[4];
    outputR[1] = arrR[1] + r1;
    outputI[1] = arrI[1] + i1;
    outputR[2] = arrR[2];
    outputI[2] = -arrR[6];
    outputR[3] = arrR[3] + r2;
    outputI[3] = arrI[3] + i2;

    outputR[4] = arrR[0] - arrR[4];
    outputR[5] = arrR[1] - r1;
    outputI[5] = arrI[1] - i1;
    outputR[6] = arrR[2];
    outputI[6] = arrR[6];
    outputR[7] = arrR[3] - r2;
    outputI[7] = arrI[3] - i2;
}

float main()
{
    // input of 8 numbers
    float arr[8] ;
    float result_arr[8];
    printf("Please Enter numbers\n");
    for (int i = 0; i < 8; i++)
    {
        scanf("%f", &arr[i]);
    }

    // stage 1 working
    float out1R[8];
    float out1I[8];
    stage_1(arr, out1R);
    // print_arr(out1R, out1I);

    // stage 2 working
    float out2R[8];
    float out2I[8];
    stage_2(out1R, out2R, out2I);
    // print_arr(out2R, out2I);

    // stage 3 working
    float out3R[8];
    float out3I[8];
    stage_3(out2R, out2I, out3R, out3I);
    print_arr(out3R, out3I);
    return 0;
}