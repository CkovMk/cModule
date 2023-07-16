# 1 "main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "main.c"
# 1 "function_timing.h" 1
# 2 "main.c" 2
# 32 "main.c"
int main(void)
{
    float result;
# 43 "main.c"
    {
        assert((100U) > 0);
        int returnValue;
        uint32_t loop_start, loop_end;
        uint32_t loop1_time = 0, loop2_time = 0;
        (0);
        for (int functim_iter = 0; functim_iter < (100U); ++functim_iter)
        {
            loop_start = (timing_counter_get());
            loop_end = (timing_counter_get());
            loop1_time += (timing_cycles_get(&loop_start, &loop_end));
        }
        (0);
        (0);
        for (int functim_iter = 0; functim_iter < (100U); ++functim_iter)
        {
            loop_start = (timing_counter_get());
            {
                returnValue = pthread_create(&tid[functim_iter], &attr[functim_iter], thread_func, NULL);
            };
            loop_end = (timing_counter_get());
            loop2_time += (timing_cycles_get(&loop_start, &loop_end));
            {
                if (0 != returnValue)
                    printf("Error: got %c", returnValue);
            };
        }
        (0);
        result = (float)(loop2_time - loop1_time) / (float)(100U);
    };

    return 0;
}
