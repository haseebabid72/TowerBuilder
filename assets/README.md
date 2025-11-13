# Assets Directory

This directory is for game assets like sprites, sounds, and fonts.

## Directory Structure

```
assets/
├── sprites/     # Block textures and images
├── sounds/      # Sound effects (drop, perfect, game over)
└── fonts/       # Custom fonts for UI
```

## Adding Assets

### Sprites
Place any PNG or JPG images in the `sprites/` directory. You can use textures from the [original tower_game repository](https://github.com/iamkun/tower_game) or create your own.

### Sounds
Add WAV or OGG sound files to the `sounds/` directory. Suggested sounds:
- `drop.wav` - When block lands
- `perfect.wav` - Perfect alignment
- `gameover.wav` - Game over sound
- `music.ogg` - Background music (optional)

### Fonts
Add TTF font files to the `fonts/` directory for custom text rendering.

## Using Assets in Code

### Loading Textures
```cpp
Texture2D blockTexture = LoadTexture("assets/sprites/block.png");
```

### Loading Sounds
```cpp
Sound dropSound = LoadSound("assets/sounds/drop.wav");
PlaySound(dropSound);
```

### Loading Fonts
```cpp
Font gameFont = LoadFont("assets/fonts/game_font.ttf");
```

## Current Status

The game currently works without any assets, using raylib's built-in primitives for rendering. Assets are optional but can enhance the visual and audio experience!

## Credits

If you use assets from other sources, please credit them here:
- [Original tower_game by iamkun](https://github.com/iamkun/tower_game)
