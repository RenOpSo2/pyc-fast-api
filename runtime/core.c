#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>

char* get_timestamp() {
    time_t now = time(NULL);
    char* ts = ctime(&now);
    ts[strlen(ts)-1] = '\0'; 
    return ts;
}

const char* get_server_metrics() {
    static char buffer[256];
    
    long ticks = sysconf(_SC_CLK_TCK);
    
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    
    snprintf(buffer, sizeof(buffer),
             "Memory: %ldKB | Timestamp: %s | PID: %d",
             usage.ru_maxrss,
             get_timestamp(),
             getpid());
    
    return buffer;
}

const char* process_request() {
    static char result[512];
    
    char* timestamp = get_timestamp();
    char* metrics = (char*)get_server_metrics();
    
    snprintf(result, sizeof(result),
             "Fast Response from C Core\n"
             "Processed: %s\n"
             "Optimized Native Code\n"
             "Metrics: %s\n"
             "Runtime: C + Flask Hybrid",
             timestamp, metrics);
    
    return result;
}

const char* get_server_info() {
    static char info[512];
    
    char* timestamp = get_timestamp();
    
    snprintf(info, sizeof(info),
             "Server Status: ONLINE\n"
             "Uptime: %s\n"
             "Engine: Flask + C Native Core\n"
             "Performance: Maximum Speed\n"
             "Architecture: Hybrid Python/C\n"
             "API Endpoints: /api/data, /api/health",
             timestamp);
    
    return info;
}

// Wrapper functions for Python
extern const char* process_request_wrapper() {
    return process_request();
}

extern const char* get_server_info_wrapper() {
    return get_server_info();
}
