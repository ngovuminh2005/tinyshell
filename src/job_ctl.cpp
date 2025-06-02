#include "job_ctl.hpp"
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>

JobControl::JobControl() : next_jid(1), foreground_pid(0) {}

// Destructor: Ensure process handles are closed if the shell exits
// while background jobs are still technically running (though they might become orphaned).
JobControl::~JobControl() {
    for (auto const& [jid, job] : jobs) {
        if (job.process_handle != NULL && job.process_handle != INVALID_HANDLE_VALUE) {
            // Check if process is still running before trying to close handle?
            // Or just close it - closing handle doesn't terminate process.
            CloseHandle(job.process_handle);
        }
    }
}

int JobControl::add_job(DWORD pid, HANDLE process_handle, const std::string& cmd) {
    int current_jid = next_jid++;
    jobs[current_jid] = {current_jid, pid, process_handle, cmd, JobState::RUNNING};
    return current_jid;
}

void JobControl::update_job_states() {
    std::vector<int> jobs_to_remove;
    for (auto& [jid, job] : jobs) {
        if (job.state == JobState::RUNNING) {
            DWORD exit_code;
            // Check if the process has exited
            if (GetExitCodeProcess(job.process_handle, &exit_code)) {
                if (exit_code != STILL_ACTIVE) {
                    job.state = JobState::DONE;
                    std::cout << std::endl; // Newline to avoid overwriting prompt
                    std::cout << "[Job " << jid << "] Done (" << exit_code << ") " << job.command_line << std::endl;
                    // Close the handle now that the process has terminated
                    CloseHandle(job.process_handle);
                    job.process_handle = NULL; // Mark handle as closed
                    jobs_to_remove.push_back(jid);
                } else {
                    // Still running
                    job.state = JobState::RUNNING;
                }
            } else {
                // Error getting exit code, maybe process terminated abnormally or handle invalid?
                std::cerr << "Error checking status for job " << jid << " (PID: " << job.pid << "). Error: " << GetLastError() << std::endl;
                job.state = JobState::TERMINATED; // Assume terminated on error
                if (job.process_handle != NULL) CloseHandle(job.process_handle);
                job.process_handle = NULL;
                jobs_to_remove.push_back(jid);
            }
        }
    }
    // Remove completed jobs from the active list after iteration
    for (int jid_to_remove : jobs_to_remove) {
        remove_job(jid_to_remove);
    }
}

std::vector<Job> JobControl::get_jobs() const {
    std::vector<Job> job_list;
    for (const auto& [jid, job] : jobs) {
        job_list.push_back(job);
    }
    // Sort by jid for consistent output
    std::sort(job_list.begin(), job_list.end(), [](const Job& a, const Job& b) {
        return a.jid < b.jid;
    });
    return job_list;
}

Job* JobControl::get_job_by_jid(int jid) {
    auto it = jobs.find(jid);
    if (it != jobs.end()) {
        return &it->second;
    }
    return nullptr;
}

Job* JobControl::get_job_by_pid(DWORD pid) {
    for (auto& [jid, job] : jobs) {
        if (job.pid == pid) {
            return &job;
        }
    }
    return nullptr;
}

bool JobControl::remove_job(int jid) {
    auto it = jobs.find(jid);
    if (it != jobs.end()) {
        // Ensure handle is closed if job is removed while potentially running (e.g., via kill builtin)
        if (it->second.process_handle != NULL && it->second.process_handle != INVALID_HANDLE_VALUE) {
             // Don't close handle here if removal is just bookkeeping after termination
             // CloseHandle(it->second.process_handle);
        }
        jobs.erase(it);
        return true;
    }
    return false;
}

// Bringing a job to the foreground on Windows is complex without full terminal control.
// This implementation simply waits for the specified job.
void JobControl::bring_to_foreground(int jid, bool cont) {
    Job* job = get_job_by_jid(jid);
    if (!job) {
        std::cerr << "fg: job not found: %" << jid << std::endl;
        return;
    }

    if (job->state != JobState::RUNNING) {
         std::cerr << "fg: job %" << jid << " is not running (" << static_cast<int>(job->state) << ")" << std::endl;
         return;
    }

    HANDLE process_handle = job->process_handle;
    DWORD pid = job->pid;
    std::string cmd = job->command_line;

    // Remove from background job list temporarily
    // We don't actually remove it until it finishes
    // jobs.erase(jid);

    std::cout << cmd << std::endl; // Echo command being brought to foreground

    // TODO: Set foreground process group (difficult/limited on Windows cmd)
    foreground_pid = pid;

    // Wait for the process to complete
    WaitForSingleObject(process_handle, INFINITE);

    DWORD exit_code;
    if (GetExitCodeProcess(process_handle, &exit_code)) {
        // Report status?
    } else {
        std::cerr << "fg: Failed to get exit code for job %" << jid << ". Error: " << GetLastError() << std::endl;
    }

    foreground_pid = 0;
    // Close handle and remove job after it finishes
    CloseHandle(process_handle);
    job->process_handle = NULL;
    job->state = JobState::DONE; // Mark as done
    remove_job(jid);
    update_job_states(); // Clean up any other finished jobs
}

void JobControl::print_jobs() {
    update_job_states(); // Ensure states are current before printing
    std::vector<Job> current_jobs = get_jobs();
    if (current_jobs.empty()) {
        // std::cout << "No active jobs." << std::endl;
        return;
    }

    for (const auto& job : current_jobs) {
        std::cout << "[" << job.jid << "]  ";
        switch (job.state) {
            case JobState::RUNNING:
                std::cout << "Running    ";
                break;
            case JobState::STOPPED:
                std::cout << "Stopped    "; // Unlikely on Windows
                break;
            case JobState::DONE:
                std::cout << "Done       ";
                break;
            case JobState::TERMINATED:
                std::cout << "Terminated ";
                break;
        }
        std::cout << " " << job.command_line << " (PID: " << job.pid << ")" << std::endl;
    }
}


