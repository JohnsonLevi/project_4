#include "algorithms/mlfq/mlfq_algorithm.hpp"

#include <cassert>
#include <stdexcept>
#include <string>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the MLFQ algorithm.
*/

MFLQScheduler::MFLQScheduler(int slice) {
    if (slice != -1) {
        throw("MLFQ does NOT take a customizable time slice");
    }
}

std::shared_ptr<SchedulingDecision> MFLQScheduler::get_next_thread() {
    std::shared_ptr<SchedulingDecision> thread  = std::make_shared<SchedulingDecision>();
    for(int i = 0; i < 10; ++i){
        if(!q[i].empty()){
            thread->thread = q[i].top();
            thread->time_slice = pow(2,i);
            this->time_slice = pow(2,i);
            

            if(thread->thread->priority == SYSTEM){
                thread->explanation = "Selected from queue " + std::to_string(i) + " (priority = SYSTEM, runtime = " + std::to_string(thread->thread->currentQueueRunTime) + "). Will run for at most " + std::to_string(thread->time_slice) + " ticks.";
            }else if(thread->thread->priority == INTERACTIVE){
                thread->explanation = "Selected from queue " + std::to_string(i) + " (priority = INTERACTIVE, runtime = " + std::to_string(thread->thread->currentQueueRunTime) + "). Will run for at most " + std::to_string(thread->time_slice) + " ticks.";
            }else if(thread->thread->priority == NORMAL){
                thread->explanation = "Selected from queue " + std::to_string(i) + " (priority = NORMAL, runtime = " + std::to_string(thread->thread->currentQueueRunTime) + "). Will run for at most " + std::to_string(thread->time_slice) + " ticks.";
            }else{
                thread->explanation = "Selected from queue " + std::to_string(i) + " (priority = BATCH, runtime = " + std::to_string(thread->thread->currentQueueRunTime) + "). Will run for at most " + std::to_string(thread->time_slice) + " ticks.";
            }
            thread->thread->currentQueueRunTime += thread->thread->get_next_burst(CPU)->length;
            q[i].pop();
            return thread;
        }
    }
    thread->thread = nullptr;
    thread->explanation = "No threads available for scheduling.";
    return thread;
}

void MFLQScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    if(pow(2,thread->mlfqQueue) <= thread->currentQueueRunTime){
        if(thread->mlfqQueue != 9){
            thread->mlfqQueue += 1;
            thread->currentQueueRunTime = 0;
        }
    }
    int value;
    if(thread->priority == SYSTEM){
        value = 1;
    }else if(thread->priority == INTERACTIVE){
        value = 2;
    }else if(thread->priority == NORMAL){
        value = 3;
    }else{
        value = 4;
    }
    for(int i = 0; i < 10; ++i){
        if(thread->mlfqQueue == i){
            q[i].push(value,thread);
        }
    }
}

size_t MFLQScheduler::size() const {
    int total = 0;
    for(int i = 0; i < 10; ++i){
        total += q[i].size();
    }
    return total;
}
