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
    logger.logDebug("Start timer: ", duration.count(), "ms");
    isRunning = true;
    startTime = std::chrono::system_clock::now();
    std::thread t([&, duration](){
        while(isRunning) {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count() > duration.count()) {
                handler->handleTimeout();
                break;
            }
        }

    });
    t.detach();
}

void TimerPort::stopTimer()
{
    logger.logDebug("Stop timer");
    isRunning = false;
}

}
