
#include "kNOC_SMTP__FileInRAMStream.hpp"

class Serializable
{
    //________________________________PUBLIC________________________________________
    virtual void SerializeInto(kNOC_SMTP::Utils::FileInRAMStream) = 0;
    virtual void DeserializeFrom(kNOC_SMTP::Utils::FileInRAMStream) = 0;

};