# Full list of changes

## Visual

### Tracks

- [Lowered track refresh delay to 7 ms](https://github.com/somefoolouthere/audacity/blob/master/src/TrackPanel.h#L57)
  - Note: Requires playback at a high sample rate to work reliably.
  - Warning: Will cause freezes when spectrogram view is used while moving the mouse to different panels during playback.

## Tools

### Zoom

- [Samples zoom preset is changed to 1/144th of a second.](https://github.com/somefoolouthere/audacity/blob/master/src/menus/ViewMenus.cpp#104)

## Effects

### Truncate Silence

- [Adjusted minimum and maximum thresholds to -145 dB to -6 dB](https://github.com/somefoolouthere/audacity/blob/master/src/effects/TruncSilence.h#124)
