# gdffmpeg
## use ffmpeg from within godot!

## Contents
* an example Godot project (`demo/`)
* godot-cpp as a submodule (`godot-cpp/`)
* TODO update github issues template
* GitHub CI/CD workflows to publish the library packages when creating a release (`.github/workflows/builds.yml`)

# build instructions

- make sure you got all the submodules
  - when cloning use `git clone https://github.com/zodiepupper/gdffmpeg --recurse-submodules`
  - or run `git submodule update --init --recursive` if you've already clones the repo
- move into the ffmpeg folder `cd src/ffmpeg`
- run the configuration file with:
  - `./configure --enable-pic --extra-ldexeflags=-pie`
  - this ensures that the library is built with Position Independent Code enabled and an extra link flag to help force it to behave in some edge cases
- run `make` to build the ffmpeg libraries
- move back to the root directory `cd ../..`
- run scons to build the gdextension
