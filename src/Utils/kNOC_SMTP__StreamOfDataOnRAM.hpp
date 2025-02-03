#pragma once

#include <cstdint>
#include <vector>
#include <mutex>

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