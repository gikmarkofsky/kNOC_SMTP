

#include "kNOC_SMTP__FileInRAMStream.hpp"
/*
HEADER: kNOC_SMTP__FileInRAMStream.hpp
___________________________________________________________________________________________

namespace kNOC_SMTP::Utils
{
    enum class CARRIAGE_MOVE_ERROR
    {
        REACH_RIGHT_DEAD_END,
        REACH_LEFT_DEAD_END
    };

    // Note: be aware, that you should move the "carriage" manually after reading/writing
    class FileInRAMStream
    {
        //_________________________________PUBLIC__________________________________________
        public:
            ::std::timed_mutex timedMutex;

            void PlaceCarriageToTheStart();
            void PlaceCarriageToTheEnd();

            //- If we try to move the carriage too much left then
            // return CARRIAGE_MOVE_ERROR::REACH_LEFT_DEAD_END
            // and place the carriage to the start
            auto MoveCarriageLeftBy(::std::uint64_t) -> CARRIAGE_MOVE_ERROR;

            //- If we try to move the carriage too much left then
            // return CARRIAGE_MOVE_ERROR::REACH_RIGHT_DEAD_END
            // and place the carriage to the end
            auto MoveCarriageRightBy(::std::uint64_t) -> CARRIAGE_MOVE_ERROR;

            auto GetCarriagePosition() -> ::std::uint64_t;
            auto GetDistanceFromCarriageToEnd() -> ::std::uint64_t;

            auto ReadOneByteUnderCarriage() -> unsigned char;
            void WriteOneByteToTheEnd(unsigned char);

        //___________________________________PRIVATE_________________________________________
        private:
            ::std::vector<unsigned char> memory;
            ::std::uint64_t carriage;

    };
}
___________________________________________________________________________________________
*/

void kNOC_SMTP::Utils::FileInRAMStream:: PlaceCarriageToTheStart()
{
    this->carriage = 0;
}

void kNOC_SMTP::Utils::FileInRAMStream:: PlaceCarriageToTheEnd()
{
    this->carriage = this->memory.size();
}

auto kNOC_SMTP::Utils::FileInRAMStream:: MoveCarriageLeftBy(::std::uint64_t shift) -> CARRIAGE_MOVE_ERROR
{
    if (shift > this->carriage)
    {
        this->PlaceCarriageToTheStart();
        return CARRIAGE_MOVE_ERROR::REACH_LEFT_DEAD_END;
    }
}

auto kNOC_SMTP::Utils::FileInRAMStream:: MoveCarriageRightBy(::std::uint64_t shift) -> CARRIAGE_MOVE_ERROR
{
    if (shift > this->carriage)
    {
        this->PlaceCarriageToTheEnd();
        return CARRIAGE_MOVE_ERROR::REACH_RIGHT_DEAD_END;
    }
}

auto kNOC_SMTP::Utils::FileInRAMStream:: GetCarriagePosition() -> ::std::uint64_t
{
    return this->carriage;
}

auto kNOC_SMTP::Utils::FileInRAMStream:: GetDistanceFromCarriageToEnd() -> ::std::uint64_t
{
    return this->memory.size() - this->carriage;
}

auto kNOC_SMTP::Utils::FileInRAMStream:: ReadOneByteUnderCarriage() -> unsigned char
{
    return this->memory[this->carriage];
}

void kNOC_SMTP::Utils::FileInRAMStream:: WriteOneByteToTheEnd(unsigned char byte)
{
    this->memory[this->carriage] = byte;
}

