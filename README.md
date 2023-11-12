# Tank Mania!

A Simple 2D Top Down Tank game for 2 players. Made with C++ using the SFML Library, and a simple custom made collision engine.

Players compete for dominance in an all out tank battle! Either capture the opponent's flag, or destroy the opponent.

![Tank Mania Screenshot](https://github.com/Caruychen/tankMania/blob/master/img/tankMania.png)

## How to Play

Basic actions are
* Move Forward
* Move Backward
* Turn Left
* Turn Right
* Shoot!

Below are the keybindings per player:

### Player 1

* Move Forward - W
* Move Backward - S
* Turn Left - A
* Turn Right - D
* Shoot! - Q

### Player 2

* Move Forward - Up key
* Move Backward - Down key
* Turn Left - Left key
* Turn Right - Right key
* Shoot! - Space

## How to Run

You will need to generate the binary for your system first before running the game.

1. Configure and build.
    Using CMake from the command line is straightforward as well.

    For a single-configuration generator (typically the case on Linux and macOS):
    ```
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ```

    For a multi-configuration generator (typically the case on Windows):
    ```
    cmake -S . -B build
    cmake --build build --config Release
    ```

    This should generate a binary file in `./build/bin/tankMania`
1. Enjoy!
