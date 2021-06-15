#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include <future>
namespace ue
{

class TimerPort : public ITimerPort
{
public:
    TimerPort(common::ILogger& logger);

    void start(ITimerEventsHandler& handler);
    void stop();

    // ITimerPort interface
    void startTimer(Duration duration) override;
    void stopTimer() override;
    void countTime(Duration duration) override;
private:
    bool running= false;
    common::PrefixedLogger logger;
    ITimerEventsHandler* handler = nullptr;
};

}
