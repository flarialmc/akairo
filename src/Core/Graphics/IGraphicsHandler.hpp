#pragma once

namespace akairo::Graphics {

    class IGraphicsHandler {
    public:
        virtual ~IGraphicsHandler() = default;
        virtual bool Initialize(void* wnd) = 0;
        virtual void Shutdown() = 0;
        virtual void Resize(int Width, int Height) = 0;
        int Width{};
        int Height{};
    };

}