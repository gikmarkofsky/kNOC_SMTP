#pragma once

#include <cstdint>
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