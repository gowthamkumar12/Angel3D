# Angel3D

## Table of Contents

 1. [**Description**](#description)
 2. [**Key features**](#key-features)
 3. [**Libraries and Frameworks**](#libraries-and-frameworks)
 4. [**Installation**](#installation)
 5. [**Acknowledgments**](#acknowledgments)
 6. [**License**](#license)

## NOTE:
### This is still in development phase, currently supports windows only.

## Description
Angel3D is an open-source game engine inspired by the Hazel Game Engine series by The Cherno. It is a personal learning project designed to deepen the understanding of game engine development while building a fully functional engine from the ground up.

The engine serves as a platform to explore and implement core concepts of game development, including rendering, physics, asset management, input systems, and more. By following Hazel's architectural patterns and design philosophies, Angel3D seeks to provide an accessible and modular framework for experimenting with game creation.

This project is a stepping stone for mastering the intricate details of engine development and showcases the journey of creating a custom game engine from scratch.

## Key features
1. **Cross-Platform Compatibility**: Angel3D is aimed to run seamlessly on multiple platforms, making it versatile for developers targeting diverse environments. Platforms like Windows, Linux and MacOS will be supported.
2. **Multiple Graphics API Support**: The engine is aimed to support multiple graphics specifications, providing flexibility to work with modern APIs like Vulkan, OpenGL, or DirectX based on the target platform.

## Libraries and Frameworks
1. [spdlog](https://github.com/gabime/spdlog)
2. [GLFW](https://github.com/glfw/glfw)
3. [GLM](https://github.com/g-truc/glm)
4. [GLAD](https://glad.dav1d.de/)
5. [ImGui](https://github.com/ocornut/imgui)
6. [Colorama](https://github.com/tartley/colorama)

## Installation
### Pre-requisites:
1. CMake
2. Python
3. Git
4. Doxygen

### Clone the repo:
1. Create a new workspace folder in your local machine
2. Open a new command prompt in that folder and clone the repo using below command.
   * `git clone --recurse-submodules -j8 https://github.com/gowthamkumar12/Angel3D.git`
3. Once the repo is cloned change the directory to the repository.
4. Build the repo for debug using the below command.
   * `build -mbuild DEBUG`
   * A new build folder with name `_out` will be generated.

### Some commands to know
1. We have total of 3 build configurations(i.e., **DEBUG**, **RELEASE** and **DIST**).
    * For debug build   `build.cmd -mbuild DEBUG`
    * For release build `build.cmd -mbuild RELEASE`
    * For dist build    `build.cmd -mbuild DIST`
2. To clean the build.
    * `build.cmd -mclean`
3. To generate the doxygen documentation.
    * `build.cmd -doc`
    * The generated doxygen will be under the build folder (i.e., `_out/doxygen`)

## Acknowledgments
1. Special thanks to [The Cherno](https://www.youtube.com/@TheCherno) for inspiring this project through his game engine development series. Check out his [Hazel Game Engine playlist](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) for valuable insights on building game engines

## License
[**Apache-2.0 license**](LICENSE)
