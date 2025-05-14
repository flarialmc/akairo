#pragma once

namespace akairo::Graphics {


    /*
     * This is 赤色's "Graphics Interface". This is supposed to be a backend device that will store necessary objects.
     * For example, in OpenGL not much is needed due to how easy initialization and it's use is.
     * But for DirectX11, DirectX11on12, and etc.
     * You may need multiple D3D devices to support you.
     * This is merely a storage object.
     */

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