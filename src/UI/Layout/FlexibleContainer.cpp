#include "FlexibleContainer.hpp"

#include <iostream>
#include <utility>

#include "Core/Renderer/ImGui.hpp"
#include "UI/Shapes/Rectangle.hpp"

namespace akairo::Layouts
{
    FlexibleContainer::FlexibleContainer(std::string name, const std::shared_ptr<Renderer::Interface>& renderer, const std::shared_ptr<Element>& _body) :
        Element(std::move(name), renderer), _direction(TOP_TO_BOTTOM), _flexBehavior(WRAP), _overflowBehavior(ENLARGE)
    {
        this->_body = _body;
    }

    FlexibleContainer::~FlexibleContainer()
    = default;

    void FlexibleContainer::remove(const std::string& name)
    {
        this->children.erase(
            std::remove_if(this->children.begin(), this->children.end(),
                [&](const std::shared_ptr<Element>& e) { return e->name == name; }),
            this->children.end()
        );
    }

    void FlexibleContainer::Draw()
    {
        this->_body->Draw();
        if (_overflowBehavior == HIDDEN) this->renderer->PushClipRect(_body->_position, _body->_size, true);
        for (const auto& element : this->children) element->Draw();
        if (_overflowBehavior == HIDDEN) this->renderer->PopClipRect();

    }

void FlexibleContainer::UpdateInternal(const Vec2& contentStart, const Vec2& contentSize) const
{
    BoundingRect childBounds(contentStart, contentStart + contentSize);
    Vec2 currentPos = contentStart;

    float maxRight  = contentStart.x + _padding.x;
    float maxBottom = contentStart.y + _padding.y;

    float rowHeight = 0.0f;
    float colWidth  = 0.0f;

    currentPos.x += _padding.x;
    currentPos.y += _padding.y;

    for (auto& child : this->children)
    {
        child->_position.Bind(childBounds);
        child->_size.Bind(childBounds);
        child->_size.Update();

        if (auto rect = dynamic_cast<Shapes::Rectangle*>(child.get())) {
            rect->com_rounding.Update(rect->renderer->Height);
        }

        Vec2 childSize = child->_size.size;

        // --- Flex layout positioning ---
        switch (_direction)
        {
            case LEFT_TO_RIGHT:
            {
                float wrapLimit = contentStart.x + contentSize.x - _padding.z;
                if (_flexBehavior == WRAP && (currentPos.x + childSize.x) > wrapLimit)
                {
                    currentPos.x = contentStart.x + _padding.x;
                    currentPos.y += rowHeight + _gap.y;
                    rowHeight = 0.0f;}
                child->_position.position = currentPos;
                currentPos.x += childSize.x + _gap.x;
                rowHeight = std::max(rowHeight, childSize.y);
                break;
            }

            case RIGHT_TO_LEFT:
            {
                float wrapLimit = contentStart.x + _padding.x;
                if (_flexBehavior == WRAP && (currentPos.x - childSize.x) < wrapLimit)
                {
                    currentPos.x = contentStart.x + contentSize.x - _padding.z;
                    currentPos.y += rowHeight + _gap.y;
                    rowHeight = 0.0f;
                }
                currentPos.x -= childSize.x;
                child->_position.position = currentPos;
                currentPos.x -= _gap.x;
                rowHeight = std::max(rowHeight, childSize.y);
                break;
            }

            case TOP_TO_BOTTOM:
            {
                float wrapLimit = contentStart.y + contentSize.y - _padding.w;
                if (_flexBehavior == WRAP && (currentPos.y + childSize.y) > wrapLimit)
                {
                    currentPos.y = contentStart.y + _padding.y;
                    currentPos.x += colWidth + _gap.x;
                    colWidth = 0.0f;
                }
                child->_position.position = currentPos;
                currentPos.y += childSize.y + _gap.y;
                colWidth = std::max(colWidth, childSize.x);
                break;
            }

            case BOTTOM_TO_TOP:
            {
                float wrapLimit = contentStart.y + _padding.y;
                if (_flexBehavior == WRAP && (currentPos.y - childSize.y) < wrapLimit)
                {
                    currentPos.y = contentStart.y + contentSize.y - _padding.w;
                    currentPos.x += colWidth + _gap.x;
                    colWidth = 0.0f;
                }
                currentPos.y -= childSize.y;
                child->_position.position = currentPos;
                currentPos.y -= _gap.y;
                colWidth = std::max(colWidth, childSize.x);
                break;
            }
        }

        maxRight  = std::max(maxRight,  child->_position.position.x + childSize.x);
        maxBottom = std::max(maxBottom, child->_position.position.y + childSize.y);

        for (auto& grandchild : child->children)
            grandchild->Update();
    }

    // --- Compute needed size based on children ---
    Vec2 neededSize(
        maxRight - contentStart.x + _padding.z,
        maxBottom - contentStart.y + _padding.w
    );

    // --- Apply overflow behavior ---
    switch (_overflowBehavior)
    {
        case HIDDEN:
        case VISIBLE:
        case SCROLL:
            // Do not enlarge container; keep original contentSize + padding
            this->_body->_size.size = contentSize + Vec2(_padding.x + _padding.z, _padding.y + _padding.w);
            break;

        case ENLARGE:
            // Automatically resize container to fit children
            this->_body->_size.size = neededSize + Vec2(_padding.x + _padding.z, _padding.y + _padding.w);
            break;
    }

}



    void FlexibleContainer::Update(Vec2 newbounds)
    {
        BoundingRect ParentBounds(
            this->_position.position,
            this->_position.position + newbounds
        );

        this->_body->_position.Bind(ParentBounds);
        this->_body->_size.Bind(ParentBounds);
        this->_body->_position.Update();
        this->_body->_size.Update();

        if (auto rect = dynamic_cast<Shapes::Rectangle*>(this->_body.get()))
            rect->com_rounding.Update(rect->renderer->Height);

        Vec2 contentStart = this->_body->_position.position + Vec2(_padding.x, _padding.y);
        Vec2 contentSize  = this->_body->_size.size - Vec2(_padding.x + _padding.z, _padding.y + _padding.w);

        UpdateInternal(contentStart, contentSize);
    }

    void FlexibleContainer::Update()
    {

        if (auto parent = this->parent.lock())
        {
            BoundingRect ParentBounds(
                parent->_position.position,
                parent->_position.position + parent->_size.size
            );
            this->_body->_position.Bind(ParentBounds);
            this->_body->_size.Bind(ParentBounds);
        }

        this->_body->_position.Update();
        this->_body->_size.Update();

        if (auto rect = dynamic_cast<Shapes::Rectangle*>(this->_body.get()))
            rect->com_rounding.Update(rect->renderer->Height);

        Vec2 contentStart = this->_body->_position.position + Vec2(_padding.x, _padding.y);
        Vec2 contentSize  = this->_body->_size.size - Vec2(_padding.x + _padding.z, _padding.y + _padding.w);

        UpdateInternal(contentStart, contentSize);
    }
}

