# Full list of changes

## Visual

### Tracks

- [Lowered track refresh delay to 7 ms](https://github.com/somefoolouthere/audacity/blob/master/src/TrackPanel.h#L55)
  - Note: Requires playback at a high sample rate to work reliably.
  - Warning: Short freezes may occur when moving the mouse to different panels during playback, especially in spectrogram view.

## Tools

### Zoom

- Added 1/144th Second zoom preset.

## Effects

### Truncate Silence

- [Adjusted minimum and maximum thresholds to -145 dB to -6 dB](https://github.com/somefoolouthere/audacity/blob/master/src/effects/TruncSilence.h#126)
