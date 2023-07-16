#include "function_timing.h"

//#define TEST_FUNCTION(iter) \
//{ \
//    getchar(iter); \
//}
//
// #define TEST_FUNCTION_CHECKED(iter, ret) \
//{ \
//    ret = getchar(iter); \
//}
//
// #define CHECK_RETURN(x)                 \
//    {                                   \
//        if ('c' != x)                   \
//            printf("Error: got %c", x); \
//    }

#define ITERATIONS (100U)

#define TEST_FUNCTION(iter, ret)                                          \
    {                                                                     \
        ret = pthread_create(&tid[iter], &attr[iter], thread_func, NULL); \
    }

#define CHECK_RETURN(ret)                 \
    {                                     \
        if (0 != ret)                     \
            printf("Error: got %c", ret); \
    }

int main(void)
{
    float result;

    //    FUNCTIM_GET_TIMING(TEST_FUNCTION, 100,
    //                       uint32_t, float, result);
    //
    //    FUNCTIM_GET_TIMING_CHECKED(TEST_FUNCTION_CHECKED, 100,
    //                               char, CHECK_RETURN,
    //                               uint32_t, float, result);

    FUNCTIM_GET_TIMING_CHECKED(TEST_FUNCTION, ITERATIONS,
                               int, CHECK_RETURN,
                               uint32_t, float, result);

    return 0;
}

// TODO: document 'gcc -E main.c -o main_expand.c'
