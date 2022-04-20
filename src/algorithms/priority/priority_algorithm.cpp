#include "algorithms/priority/priority_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the priority algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice) {
    if (slice != -1) {
        throw("PRIORITY must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread() {
    std::shared_ptr<SchedulingDecision> thread  = std::make_shared<SchedulingDecision>();
    if(!q.empty()){
        int value;
        thread->thread = q.top();
        if(thread->thread->priority == SYSTEM){
            value = 0;
        }else if(thread->thread->priority == INTERACTIVE){
            value = 1;
        }else if(thread->thread->priority == NORMAL){
            value = 2;
        }else{
            value = 3;
        }
        thread->explanation = "[S: " + std::to_string(priority_counts[0]) + " I: " + std::to_string(priority_counts[1]) + " N: " + std::to_string(priority_counts[2]) + " B: " + std::to_string(priority_counts[3]) + "] -> ";
        priority_counts[value] -= 1;
        thread->explanation += "[S: " + std::to_string(priority_counts[0]) + " I: " + std::to_string(priority_counts[1]) + " N: " + std::to_string(priority_counts[2]) + " B: " + std::to_string(priority_counts[3]) + "]. Will run to completion of burst.";
        q.pop();
        
    }
    else{
        thread->thread = nullptr;
        thread->explanation = "No threads available for scheduling.";
    }
    return thread;
}

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    int value = 0;
    if(thread->priority == SYSTEM){
        value = 1;
        priority_counts[0] += 1;
    }else if(thread->priority == INTERACTIVE){
        value = 2;
        priority_counts[1] += 1;
    }else if(thread->priority == NORMAL){
        value = 3;
        priority_counts[2] += 1;
    }else{
        value = 4;
        priority_counts[3] += 1;
    }
    q.push(value, thread);
}

size_t PRIORITYScheduler::size() const {
    return q.size();
}
