#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice) {
    if (slice != -1) {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread() {
    std::shared_ptr<SchedulingDecision> thread  = std::make_shared<SchedulingDecision>();
    if(!q.empty()){
        thread->thread = q.front();
        thread->explanation = "Selected from " + std::to_string(q.size()) + " threads. Will run to completion of burst.";
        q.pop();

    }
    else{
        thread->thread = nullptr;
        thread->explanation = "No threads available for scheduling.";
    }
    return thread;
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    q.push(thread);
    // TODO: implement me!
}

size_t FCFSScheduler::size() const {
        // TODO: implement me!
        return q.size();
}
