#ifndef OPULENCE_OSTYPE_H
#define OPULENCE_OSTYPE_H

#if defined OS_WINDOWS || _WIN32 || _WIN64
    #define osWindows true
#else
    #define osWindows false
#endif

// general
#include <string>
#include <algorithm>

// os
namespace OsType {
    inline std::string osConvert(std::string path)
    {
        if ( osWindows ) {
            std::replace( path.begin(), path.end(),  '/', '\\' );
        } else {
            std::replace( path.begin(), path.end(),  '\\', '/' );
        }
        return path;
    }
}

#endif
