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
        if (_overflowBehavior == HIDDEN) Renderer::ImGui::PushClipRect(_body->com_position, _body->com_size, true);
        for (auto element : this->children) element->Draw();
        if (_overflowBehavior == HIDDEN) Renderer::ImGui::PopClipRect();

    }

void FlexibleContainer::UpdateInternal(const Vec2& contentStart, const Vec2& contentSize) const
{
    BoundingRect childBounds(contentStart, contentStart + contentSize);
    Vec2 currentPos = contentStart;

    float maxRight  = contentStart.x + _padding.x;
    float maxBottom = contentStart.y + _padding.y;

    float rowHeight = 0.0f;
    float colWidth  = 0.0f;
    bool didWrap = false;

    currentPos.x += _padding.x;
    currentPos.y += _padding.y;

    for (auto& child : this->children)
    {
        child->com_position.Bind(childBounds);
        child->com_size.Bind(childBounds);
        child->com_size.Update();

        if (auto rect = dynamic_cast<Shapes::Rectangle*>(child.get())) {
            rect->com_rounding.Update(rect->renderer->Height);
        }

        Vec2 childSize = child->com_size.ProperSize;

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
                    rowHeight = 0.0f;
                    didWrap = true;
                }
                child->com_position.ProperPosition = currentPos;
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
                    didWrap = true;
                }
                currentPos.x -= childSize.x;
                child->com_position.ProperPosition = currentPos;
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
                    didWrap = true;
                }
                child->com_position.ProperPosition = currentPos;
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
                    didWrap = true;
                }
                currentPos.y -= childSize.y;
                child->com_position.ProperPosition = currentPos;
                currentPos.y -= _gap.y;
                colWidth = std::max(colWidth, childSize.x);
                break;
            }
        }

        maxRight  = std::max(maxRight,  child->com_position.ProperPosition.x + childSize.x);
        maxBottom = std::max(maxBottom, child->com_position.ProperPosition.y + childSize.y);

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
            this->_body->com_size.ProperSize = contentSize + Vec2(_padding.x + _padding.z, _padding.y + _padding.w);
            break;

        case ENLARGE:
            // Automatically resize container to fit children
            this->_body->com_size.ProperSize = neededSize + Vec2(_padding.x + _padding.z, _padding.y + _padding.w);
            break;
    }

}



    void FlexibleContainer::Update(Vec2 newbounds)
    {
        BoundingRect ParentBounds(
            this->com_position.ProperPosition,
            this->com_position.ProperPosition + newbounds
        );

        this->_body->com_position.Bind(ParentBounds);
        this->_body->com_size.Bind(ParentBounds);
        this->_body->com_position.Update();
        this->_body->com_size.Update();

        if (auto rect = dynamic_cast<Shapes::Rectangle*>(this->_body.get()))
            rect->com_rounding.Update(rect->renderer->Height);

        Vec2 contentStart = this->_body->com_position.ProperPosition + Vec2(_padding.x, _padding.y);
        Vec2 contentSize  = this->_body->com_size.ProperSize - Vec2(_padding.x + _padding.z, _padding.y + _padding.w);

        UpdateInternal(contentStart, contentSize);
    }

    void FlexibleContainer::Update()
    {

        if (auto parent = this->parent.lock())
        {
            BoundingRect ParentBounds(
                parent->com_position.ProperPosition,
                parent->com_position.ProperPosition + parent->com_size.ProperSize
            );
            this->_body->com_position.Bind(ParentBounds);
            this->_body->com_size.Bind(ParentBounds);
        }

        this->_body->com_position.Update();
        this->_body->com_size.Update();

        if (auto rect = dynamic_cast<Shapes::Rectangle*>(this->_body.get()))
            rect->com_rounding.Update(rect->renderer->Height);

        Vec2 contentStart = this->_body->com_position.ProperPosition + Vec2(_padding.x, _padding.y);
        Vec2 contentSize  = this->_body->com_size.ProperSize - Vec2(_padding.x + _padding.z, _padding.y + _padding.w);

        UpdateInternal(contentStart, contentSize);
    }
}

