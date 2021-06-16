#include "TimerPort.hpp"

#include <thread>
namespace ue
{

TimerPort::TimerPort(common::ILogger &logger)
    : logger(logger, "[TIMER PORT]")
{}

void TimerPort::start(ITimerEventsHandler &handler)
{

    logger.logDebug("Started");
    this->handler = &handler;
}

void TimerPort::stop()
{
    logger.logDebug("Stoped");
    handler = nullptr;
}

void TimerPort::startTimer(Duration duration)
{
    running=true;
    std::thread timer(&TimerPort::countTime,this,duration);
    newThreadID= timer.get_id();
    timer.detach();
    logger.logDebug("Start timer: ", duration.count(), "ms");

}

void TimerPort::countTime(Duration duration) {

    using namespace std::literals::chrono_literals;
    auto start=std::chrono::high_resolution_clock::now();
    std::chrono::duration<float>result=0ms;

    while (duration>result){
        std::this_thread::sleep_for(200ms);
        if (!this->running){return;}

        auto end=std::chrono::high_resolution_clock::now();
        result=end-start;
        logger.logInfo(result.count());
        if (std::this_thread::get_id()!=newThreadID){return;}
    }
    handler->handleTimeout();
}

void TimerPort::stopTimer()
{

    running= false;
    logger.logDebug("Stop timer");

}

}
