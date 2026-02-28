#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

class SystemMonitor {
public:
    float getCPUUsage();
    float getMemoryUsage();
    float getTemperature();

private:
    unsigned long long prevIdle = 0;
    unsigned long long prevTotal = 0;
};

struct thresholds{
    float cpu_max = 80.0;
    float temp_max = 75.0;
};

#endif
