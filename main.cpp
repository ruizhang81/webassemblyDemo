#include <emscripten.h>


extern "C"  {
    EMSCRIPTEN_KEEPALIVE
    const char* reply(const char* chr) {
        return "hi man";
    }
};
