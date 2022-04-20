#include "algorithms/spn/spn_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the SPN algorithm.
*/

SPNScheduler::SPNScheduler(int slice) {
    if (slice != -1) {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread() {
    std::shared_ptr<SchedulingDecision> thread  = std::make_shared<SchedulingDecision>();
    if(!q.empty()){
        thread->thread = q.top();
        thread->explanation = "Selected from " + std::to_string(size()) + " threads. Will run to completion of burst.";
        q.pop();
    }
    else{
        thread->thread = nullptr;
        thread->explanation = "No threads available for scheduling.";
    }
 
    return thread;
}

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    q.push(thread->bursts.front()->length, thread);
}

size_t SPNScheduler::size() const {
    return q.size();
}
