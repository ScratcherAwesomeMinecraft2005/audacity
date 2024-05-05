#include "projectuiactions.h"

#include "types/translatablestring.h"
#include "context/shortcutcontext.h"

using namespace muse;
using namespace muse::ui;
using namespace au::project;

const UiActionList ProjectUiActions::m_actions = {
    UiAction("file-open",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "&Open…"),
             TranslatableString("action", "Open…"),
             IconCode::Code::OPEN_FILE
             ),
    UiAction("file-new",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "&New…"),
             TranslatableString("action", "New…"),
             IconCode::Code::NEW_FILE
             ),
    UiAction("file-close",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "&Close"),
             TranslatableString("action", "Close")
             ),
    UiAction("file-save",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "&Save"),
             TranslatableString("action", "Save"),
             IconCode::Code::SAVE
             ),
    UiAction("file-save-as",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Save &as…"),
             TranslatableString("action", "Save as…")
             ),
    UiAction("file-save-a-copy",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Save a cop&y…"),
             TranslatableString("action", "Save a copy…")
             ),
    UiAction("file-save-selection",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Save se&lection…"),
             TranslatableString("action", "Save selection…")
             ),
    UiAction("file-save-to-cloud",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Save to clo&ud…"),
             TranslatableString("action", "Save to cloud…"),
             IconCode::Code::CLOUD_FILE
             ),
    UiAction("file-publish",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Pu&blish to MuseScore.com…"),
             TranslatableString("action", "Publish to MuseScore.com…"),
             IconCode::Code::CLOUD_FILE
             ),
    UiAction("file-share-audio",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Share on Audio.com…"),
             TranslatableString("action", "Share on Audio.com…"),
             IconCode::Code::SHARE_AUDIO
             ),
    UiAction("file-export",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "&Export…"),
             TranslatableString("action", "Export…"),
             IconCode::Code::SHARE_FILE
             ),
    UiAction("file-import-pdf",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Import P&DF…"),
             TranslatableString("action", "Import PDF…"),
             IconCode::Code::IMPORT
             ),
    UiAction("project-properties",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "Project propert&ies…"),
             TranslatableString("action", "Project properties…")
             ),
    UiAction("print",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "&Print…"),
             TranslatableString("action", "Print…"),
             IconCode::Code::PRINT
             ),
    UiAction("clear-recent",
             au::context::UiCtxAny,
             au::context::CTX_ANY,
             TranslatableString("action", "&Clear recent files"),
             TranslatableString("action", "Clear recent files")
             )
};

ProjectUiActions::ProjectUiActions(std::shared_ptr<ProjectActionsController> controller)
    : m_controller(controller)
{
}

const UiActionList& ProjectUiActions::actionsList() const
{
    return m_actions;
}

bool ProjectUiActions::actionEnabled(const UiAction& act) const
{
    if (!m_controller->canReceiveAction(act.code)) {
        return false;
    }

    return true;
}

bool ProjectUiActions::actionChecked(const UiAction&) const
{
    return false;
}

muse::async::Channel<muse::actions::ActionCodeList> ProjectUiActions::actionEnabledChanged() const
{
    return m_actionEnabledChanged;
}

muse::async::Channel<muse::actions::ActionCodeList> ProjectUiActions::actionCheckedChanged() const
{
    return m_actionCheckedChanged;
}
