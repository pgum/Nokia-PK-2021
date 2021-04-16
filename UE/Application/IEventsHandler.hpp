#pragma once

#include "Ports/IBtsPort.hpp"
#include "Ports/ITimerPort.hpp"
#include "Ports/IUserPort.hpp"

namespace ue
{
class IEventsHandler : public IBtsEventsHandler,
                       public IUserEventsHandler,
                       public ITimerEventsHandler
{};

}  // namespace ue
