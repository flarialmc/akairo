#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <UI/Components/Color/Color.hpp>
#include <UI/Components/Position/Position.hpp>
#include <UI/Components/Size/Size.hpp>

namespace akairo
{
    class Element;
}

namespace akairo::Renderer {

    enum FrameworkType
    {
        UndefinedFramework,
        ImGUI,
        D2D
    };
    enum BackendType {

        UndefinedBackend,
        DirectX11,
        OpenGL

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

        explicit Interface(BackendType backend) {
            this->backendType = backend;
          }

        /*
         * This is an abstraction function that differs between renderers. For example,
         * There could be D2D.. ImGUI.. Pure OpenGL.. or even DirectX11.
         */
        virtual void DrawRectangle(Components::Position pos, Components::Size size, Components::Color color) const = 0;
        virtual void DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const = 0;
        virtual void DrawCircle(Components::Position pos, float radius, Components::Color color) const = 0;
        std::unordered_map<std::string, std::shared_ptr<Element>> elements;


        /*
         * Creates an element, with a name, that you can modify as you wish.
         * This is stored in the elements map. The renderer iterates through these elements
         * Then renders it in a Retained mode, ordered style.
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> CreateElement(const std::string& name, Args&&... args) {
            if (elements.find(name) != elements.end()) {
                return std::dynamic_pointer_cast<T>(elements[name]);
            }

            auto element = std::make_shared<T>(name, std::forward<Args>(args)...);
            elements[name] = std::static_pointer_cast<Element>(element);
            return element;
        }

        /*
         * Get and modify any element you want,
         * Especially one you didn't store yourself, for some reason.
         */
        std::shared_ptr<Element> GetElement(const std::string& name) {
            auto it = elements.find(name);
            if (it != elements.end()) {

                return it->second;
            }
            return nullptr;
        }
    };
}
