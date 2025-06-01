#pragma once
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
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

        explicit Interface(const BackendType backend) {
            this->backendType = backend;
          }

        /*
         * This is an abstraction function that differs between renderers. For example,
         * There could be D2D.. ImGUI.. Pure OpenGL.. or even DirectX11.
         */
        virtual void DrawRectangle(Components::Position pos, Components::Size size, Components::Color color) const = 0;
        virtual void DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const = 0;
        virtual void DrawCircle(Components::Position pos, float radius, Components::Color color) const = 0;

        /*
        * In the future, elements map will need to be stored in Graphics.
        * Because, we may need to swap between multiple renderers such as D2D & ImGUI.
        */
        std::map<std::string, std::shared_ptr<Element>> elements;
        virtual void Render(const std::function<void()>& func) = 0;

        /*
         * This registers an element you have built, and want to render.
         * This is stored in the elements map. The renderer iterates through these elements
         * Then renders it in a Retained mode, ordered style, when called by Renderer::Interface->Render().
         */
        template<typename T>
        void RegisterElement(const std::string& name, std::shared_ptr<T> element) {
            auto it = elements.find(name);
            if (it != elements.end()) {
                throw std::runtime_error("Element '" + name + "' is already registered");
            }

            elements[name] = element;
        }

        /*
         * Get and modify any element you want,
         * Especially one you didn't store yourself, for some reason.
         */
        template<typename T>
        std::shared_ptr<T> GetElement(const std::string& name) {
            if (const auto it = elements.find(name); it != elements.end()) {
                return std::dynamic_pointer_cast<T>(it->second);
            }
            return nullptr;
        }
    };
}
