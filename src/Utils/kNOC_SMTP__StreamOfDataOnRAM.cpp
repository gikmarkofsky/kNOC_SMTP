

#include "kNOC_SMTP__StreamOfDataOnRAM.hpp"
/*
HEADER: kNOC_SMTP__StreamOfDataOnRAM.hpp
________________________________________________________________________________
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
//_________________________________PUBLIC_______________________________
    public:
        ::std::timed_mutex 
        timedMutex;

        auto
        PlaceCarriageToTheStart
        (void)
        -> void;

        auto 
        PlaceCarriageToTheEnd
        (void)
        -> void;

//- If we try to move the carriage too much left then
// return CARRIAGE_MOVE_STATUS::REACH_LEFT_DEAD_END
// and place the carriage to the start
        auto
        MoveCarriageLeftBy
        (::std::uint64_t)
        -> CARRIAGE_MOVE_STATUS;

//- If we try to move the carriage too much left then
// return CARRIAGE_MOVE_STATUS::REACH_RIGHT_DEAD_END
// and place the carriage to the end
        auto
        MoveCarriageRightBy
        (::std::uint64_t)
        -> CARRIAGE_MOVE_STATUS;

        auto
        GetCarriagePosition
        (void)                              
        -> ::std::uint64_t;

        auto
        GetDistanceFromCarriageToEnd
        (void)                     
        -> ::std::uint64_t;

        auto
        ReadOneByteUnderCarriage
        (void)                         
        -> unsigned char;

        auto
        WriteOneByteToTheEnd
        (unsigned char)
        -> void;

        auto
        WriteOneByteOverByteUnderCarriage
        (unsigned char)
        -> void;

// Set all bytes to zero and place the carriage to the start
        auto
        ZeroAllBytes
        (void)
        -> void;

//__________________________________PRIVATE_____________________________
    private:
        
        using 
        VectUint64 = 
        ::std::vector<unsigned char>;

        VectUint64
        memory;

        ::std::uint64_t
        carriage;
    };
}
________________________________________________________________________________
*/


auto kNOC_SMTP::Utils::StreamOfDataOnRAM::
PlaceCarriageToTheStart
(void)
-> void
{
    this->carriage = 0;
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM::
PlaceCarriageToTheEnd
(void)
-> void
{
    this->carriage = this->memory.size();
}


//- If we try to move the carriage too much left then
// return CARRIAGE_MOVE_STATUS::REACH_LEFT_DEAD_END
// and place the carriage to the start
auto kNOC_SMTP::Utils::StreamOfDataOnRAM::
MoveCarriageLeftBy
(::std::uint64_t shift) 
-> CARRIAGE_MOVE_STATUS
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
auto kNOC_SMTP::Utils::StreamOfDataOnRAM::
MoveCarriageRightBy
(::std::uint64_t shift) 
-> CARRIAGE_MOVE_STATUS
{
    if (shift > this->GetDistanceFromCarriageToEnd())
    {
        this->PlaceCarriageToTheEnd();
        return CARRIAGE_MOVE_STATUS::REACH_RIGHT_DEAD_END;
    }
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: 
GetCarriagePosition
(void) 
-> ::std::uint64_t
{
    return this->carriage;
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: 
GetDistanceFromCarriageToEnd
(void) 
-> ::std::uint64_t
{
    return this->memory.size() - this->carriage;
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: 
ReadOneByteUnderCarriage
(void) 
-> unsigned char
{
    return this->memory[this->GetCarriagePosition()];
}


auto kNOC_SMTP::Utils::StreamOfDataOnRAM:: 
WriteOneByteToTheEnd
(unsigned char byte)
-> void
{
    this->memory[this->GetCarriagePosition()] = byte;
}


auto
WriteOneByteOverByteUnderCarriage
(unsigned char)
-> void
{
    
}


// Set all bytes to zero and place the carriage to the start
auto kNOC_SMTP::Utils::StreamOfDataOnRAM::
ZeroAllBytes()
-> void
{ 
    this->PlaceCarriageToTheStart();

    do {
        this->WriteOneByteOverByteUnderCarriage(0);

    }while (this->MoveCarriageRightBy(1) == CARRIAGE_MOVE_STATUS::OK);

    this->PlaceCarriageToTheStart();
}

