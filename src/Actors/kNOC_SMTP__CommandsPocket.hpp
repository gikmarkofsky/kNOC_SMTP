#pragma once

#include <mutex>
#include <queue>

#include "../Utils/kNOC_SMTP__StreamOfDataOnRAM.hpp"

namespace kNOC_SMTP::Actors 
{
    template <typename IncomeMessagesType, typename OutcomeMessagesType>
    struct CommandsPocket
    {
        ::std::mutex
        mutex;

        ::std::queue<IncomeMessagesType>
        incomeMessages;

        ::std::queue<kNOC_SMTP::Utils::StreamOfDataOnRAM *> 
        incomeDataStreams;

        ::std::queue<OutcomeMessagesType>
        outcomeMessages;

        ::std::queue<kNOC_SMTP::Utils::StreamOfDataOnRAM *> 
        outcomeDataStreams;
    };
}