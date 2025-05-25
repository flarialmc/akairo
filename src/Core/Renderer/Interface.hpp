#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <Core/Graphics/OpenGL.hpp>
#include "UI/Components/Position/Position.hpp"
#include "UI/Element.hpp"
#include "UI/Components/Color/Color.hpp"

namespace akairo
{
    class Element;
}

namespace akairo::Renderer {

    enum BackendType {

        UndefinedBackend,
        DirectX11,
        OpenGL

     };

    enum FrameworkType
    {
        UndefinedFramework,
        ImGUI,
        D2D
    };

    enum OSType
    {
        Android,
        Windows
    };

    class Interface {
    public:
        virtual ~Interface() = default;
        BackendType backendType = OpenGL;
        std::unique_ptr<Graphics::Interface> backend{};

        explicit Interface(BackendType backend) {
            this->backendType = backend;
          }

        [[nodiscard]] bool Initialize() const;

        /*
         * This is an abstraction function that differs between renderers. For example,
         * There could be D2D.. ImGUI.. Pure OpenGL.. or even DirectX11.
         */
        virtual void DrawRectangle(Components::Position pos, Components::Size size, Components::Color color) const = 0;
        virtual void DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const = 0;
        virtual void DrawCircle(Components::Position pos, float radius, Components::Color color) const = 0;
        std::unordered_map<std::string, std::unique_ptr<Element>> elements;


        /*
         * Creates an element, with a name, that you can modify as you wish.
         * This is stored in the elements map. The renderer iterates through these elements
         * Then renders it in a Retained mode, ordered style.
         */
        template<typename T, typename... Args>
        std::unique_ptr<T> CreateElement(const std::string& name, Args&&... args) {
            if (elements.find(name) != elements.end()) {
                return dynamic_cast<T*>(elements[name].get());
            }

            auto element = std::make_unique<T>(std::forward<Args>(args)..., name, this);
            T* elementPtr = element.get();
            elements[name] = std::move(element);

            return elementPtr;
        }

        /*
         * Get and modify any element you want,
         * Especially one you didn't store yourself, for some reason.
         */
        Element* GetElement(const std::string& name) {
            auto it = elements.find(name);
            if (it != elements.end()) {

                return it->second.get();
            }
            return nullptr;
        }
    };
}
