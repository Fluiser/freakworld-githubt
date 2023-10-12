#pragma once
#include <Util/VInc.hpp>
#include <System/Util.hpp>


namespace Engine {
    namespace Window {
        namespace Wrapper {
            
            template<class T>
            struct safeWrapper: T {
                safeWrapper()
                {
                    ZeroMem(*this);
                }
            };

        }
    }
}