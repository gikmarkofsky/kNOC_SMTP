
#include "kNOC_SMTP__StreamOfDataOnRAM.hpp"

namespace kNOC_SMTP::Utils 
{
    class Serializable
    {
        //________________________________PUBLIC________________________________________
        virtual void SerializeInto(kNOC_SMTP::Utils::StreamOfDataOnRAM) = 0;
        virtual void DeserializeFrom(kNOC_SMTP::Utils::StreamOfDataOnRAM) = 0;

    };
}