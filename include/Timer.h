#ifndef MSCNProblem_TIMER_H
#define MSCNProblem_TIMER_H
#include <Windows.h>

class Timer {
private:
    double secs;
    LARGE_INTEGER start, end, freq;
public:
    void time_start() {
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
}
    double time_stop() {
        QueryPerformanceCounter(&end);
        secs =end.QuadPart - start.QuadPart;
        secs = secs / freq.QuadPart;

        return secs;
    }
};

#endif //MSCNProblem_TIMER_H
