#ifndef JOB_CTL_HPP
#define JOB_CTL_HPP

#include <windows.h>
#include <string>
#include <vector>
#include <map>

// Represents the state of a job
enum class JobState {
    RUNNING,
    STOPPED, // Not directly applicable on Windows like POSIX, but can represent suspended
    DONE,
    TERMINATED
};

// Structure to hold information about a background job
struct Job {
    int jid;                 // Job ID assigned by the shell
    DWORD pid;               // Process ID from Windows
    HANDLE process_handle;   // Handle to the process
    std::string command_line;
    JobState state;
};

class JobControl {
public:
    JobControl();
    ~JobControl();

    int add_job(DWORD pid, HANDLE process_handle, const std::string& cmd);
    void update_job_states();
    std::vector<Job> get_jobs() const;
    Job* get_job_by_jid(int jid);
    Job* get_job_by_pid(DWORD pid);
    bool remove_job(int jid);
    void bring_to_foreground(int jid, bool cont = false); // cont might not be needed on Windows
    void print_jobs();

private:
    std::map<int, Job> jobs;
    int next_jid = 1;
    // Maybe track the current foreground job PID?
    DWORD foreground_pid = 0; 
};

#endif // JOB_CTL_HPP

