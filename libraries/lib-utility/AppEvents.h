/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * SPDX-FileName: AppEvents.h
 * SPDX-FileContributor: Dmitry Vedenko
 */

#pragma once

#include <functional>

namespace AppEvents
{
/*! Register callback to be called when application is initialized.
 *  If application is already initialized, callback will be called immediately.
 *  @param callback Callback to be called when application is initialized.
 *  @pre `!!calback`
 */
UTILITY_API void OnAppInitialized(std::function<void()> callback);

/*! Base class for application events providers.
 *  This class has no virtual methods and should not be publicly derived from.
 *  Derived classes should use the provided interface to fire events.
 *  It is safe to have multiple instances of derived classes, but it does not
 *  make much sense.
 */
class UTILITY_API ProviderBase /* not final */
{
protected:
   virtual ~ProviderBase() = default;

   void HandleAppInitialized();
};

} // namespace AppEvents
