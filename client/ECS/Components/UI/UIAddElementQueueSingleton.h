#pragma once
#include <NovusTypes.h>
#include <Utils/ConcurrentQueue.h>
#include <entt.hpp>
#include "../../Components/UI/UITransform.h"

struct UIAddElementQueueSingleton
{
public:
    UIAddElementQueueSingleton() : elementPool(1024) { }

    moodycamel::ConcurrentQueue<struct UIElementData> elementPool;
};