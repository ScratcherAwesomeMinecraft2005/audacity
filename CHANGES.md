# Full list of changes

## Visual

- [Lowered track refresh delay to 7 ms](https://github.com/ScratcherAwesomeMinecraft2005/audacity/blob/master/src/TrackPanel.h#L57)
  - Note: Requires playback at a high sample rate to work reliably.

## Effects

### Compressor

- [Lowered minimum threshold to -145 dB](https://github.com/ScratcherAwesomeMinecraft2005/audacity/blob/master/src/effects/Compressor.h#L136)
- [Increased maximum ratio to 100:1](https://github.com/ScratcherAwesomeMinecraft2005/audacity/blob/master/src/effects/Compressor.h#L140)
- [Lowered minimum attack time to 0 seconds](https://github.com/ScratcherAwesomeMinecraft2005/audacity/blob/master/src/effects/Compressor.h#L142)
- [Lowered minimum release time to 1 millisecond](https://github.com/ScratcherAwesomeMinecraft2005/audacity/blob/master/src/effects/Compressor.h#L144)
