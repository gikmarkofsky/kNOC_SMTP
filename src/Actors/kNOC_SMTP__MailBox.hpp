
#include <mutex>
#include <queue>

#include "../Utils/kNOC_SMTP__FileInRAMStream.hpp"

namespace kNOC_SMTP::Actors 
{
    template <typename IncomeMessagesType, typename OutcomeMessagesType>
    struct MailBox
    {
        ::std::mutex mutex;
        ::std::queue<IncomeMessagesType> incomeMessages;
        ::std::queue<kNOC_SMTP::Utils::FileInRAMStream *> incomeDataStreams;
        ::std::queue<OutcomeMessagesType> outcomeMessages;
        ::std::queue<kNOC_SMTP::Utils::FileInRAMStream *> outcomeDataStreams;
    };
}