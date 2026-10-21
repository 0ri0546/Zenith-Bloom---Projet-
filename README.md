# Zenith Bloom

<p align="center">
  <strong>A 2D action-platformer built with C++ and SFML.</strong>
  <br />
  Explore levels, fight enemies, manage your resources, and survive through changing day and night conditions.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white" alt="C++17" />
  <img src="https://img.shields.io/badge/SFML-2.6.2-8CC445" alt="SFML 2.6.2" />
  <img src="https://img.shields.io/badge/Platform-Windows-0078D6?logo=windows&logoColor=white" alt="Windows" />
  <img src="https://img.shields.io/badge/IDE-Visual%20Studio-5C2D91?logo=visualstudio&logoColor=white" alt="Visual Studio" />
  <img src="https://img.shields.io/badge/Genre-Action%20Platformer-7A3DB8" alt="Action platformer" />
</p>

## About the project

**Zenith Bloom** is a 2D action-platformer developed in C++ with the SFML multimedia library. The project includes a playable character, several enemy types, tile-based levels, projectiles, animations, a HUD, and a collection of menus.

The game also features a day/night cycle, collectible health and energy capsules, and a level editor.

## Features

- **Player mechanics:** movement, jumping, ranged attacks, water projectiles, health and energy management.
- **Enemies and combat:** multiple enemy types, projectiles, damage handling, and state-based enemy behaviour.
- **Levels and world:** tile-based maps, backgrounds, decorations, platforms, and repairable objects.
- **Day/night cycle:** the game switches between day and night.
- **HUD:** health, energy, overheating, and progress indicators.
- **Menus:** title screen, main menu, pause menu, options, video, sound, controls, level selection, and game over.
- **Level editor:** in-game tools for editing map tiles.
- **Audio and assets:** dedicated asset-loading, animation, and audio systems.

## Built with

| Technology | Purpose |
| --- | --- |
| [C++17](https://en.cppreference.com/w/cpp/17.html) | Game logic and systems |
| [SFML 2.6.2](https://www.sfml-dev.org/) | Graphics, window, input, audio, and timing |
| [Visual Studio 2022](https://visualstudio.microsoft.com/) | Project setup and compilation |
| MSBuild | Windows C++ build system |

## Project structure

```text
Zenith-Bloom---Projet-/
├── assets/
│   ├── ennemies/       # Enemy sprites and animations
│   ├── fonts/          # Fonts used in the game
│   └── maps/           # Map backgrounds, tiles, and level data
├── src/
│   ├── core/           # Main game loop and state management
│   ├── entities/       # Player, enemies, projectiles, and pickups
│   ├── hud/menu/       # Menus and interface screens
│   ├── map/            # Maps, tiles, platforms, and decorations
│   └── systems/        # Assets, animation, audio, and supporting systems
├── Zenith Bloom.sln
└── README.md
```

## Getting started

### Requirements

- Windows
- Visual Studio 2022 with the **Desktop development with C++** workload
- SFML **2.6.2**
- A C++17-compatible compiler

### Setup

1. Clone the repository:

   ```bash
   git clone https://github.com/0ri0546/Zenith-Bloom---Projet-.git
   cd Zenith-Bloom---Projet-
   ```

2. Install or extract SFML 2.6.2 for your Visual Studio toolchain and architecture.

3. Open `Zenith Bloom.sln` in Visual Studio.

4. Check the project's SFML include directories, library directories, and linker dependencies. The current project configuration contains machine-specific SFML paths, so update them to match your installation.

5. Select the **x64** platform and either **Debug** or **Release** configuration, then build the solution.

6. Ensure the required SFML DLLs and game assets are available from the application's working directory before running the executable.

> **Note:** The Visual Studio project currently references local SFML folders. You may need to update these paths before the project builds successfully on your machine.

## Controls

The game supports keyboard and gamepad input. Check the in-game controls menu for the complete gameplay bindings.

- **Escape:** pause during gameplay or return from supported menus.
- **Gamepad Start:** pause during gameplay.

## Development

The codebase is split into modules for game state, entities, maps, menus, and reusable systems. This structure separates gameplay logic from presentation and supporting systems.

## Tags

`cpp` `cpp17` `sfml` `sfml-2` `2d-game` `platformer` `action-game` `game-development` `visual-studio` `windows` `tilemap` `game-ai`

## Project status

This is a development project. Features, level content, and implementation details may change.

---

<p align="center">
  Developed as a game development project.
</p>
