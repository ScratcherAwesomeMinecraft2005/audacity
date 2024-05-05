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
#include "au3wrapmodule.h"

#include <iostream>
#include <wx/log.h>

#include "libraries/lib-preferences/Prefs.h"
#include "libraries/lib-audio-io/AudioIO.h"
#include "libraries/lib-project-file-io/ProjectFileIO.h"

#include "mocks/au3settingsmock.h"

#include "internal/wxlogwrap.h"

#include "modularity/ioc.h"
#include "audacity3playback.h"

#include "log.h"

using namespace au::au3;

std::string Au3WrapModule::moduleName() const
{
    return "au3wrap";
}

void Au3WrapModule::registerExports()
{
    m_playback = std::make_shared<Audacity3Playback>();

    muse::modularity::ioc()->registerExport<IAudacity3Playback>(moduleName(), m_playback);
}

void Au3WrapModule::onInit(const muse::IApplication::RunMode&)
{
    m_wxLog = new WxLogWrap();
    wxLog::SetActiveTarget(m_wxLog);

    std::unique_ptr<Au3SettingsMock> auset = std::make_unique<Au3SettingsMock>();
    InitPreferences(std::move(auset));

    AudioIO::Init();

    bool ok = ProjectFileIO::InitializeSQL();
    if (!ok) {
        LOGE() << "failed init sql";
    }
}

void Au3WrapModule::onDeinit()
{
    wxLog::SetActiveTarget(nullptr);
    delete m_wxLog;
}
