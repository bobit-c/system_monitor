#ifndef CSV_LOGGER_H
#define CSV_LOGGER_H

#include <string>

class CSVLogger {
public:
    CSVLogger(const std::string& filename = "system_monitor.csv");
    ~CSVLogger();
    
    void log(float cpu, float memory, float temperature);
    void close();

private:
    std::string filename;
    bool file_initialized;
    
    void initializeFile();
};

#endif
