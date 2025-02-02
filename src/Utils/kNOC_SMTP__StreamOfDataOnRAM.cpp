

#include "kNOC_SMTP__StreamOfDataOnRAM.hpp"
/*
HEADER: kNOC_SMTP__StreamOfDataOnRAM.hpp
___________________________________________________________________________________________

namespace kNOC_SMTP::Utils
{
    enum class CARRIAGE_MOVE_STATUS
    {
        OK,
        REACH_RIGHT_DEAD_END,
        REACH_LEFT_DEAD_END
    };

    // Note: be aware, that you should move the "carriage" manually after reading/writing
    class StreamOfDataOnRAM
    {
        //_________________________________PUBLIC__________________________________________
        public:
            ::std::timed_mutex timedMutex;

            void PlaceCarriageToTheStart();
            void PlaceCarriageToTheEnd();

            //- If we try to move the carriage too much left then
            // return CARRIAGE_MOVE_STATUS::REACH_LEFT_DEAD_END
            // and place the carriage to the start
            auto MoveCarriageLeftBy(::std::uint64_t) -> CARRIAGE_MOVE_STATUS;

            //- If we try to move the carriage too much left then
            // return CARRIAGE_MOVE_STATUS::REACH_RIGHT_DEAD_END
            // and place the carriage to the end
            auto MoveCarriageRightBy(::std::uint64_t) -> CARRIAGE_MOVE_STATUS;

            auto GetCarriagePosition() -> ::std::uint64_t;
            auto GetDistanceFromCarriageToEnd() -> ::std::uint64_t;

            auto ReadOneByteUnderCarriage() -> unsigned char;
            void WriteOneByteToTheEnd(unsigned char);
            void WriteOneByteOverByteUnderCarriage();

            // Set all bytes to zero and place the carriage to the start
            void ZeroAllBytes();

        //___________________________________PRIVATE_________________________________________
        private:
            ::std::vector<unsigned char> memory;
            ::std::uint64_t carriage;

    };
}
___________________________________________________________________________________________
*/


void kNOC_SMTP::Utils::StreamOfDataOnRAM:: PlaceCarriageToTheStart()
{
    this->carriage = 0;
}


void kNOC_SMTP::Utils::StreamOfDataOnRAM:: PlaceCarriageToTheEnd()
{
    this->carriage = this->memory.size();
}

//- If we try to move the carriage too much left then
// return CARRIAGE_MOVE_STATUS::REACH_LEFT_DEAD_END
// and place the carriage to the start
auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: MoveCarriageLeftBy(::std::uint64_t shift) -> CARRIAGE_MOVE_STATUS
{
    if (shift > this->GetCarriagePosition())
    {
        this->PlaceCarriageToTheStart();
        return CARRIAGE_MOVE_STATUS::REACH_LEFT_DEAD_END;
    }
}

//- If we try to move the carriage too much left then
// return CARRIAGE_MOVE_STATUS::REACH_RIGHT_DEAD_END
// and place the carriage to the end
auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: MoveCarriageRightBy(::std::uint64_t shift) -> CARRIAGE_MOVE_STATUS
{
    if (shift > this->GetDistanceFromCarriageToEnd())
    {
        this->PlaceCarriageToTheEnd();
        return CARRIAGE_MOVE_STATUS::REACH_RIGHT_DEAD_END;
    }
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: GetCarriagePosition() -> ::std::uint64_t
{
    return this->carriage;
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: GetDistanceFromCarriageToEnd() -> ::std::uint64_t
{
    return this->memory.size() - this->carriage;
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: ReadOneByteUnderCarriage() -> unsigned char
{
    return this->memory[this->GetCarriagePosition()];
}


void kNOC_SMTP::Utils::StreamOfDataOnRAM:: WriteOneByteToTheEnd(unsigned char byte)
{
    this->memory[this->GetCarriagePosition()] = byte;
}

// Set all bytes to zero and place the carriage to the start
void kNOC_SMTP::Utils::StreamOfDataOnRAM:: ZeroAllBytes()
{ 
    this->PlaceCarriageToTheStart();

    do {
        this->WriteOneByteOverByteUnderCarriage(0);

    }while (this->MoveCarriageRightBy(1) == CARRIAGE_MOVE_STATUS::OK);

    this->PlaceCarriageToTheStart();
}

