#ifndef FUNCTION_TIMING_H
#define FUNCTION_TIMING_H

#define FUNCTIM_TIMER_START() (0)
#define FUNCTIM_TIMER_STOP()  (0)
#define FUNCTIM_TIMER_GET()   (timing_counter_get())
#define FUNCTIM_TIMER_DIFF(ptr_start, ptr_end) (timing_cycles_get(ptr_start, ptr_end))

#define FUNCTIM_GET_TIMING(func_timingTest, loop_cnt, \
        timer_count_type, result_type, result) \
    { \
        assert(loop_cnt > 0); \
        timer_count_type loop_start, loop_end; \
        timer_count_type loop1_time = 0, loop2_time = 0; \
        FUNCTIM_TIMER_START(); \
        for (int functim_iter = 0; functim_iter < loop_cnt; ++functim_iter) { \
            loop_start = FUNCTIM_TIMER_GET(); \
            loop_end = FUNCTIM_TIMER_GET(); \
            loop1_time += FUNCTIM_TIMER_DIFF(&loop_start, &loop_end); \
        } \
        FUNCTIM_TIMER_STOP(); \
        FUNCTIM_TIMER_START(); \
        for (int functim_iter = 0; functim_iter < loop_cnt; ++functim_iter) { \
            loop_start = FUNCTIM_TIMER_GET(); \
            func_timingTest(functim_iter); \
            loop_end = FUNCTIM_TIMER_GET(); \
            loop2_time += FUNCTIM_TIMER_DIFF(&loop_start, &loop_end); \
        } \
        FUNCTIM_TIMER_STOP(); \
        result = (result_type)(loop2_time - loop1_time) / (result_type)loop_cnt; \
    }

#define FUNCTIM_GET_TIMING_CHECKED(func_timingTest, loop_cnt, \
        returnType, func_returnCheck, \
        timer_count_type, result_type, result) \
    { \
        assert(loop_cnt > 0); \
        returnType returnValue; \
        timer_count_type loop_start, loop_end; \
        timer_count_type loop1_time = 0, loop2_time = 0; \
        FUNCTIM_TIMER_START(); \
        for (int functim_iter = 0; functim_iter < loop_cnt; ++functim_iter) { \
            loop_start = FUNCTIM_TIMER_GET(); \
            loop_end = FUNCTIM_TIMER_GET(); \
            loop1_time += FUNCTIM_TIMER_DIFF(&loop_start, &loop_end); \
        } \
        FUNCTIM_TIMER_STOP(); \
        FUNCTIM_TIMER_START(); \
        for (int functim_iter = 0; functim_iter < loop_cnt; ++functim_iter) { \
            loop_start = FUNCTIM_TIMER_GET(); \
            func_timingTest(functim_iter, returnValue); \
            loop_end = FUNCTIM_TIMER_GET(); \
            loop2_time += FUNCTIM_TIMER_DIFF(&loop_start, &loop_end); \
            func_returnCheck(returnValue); \
        } \
        FUNCTIM_TIMER_STOP(); \
        result = (result_type)(loop2_time - loop1_time) / (result_type)loop_cnt; \
    }

#endif // ! FUNCTION_TIMING_H
