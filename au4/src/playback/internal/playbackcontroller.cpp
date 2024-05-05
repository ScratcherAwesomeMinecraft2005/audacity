/*
* Audacity: A Digital Audio Editor
*/
#include "playbackcontroller.h"

#include "audiotypes.h"

using namespace muse;
using namespace au::audio;
using namespace au::playback;
using namespace muse::async;
using namespace muse::actions;

static const ActionCode PLAY_CODE("play");
static const ActionCode STOP_CODE("stop");
static const ActionCode REWIND_CODE("rewind");
static const ActionCode LOOP_CODE("loop");
static const ActionCode LOOP_IN_CODE("loop-in");
static const ActionCode LOOP_OUT_CODE("loop-out");
static const ActionCode PAN_CODE("pan");
static const ActionCode REPEAT_CODE("repeat");

static const QTime ZERO_TIME(0, 0, 0, 0);

inline float secondsFromMilliseconds(msecs_t milliseconds)
{
    return milliseconds / 1000.f;
}

void PlaybackController::init()
{
    dispatcher()->reg(this, PLAY_CODE, this, &PlaybackController::togglePlay);
    dispatcher()->reg(this, STOP_CODE, this, &PlaybackController::pause);
    dispatcher()->reg(this, REWIND_CODE, this, &PlaybackController::rewind);
    dispatcher()->reg(this, LOOP_CODE, this, &PlaybackController::toggleLoopPlayback);
    // dispatcher()->reg(this, LOOP_IN_CODE, [this]() { addLoopBoundary(LoopBoundaryType::LoopIn); });
    // dispatcher()->reg(this, LOOP_OUT_CODE, [this]() { addLoopBoundary(LoopBoundaryType::LoopOut); });
    dispatcher()->reg(this, REPEAT_CODE, this, &PlaybackController::togglePlayRepeats);
    dispatcher()->reg(this, PAN_CODE, this, &PlaybackController::toggleAutomaticallyPan);

    globalContext()->currentProcessingProjectChanged().onNotify(this, [this]() {
        onProjectChanged();
    });

    m_playbackPositionChanged.onNotify(this, []() {
        // msecs_t endMsecs = playbackEndMsecs();
        // const LoopBoundaries& loop = playback()->loopBoundaries();
        // if (m_currentPlaybackTimeMsecs == endMsecs && m_currentPlaybackTimeMsecs != loop.loopOutTick) {
        //     stop();
        // }
    });
}

bool PlaybackController::isPlayAllowed() const
{
    return isLoaded();
}

Notification PlaybackController::isPlayAllowedChanged() const
{
    return m_isPlayAllowedChanged;
}

bool PlaybackController::isPlaying() const
{
    return m_currentPlaybackStatus == PlaybackStatus::Running;
}

bool PlaybackController::isPaused() const
{
    return m_currentPlaybackStatus == PlaybackStatus::Paused;
}

bool PlaybackController::isLoaded() const
{
    return m_loadingTrackCount == 0;
}

bool PlaybackController::isLoopEnabled() const
{
    NOT_IMPLEMENTED;
    return false;
}

bool PlaybackController::loopBoundariesSet() const
{
    NOT_IMPLEMENTED;
    return false;
}

Notification PlaybackController::isPlayingChanged() const
{
    return m_isPlayingChanged;
}

void PlaybackController::seek(const audio::msecs_t msecs)
{
    IF_ASSERT_FAILED(au3Playback()) {
        return;
    }

    if (m_currentPlaybackTimeMsecs == msecs) {
        return;
    }

    au3Playback()->seek(msecs);
}

void PlaybackController::reset()
{
    stop();
}

Notification PlaybackController::playbackPositionChanged() const
{
    return m_playbackPositionChanged;
}

Channel<uint32_t> PlaybackController::midiTickPlayed() const
{
    return m_tickPlayed;
}

float PlaybackController::playbackPositionInSeconds() const
{
    return secondsFromMilliseconds(m_currentPlaybackTimeMsecs);
}

muse::async::Channel<TrackId> PlaybackController::trackAdded() const
{
    return m_trackAdded;
}

muse::async::Channel<TrackId> PlaybackController::trackRemoved() const
{
    return m_trackRemoved;
}

// ISoloMuteState::SoloMuteState PlaybackController::trackSoloMuteState(const TrackId& trackId) const
// {
// }

// void PlaybackController::setTrackSoloMuteState(const TrackId& trackId,
//                                                const ISoloMuteState::SoloMuteState& state) const
// {
// }

void PlaybackController::onProjectChanged()
{
}

void PlaybackController::togglePlay()
{
    if (!isPlayAllowed()) {
        LOGW() << "playback not allowed";
        return;
    }

    if (isPlaying()) {
        pause();
    } else if (isPaused()) {
        msecs_t endMsecs = playbackEndMsecs();

        if (m_currentPlaybackTimeMsecs == endMsecs) {
            msecs_t startMsecs = playbackStartMsecs();
            seek(startMsecs);
        }

        resume();
    } else {
        play();
    }
}

void PlaybackController::play()
{
    IF_ASSERT_FAILED(au3Playback()) {
        return;
    }

    if (isLoopEnabled()) {
        msecs_t startMsecs = playbackStartMsecs();
        seek(startMsecs);
    }

    au3Playback()->play();
    setCurrentPlaybackStatus(PlaybackStatus::Running);
}

void PlaybackController::rewind(const ActionData& args)
{
    //! NOTE: In Audacity 3 we can't rewind while playing
    stop();

    msecs_t startMsecs = playbackStartMsecs();
    msecs_t endMsecs = playbackEndMsecs();
    msecs_t newPosition = !args.empty() ? args.arg<msecs_t>(0) : 0;
    newPosition = std::clamp(newPosition, startMsecs, endMsecs);

    seek(newPosition);
}

void PlaybackController::pause()
{
    IF_ASSERT_FAILED(au3Playback()) {
        return;
    }

    au3Playback()->pause();
    setCurrentPlaybackStatus(PlaybackStatus::Paused);
}

void PlaybackController::stop()
{
    IF_ASSERT_FAILED(au3Playback()) {
        return;
    }

    au3Playback()->stop();
    setCurrentPlaybackStatus(PlaybackStatus::Stopped);
}

void PlaybackController::resume()
{
    IF_ASSERT_FAILED(au3Playback()) {
        return;
    }

    au3Playback()->resume();
    setCurrentPlaybackStatus(PlaybackStatus::Running);
}

msecs_t PlaybackController::playbackStartMsecs() const
{
    // const LoopBoundaries& loop = playback()->loopBoundaries();
    // if (loop.enabled) {
    //     return tickToMsecs(loop.loopInTick);
    // }

    return 0;
}

msecs_t PlaybackController::playbackEndMsecs() const
{
    NOT_IMPLEMENTED;
    return 0; // total time
}

void PlaybackController::setCurrentPlaybackStatus(PlaybackStatus status)
{
    if (m_currentPlaybackStatus == status) {
        return;
    }

    m_currentPlaybackStatus = status;
    m_isPlayingChanged.notify();
}

void PlaybackController::togglePlayRepeats()
{
    NOT_IMPLEMENTED;

    // configuration()->setIsPlayRepeatsEnabled(!playRepeatsEnabled);

    notifyActionCheckedChanged(REPEAT_CODE);
}

void PlaybackController::toggleAutomaticallyPan()
{
    NOT_IMPLEMENTED;

    // configuration()->setIsAutomaticallyPanEnabled(!panEnabled);

    notifyActionCheckedChanged(PAN_CODE);
}

void PlaybackController::toggleLoopPlayback()
{
    NOT_IMPLEMENTED;
}

// void PlaybackController::addLoopBoundary(LoopBoundaryType type)
// {
// }

// void PlaybackController::addLoopBoundaryToTick(LoopBoundaryType type, int tick)
// {
// }

// void PlaybackController::updateLoop()
// {
// }

// void PlaybackController::enableLoop()
// {
// }

// void PlaybackController::disableLoop()
// {
// }

void PlaybackController::notifyActionCheckedChanged(const ActionCode& actionCode)
{
    m_actionCheckedChanged.send(actionCode);
}

void PlaybackController::setCurrentPlaybackTime(msecs_t msecs)
{
    if (m_currentPlaybackTimeMsecs == msecs) {
        return;
    }

    m_currentPlaybackTimeMsecs = msecs;

    m_playbackPositionChanged.notify();
}

void PlaybackController::subscribeOnAudioParamsChanges()
{
    NOT_IMPLEMENTED;
}

void PlaybackController::initMuteStates()
{
    NOT_IMPLEMENTED;
}

void PlaybackController::updateSoloMuteStates()
{
    NOT_IMPLEMENTED;
}

bool PlaybackController::actionChecked(const ActionCode& actionCode) const
{
    QMap<std::string, bool> isChecked {
        { LOOP_CODE, isLoopEnabled() },
        // { REPEAT_CODE, configuration()->isPlayRepeatsEnabled() },
        // { PAN_CODE, configuration()->isAutomaticallyPanEnabled() },
    };

    return isChecked[actionCode];
}

Channel<ActionCode> PlaybackController::actionCheckedChanged() const
{
    return m_actionCheckedChanged;
}

QTime PlaybackController::totalPlayTime() const
{
    QTime result = ZERO_TIME;

    NOT_IMPLEMENTED;

    return result;
}

Notification PlaybackController::totalPlayTimeChanged() const
{
    return m_totalPlayTimeChanged;
}

muse::Progress PlaybackController::loadingProgress() const
{
    return m_loadingProgress;
}

bool PlaybackController::canReceiveAction(const ActionCode&) const
{
    return globalContext()->currentProject() != nullptr;
}

msecs_t PlaybackController::tickToMsecs(int tick) const
{
    NOT_IMPLEMENTED;
    UNUSED(tick);
    return 0;
}
