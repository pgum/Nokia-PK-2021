#pragma once

#include <chrono>
#include <thread>
#include <future>

namespace ue
{

class ITimerEventsHandler
{
public:
    virtual ~ITimerEventsHandler() = default;

    virtual void handleTimeout() = 0;
};

class ITimerPort
{
public:
    using Duration = std::chrono::milliseconds;

    virtual ~ITimerPort() = default;
    virtual void countTime(Duration duration) =0;
    virtual void startTimer(Duration) = 0;
    virtual void stopTimer() = 0;
};

}
