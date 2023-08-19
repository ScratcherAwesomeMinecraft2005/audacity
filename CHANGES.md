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

### Compressor

- [Lowered minimum threshold to -145 dB](https://github.com/somefoolouthere/audacity/blob/master/src/effects/Compressor.h#L136)
- [Increased maximum ratio to 100:1](https://github.com/somefoolouthere/audacity/blob/master/src/effects/Compressor.h#L140)
- [Lowered minimum attack time to 0 seconds](https://github.com/somefoolouthere/audacity/blob/master/src/effects/Compressor.h#L142)
- [Lowered minimum release time to 0 seconds and made it increment by 1/20s](https://github.com/somefoolouthere/audacity/blob/master/src/effects/Compressor.h#L144)

### Truncate Silence

- [Adjusted minimum and maximum thresholds to -145 dB to -6 dB](https://github.com/somefoolouthere/audacity/blob/master/src/effects/TruncSilence.h#124)
