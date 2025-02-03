
#include <chrono>
#include <thread>

#include "kNOC_SMTP__Actor.hpp"
/*
HEADER: kNOC_SMTP__Actor.hpp
_______________________________________________________________________________

namespace kNOC_SMTP::Actors
{
//- Parent class for all actors.
// Constructor of children must receive an exemplar of MailBox class
// which one will store income/outcome commands in the future.
    class Actor
    {
//_________________________________PUBLIC___________________________________
    public:
        auto             
        GetMaxTicksPerSecond
        (void)
        -> ::std::uint8_t;

        auto
        SetMaxTicksPerSecond
        (int maxTicks)
        -> void;

        auto
        RunLoop
        (void)
        -> void;

//_________________________________PROTECTED________________________________
    protected:
        virtual auto    
        PlayScenario
        (void)
        -> bool
        = 0;   

//_________________________________PRIVATE__________________________________
    private:
        ::std::uint8_t
        maxTicksPerSec
        = 1;
    };
}
*/


using namespace ::std::chrono_literals;


// Getter, the destiny is clear from the name
auto kNOC_SMTP::Actors::Actor::
GetMaxTicksPerSecond
(void)
-> ::std::uint8_t
{
    return maxTicksPerSec;
}


// Setter, the destiny is clear from the name
auto kNOC_SMTP::Actors::Actor::
SetMaxTicksPerSecond
(int maxTicks)
-> void
{
    if (maxTicks > 0)
        maxTicksPerSec = maxTicks;
    else
        maxTicksPerSec = 1;
}


//- This function get a start time of the tick,
// runs a PlayScenario abstract function where inherited class should implement its logic
// and calculates a sleep time for the driving thread
auto kNOC_SMTP::Actors::Actor::
RunLoop
(void)
-> void
{
    bool shouldExit= false;
    while (!shouldExit) 
    {
        auto startTime = 
            ::std::chrono::round<::std::chrono::milliseconds>
                (::std::chrono::steady_clock::now());

        shouldExit = PlayScenario();

        auto endTime = 
            ::std::chrono::round<::std::chrono::milliseconds>
                (::std::chrono::steady_clock::now());

        auto processTime = endTime - startTime;


//- "1000ms" is a one second.
//- "(1000ms / maxTicksPerSec)"" gives a number of millisecons per one tick of 
// an Actor class
//- "(1000ms / maxTicksPerSec) - processTime" gives a time which the thread 
// should sleep before next tick
//- What should we do if the PlayScenario function ran 1,5 ticks? 
// Nothing. We will get a right remaining time anyway
        auto remainTime = (1000ms / maxTicksPerSec) - processTime;
        ::std::this_thread::sleep_for(::std::chrono::milliseconds(remainTime));
    
    }
}