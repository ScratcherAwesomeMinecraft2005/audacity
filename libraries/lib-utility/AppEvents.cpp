/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * SPDX-FileName: AppEvents.cpp
 * SPDX-FileContributor: Dmitry Vedenko
 */

#include "AppEvents.h"

#include <cassert>
#include <vector>

namespace AppEvents
{
namespace
{

struct EventHandlers final
{
   std::vector<std::function<void()>> appInitialized;
   bool AppInitializedCalled {};
};

EventHandlers& GetEventHandlers()
{
   static EventHandlers handlers;
   return handlers;
}

} // namespace

void OnAppInitialized(std::function<void()> callback)
{
   assert(callback);

   if (!callback)
      return;

   auto& handlers = GetEventHandlers();

   if (handlers.AppInitializedCalled)
      callback();
   else
      handlers.appInitialized.push_back(std::move(callback));
}

void ProviderBase::HandleAppInitialized()
{
   auto& handlers = GetEventHandlers();

   handlers.AppInitializedCalled = true;

   std::vector<std::function<void()>> callbacks;
   std::swap(callbacks, handlers.appInitialized);

   for (auto& callback : handlers.appInitialized)
      callback();
}

} // namespace AppEvents
