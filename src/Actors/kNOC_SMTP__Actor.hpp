#pragma once

namespace kNOC_SMTP::Actors
{
    //- Parent class for all actors.
    // Constructor of children must receive an exemplar of MailBox class
    // which one will store income/outcome commands in the future.
    class Actor
    {
    //_________________________________PUBLIC__________________________________________
    public:
        int GetMaxTicksPerSecond();
        void SetMaxTicksPerSecond(int maxTicks);

        void RunLoop();

    //_________________________________PROTECTED__________________________________________
    protected:
        virtual bool PlayScenario() = 0;   

    //_________________________________PRIVATE__________________________________________
    private:
        int maxTicksPerSec = 1;
    };
}