#pragma once

#include <cstdint>
#include <string>
#include <chrono>
#include <fstream>

namespace kNOC_SMTP::FileSystem
{
    enum class FILE_ITERFACE_FINISH_STATUS
    {
        OK,
        OPEN_FILE_ERROR,
        FILE_ACCESS_ERROR,
        CLOSE_FILE_ERROR
    };

    enum class FILE_OBJECT_INTERACTION_STATUS
    {
        OK,
        CANT_GET_PATH
    };

    using Date = ::std::chrono::time_point<std::chrono::system_clock>;

    class TextFile
    {
        private:
        ::std::string pathWithoutName;
        ::std::string name;
        ::std::fstream *textStream;
        Date creationDate;
        Date changeDate;

        public:
        auto getPathWithoutNameInto(::std::string * target) -> FILE_OBJECT_INTERACTION_STATUS;

        auto setPathWithoutName(::std::string path) -> FILE_OBJECT_INTERACTION_STATUS;

        auto getNameInto(::std::string * target) -> FILE_OBJECT_INTERACTION_STATUS;

        auto setName(::std::string target) -> FILE_OBJECT_INTERACTION_STATUS;

        auto getCreationDateInto(Date * target) -> FILE_OBJECT_INTERACTION_STATUS;

        auto getChangeDateInto(Date * target) -> FILE_OBJECT_INTERACTION_STATUS;

        auto ReadNumberOfSymbolsInto(
            std::uint16_t number, ::std::string * target
        ) -> FILE_OBJECT_INTERACTION_STATUS;

        auto WriteSymbolsFrom(
            std::uint16_t number, ::std::string * target
        ) -> FILE_OBJECT_INTERACTION_STATUS;

    };

    class FileSystemInterface
    {
        virual FILE_ITERFACE_FINISH_STATUS WriteFile(
            std::string filePath, std::string fileText
        ) = 0;

        virual FILE_ITERFACE_FINISH_STATUS ReadFile(
            std::string filePath, std::string * fileTargetText
        ) = 0;

    }

};