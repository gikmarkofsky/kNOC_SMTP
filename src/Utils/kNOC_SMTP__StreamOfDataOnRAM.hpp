
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
            void WriteOneByteOverByteUnderCarriage(unsigned char);

            // Set all bytes to zero and place the carriage to the start
            void ZeroAllBytes();

        //___________________________________PRIVATE_________________________________________
        private:
            ::std::vector<unsigned char> memory;
            ::std::uint64_t carriage;

    };
}