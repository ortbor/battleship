# **Battlesh!p Game**

## About The Project

This is a battlesh!p game developed as an university project.

## Getting Started
How to install?

### Prerequisites
You need an **SFML library** and **cmake** to build project.
* SFML, required version >= 2.5.1
  ```sh
  sudo apt install libsfml-dev
  ```
* cmake, required version >= 3.2.3
  ```sh
  sudo apt install cmake
  ```

### Installation
_Now you can start to build and install game_

1. Clone the repo and go to project folder
  ```sh
  git clone https://github.com/NTheme/File-Manager.git
  cd File-Manager
  ```

2. Make a build directory and go inside
  ```sh
  mkdir build
  cd build
  ```

3. Now you can start to build and install game
  ```sh
  cmake -DCMAKE_BUILD_TYPE=Release ..
  cmake --build . --config Release -- -j 16
  sudo cmake --install . 
  ```

### Usage
  Just start the game using the following command:
  ```sh
  battlesh1p
  ```

----------------------------

### ***By NThemeDEV && ortbor***
