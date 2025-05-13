#pragma once

namespace akairo::Graphics {

    class Interface {
    public:
        virtual ~Interface() = default;
        virtual bool Initialize(int Width, int Height) = 0;
        virtual void Shutdown() = 0;
        virtual void Resize(int Width, int Height) = 0;
        int Width{};
        int Height{};
    };

}