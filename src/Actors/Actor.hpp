#pragma once

namespace kNOC_SMTP::Actors
{
    //- Parent class for all actors.
    // Constructor of children must receive an exemplar of MailBox class
    // which one will receive/send commands in the future.
    class Actor
    {
    public:
        int GetMaxTicksPerSecond();
        void SetMaxTicksPerSecond(int maxTicks);

        void RunLoop();

    protected:
        virtual bool PlayScenario() = 0;   

    private:
        int maxTicksPerSec = 1;
    };
}