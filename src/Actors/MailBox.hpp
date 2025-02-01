
#include <mutex>
#include <queue>

namespace kNOC_SMTP::Actors 
{
    template <typename IncomeMessagesType, typename OutcomeMessagesType>
    struct MailBox
    {
        ::std::mutex mutex;
        ::std::queue<IncomeMessagesType> incomeMessages;
        ::std::queue<OutcomeMessagesType> outcomeMessages;
    };
}