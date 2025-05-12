#pragma once

namespace Graphics {

    class IGraphicsHandler {
    public:
        virtual ~IGraphicsHandler() = default;
        virtual bool Initialize() = 0;
        virtual void Shutdown() = 0;
        virtual void Resize() = 0;
    };

}