#include "algorithms/rr/rr_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the round robin algorithm.
*/

RRScheduler::RRScheduler(int slice) {    
    this->time_slice = slice;
}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {
     std::shared_ptr<SchedulingDecision> thread  = std::make_shared<SchedulingDecision>();
    if(!q.empty()){
        thread->thread = q.front();
        thread->explanation = "Selected from " + std::to_string(q.size()) + " threads. Will run for at most " + std::to_string(this->time_slice) + " ticks.";
        thread->time_slice = this->time_slice;
        q.pop();

    }
    else{
        thread->thread = nullptr;
        thread->time_slice = this->time_slice;
        thread->explanation = "No threads available for scheduling.";
    }
    return thread;
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    q.push(thread);
    //TODO Implement Me
}

size_t RRScheduler::size() const {
    //TODO: Implement me!
    return q.size();
}
