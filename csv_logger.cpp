#include "csv_logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

CSVLogger::CSVLogger(const std::string& filename)
    : filename(filename), file_initialized(false) {
    initializeFile();
}

CSVLogger::~CSVLogger() {
    close();
}

void CSVLogger::initializeFile() {
    std::ofstream file(filename, std::ios::app);
    
    if (!file.is_open()) {
        return;  // File couldn't be opened
    }
    
    // Check if file is empty or doesn't exist
    file.seekp(0, std::ios::end);
    if (file.tellp() == 0) {
        // Write header
        file << "Timestamp,CPU (%),Memory (%),Temperature (°C)\n";
        file.flush();
    }
    
    file.close();
    file_initialized = true;
}

void CSVLogger::log(float cpu, float memory, float temperature) {
    std::ofstream file(filename, std::ios::app);
    
    if (!file.is_open()) {
        return;  // File couldn't be opened
    }
    
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    // Format timestamp
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    
    // Write CSV row
    file << ss.str() << ","
         << cpu << ","
         << memory << ","
         << temperature << "\n";
    
    file.flush();
    file.close();
}

void CSVLogger::close() {
    // Placeholder for cleanup if needed
}
