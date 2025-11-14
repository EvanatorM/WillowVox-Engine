# WillowVox Engine

A very modular game engine originally intended for voxel world games.

## Building

<details>
<summary>Installing dependencies on Debian-based distros</summary>
<br>

Run this command to get the dependencies for building GLFW:

```sh
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev cmake
```

</details>

<details>
<summary>Installing dependencies on Windows</summary>
<br>

You only need to have CMake installed on your system.

</details>

### Building with CMake

In the project root directory:
Create CMake files:

```sh
mkdir -p build
cd build
cmake ..
```

After that you can build the project using:

```sh
cmake --build .
```

Run the build command in the project root directory.

The final executable can be found at `(project root)/build/bin/(build type)`

#### Note for building with CMake

If you're running from a command line, make sure to run
the executable in the same directory as it is located
to ensure all resources are loaded properly.

### Using this template
To use this template, go into CMakeLists.txt and find and replace all instances of 'MyApp' with your application name.

You should also replace the 'MyProject' namespace name and the 'MyApp' class name in main.cpp.

To change the name of the window, you can change the 'appWindowName' variable near the top of main.cpp.

You must also create a folder in the root directory of the project called 'assets' for the project to build.

## Contributing

This project is split into different repositories, so this applies to any of those. If you would like to contribute to WillowVox Engine, you can do so in a couple of ways:

1. If you notice any small bugs or optimizations that can be made, you can do that.
2. If you want to add new features, you can look at the Projects tab of this repository or the other modules' repositories. In there are projects for upcoming releases. In the projects, there is a Status Board tab. You can add anything in the ready status. You can also work on tasks in the in-progress and in-review statuses.
3. If you have ideas or thoughts about the engine, you can check out the Discussions tab of the repository or the [Discord server](https://discord.gg/ZZTUgsmy75).
4. If you want to do something that I haven't approved, you can make your own module for the engine. I don't have any official guides for that yet, but you can follow the structure of some of the existing modules for that.

I will flesh out the contributing guidelines soon. I may not accept your changes if they go against the vision of the engine, but I will always discuss what changes I don't want to commit and why, and we can work together to make the best changes possible for the engine.
