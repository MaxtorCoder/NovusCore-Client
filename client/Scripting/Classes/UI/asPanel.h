#pragma once
#include <NovusTypes.h>
#include <entt.hpp>

#include "../../../ECS/Components/UI/UITransform.h"
#include "../../../ECS/Components/UI/UITransformEvents.h"
#include "../../../ECS/Components/UI/UIRenderable.h"
#include "asUITransform.h"

namespace UI
{
    class asPanel : public asUITransform
    {
    public:
        asPanel(entt::entity entityId);

        static void RegisterType();

        // TransformEvents Functions
        void SetEventFlag(const UITransformEventsFlags flags) { _events.SetFlag(flags); }
        void UnsetEventFlag(const UITransformEventsFlags flags) { _events.UnsetFlag(flags); }
        const bool IsClickable() const { return _events.IsClickable(); }
        const bool IsDraggable() const { return _events.IsDraggable(); }
        const bool IsFocusable() const { return _events.IsFocusable(); }
        void SetOnClickCallback(asIScriptFunction* callback);
        void SetOnDragCallback(asIScriptFunction* callback);
        void SetOnFocusCallback(asIScriptFunction* callback);

        // Renderable Functions
        void SetTexture(const std::string& texture);
        const std::string& GetTexture() const
        {
            return _renderable.texture;
        }

        void SetColor(const Color& color);
        const Color GetColor() const
        {
            return _renderable.color;
        }

        static asPanel* CreatePanel();

    private:
        UITransformEvents _events;
        UIRenderable _renderable;
    };
}