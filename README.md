# Wave Survival Game

A 2D top-down survival game built with C++ and SFML where you fight waves of enemies in a prison environment.

## 🎮 Game Features

- **Wave-based Combat**: Survive increasingly difficult waves of enemies
- **Dynamic Gameplay**: Player speed and damage increase with each wave
- **Tile-based Map**: Navigate through a prison environment with collision detection
- **Sound Effects**: Immersive audio for attacks, movement, and impacts
- **Menu System**: Intro menu and game over screen with statistics
- **Pause Functionality**: Pause/resume gameplay at any time

## 🕹️ Controls

- **WASD**: Move player
- **Mouse**: Aim weapon
- **Left Click**: Shoot arrows
- **ESC**: Pause/Unpause game

## 📋 Requirements

### Prerequisites
- C++20 or later
- Visual Studio 2022 (or compatible IDE)
- SFML 2.6.0

### Dependencies
- SFML Graphics
- SFML Audio
- SFML System
- SFML Window

## 🔧 Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/WaveSurvivalGame.git
cd WaveSurvivalGame
```

### 2. Install SFML
Download SFML 2.6.0 from [SFML's official website](https://www.sfml-dev.org/download.php)

### 3. Configure Project
Update the SFML paths in the project properties:
- Include directories: `C:\path\to\SFML-2.6.0\include`
- Library directories: `C:\path\to\SFML-2.6.0\lib`

### 4. Build and Run
Open `WaveSurvivalGame.vcxproj` in Visual Studio and build the solution.

## 📁 Project Structure

```
WaveSurvivalGame/
├── Assets/
│   ├── Player/Texture/          # Player sprites
│   ├── GunAssets/PNG/           # Weapon and projectile sprites
│   ├── World/Prison/            # Tileset and map assets
│   ├── Sounds/                  # Sound effects
│   ├── GameMusic/               # Background music
│   ├── Fonts/                   # Game fonts
│   └── UI/                      # UI elements
├── levels/                      # CSV map files
├── Source Files/
│   ├── main.cpp                 # Game entry point
│   ├── Player.cpp/h             # Player logic
│   ├── Enemy.cpp/h              # Enemy AI
│   ├── WaveManager.cpp/h        # Wave spawning system
│   ├── Collision.cpp/h          # Collision detection
│   ├── Sound.cpp/h              # Audio system
│   ├── Menu.cpp/h               # Menu screens
│   ├── TileMap.cpp/h            # Tile rendering
│   └── ...                      # Additional components
└── README.md
```

## 🎯 Game Mechanics

### Player
- Health: 100 HP
- Speed increases with each wave
- Arrow damage increases with each wave
- Takes damage when hit by enemies

### Enemies
- Follow player using pathfinding
- Attack on contact
- Health bar displayed above sprite
- Animated movement and idle states

### Wave System
- Wave 1: 2 enemies
- Wave 2: 16 enemies (two spawn groups)
- Wave 3: 4 enemies
- Wave 4: 6 enemies
- Wave 5: 7 enemies
- Wave 6: 3 fast enemies
- 3-second delay between waves

## 🎨 Assets Required

Ensure you have the following assets in the `Assets` folder:
- Player textures: `idle.png`, `walk.png`
- Enemy textures: `Orc_idle.png`, `Orc_walk.png`
- Weapon assets: `arrow.png`, `assaultrifle.png`
- Tileset: `tilesheet.png`
- Sounds: `arrow_shoot.ogg`, `footsteps.ogg`, `player_hurt.ogg`, etc.
- Fonts: `arial.ttf`, `OldLondon.ttf`
- Music: `gameloop.ogg`

## 🐛 Known Issues

- Enemy health bar color logic has minor conditional issues
- Some tile collision IDs are hardcoded

## 🚀 Future Enhancements

- [ ] Add more enemy types
- [ ] Implement power-ups and upgrades
- [ ] Add difficulty settings
- [ ] Create more maps
- [ ] Add boss battles
- [ ] Implement score multipliers

## 📝 License

This project is open source and available under the MIT License.

## 👥 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📧 Contact

For questions or feedback, please open an issue on GitHub.

## 🙏 Acknowledgments

- SFML development team for the excellent multimedia library
- Asset creators (please credit your asset sources here)

---

**Enjoy the game and good luck surviving the waves!** 🎮
