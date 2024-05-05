/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef AU_CONTEXT_GLOBALCONTEXT_H
#define AU_CONTEXT_GLOBALCONTEXT_H

#include "../iglobalcontext.h"

namespace au::context {
class GlobalContext : public au::context::IGlobalContext
{
public:

    void setCurrentProject(const au::project::IAudacityProjectPtr& project) override;
    au::project::IAudacityProjectPtr currentProject() const override;
    muse::async::Notification currentProjectChanged() const override;

    au::processing::ProcessingProjectPtr currentProcessingProject() const override;
    muse::async::Notification currentProcessingProjectChanged() const override;

private:
    au::project::IAudacityProjectPtr m_currentProject;
    muse::async::Notification m_currentProjectChanged;
};
}

#endif // AU_CONTEXT_GLOBALCONTEXT_H
