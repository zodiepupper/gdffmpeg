#!/usr/bin/env python
import os
import sys
import subprocess

from methods import print_error


libname = "gdffmpeg"
projectdir = "demo"

# TODO later on figure out how we can have scons run
# the build for ffmpeg automatically to simplify the
# build process
#subprocess.Popen("src/ffmpeg/configure", shell=True)

localEnv = Environment(tools=["default"], PLATFORM="")

# Build profiles can be used to decrease compile times.
# You can either specify "disabled_classes", OR
# explicitly specify "enabled_classes" which disables all other classes.
# Modify the example file as needed and uncomment the line below or
# manually specify the build_profile parameter when running SCons.

localEnv["build_profile"] = "build_profile.json"

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print_error("""godot-cpp or ffmpeg is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive""")
    sys.exit(1)

env.Command # use env.Command https://www.scons.org/doc/2.0.1/HTML/scons-user.html#chap-builders-commands

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs})

# setup paths for source files and the cpp root path
env.Append(CPPPATH=["src/",
                    "src/ffmpeg/"])

sources = Glob("src/*.cpp")

# setup paths for where to get the static library files from ffmpeg
env.Append(LIBPATH=["src/ffmpeg/libavutil/",
                    "src/ffmpeg/libavdevice/",
                    "src/ffmpeg/libavcodec/",
                    "src/ffmpeg/libavformat/",
                    "src/ffmpeg/libavfilter",
                    "src/ffmpeg/libswresample/",
                    "src/ffmpeg/libswscale/"])

# tell scons what libraries we want it to statically link
env.Append(LIBS=["libavcodec",
                 "libavdevice",
                 "libavfilter",
                 "libavformat",
                 "libavutil",
                 "libswresample",
                 "libswscale"])

# these are linker flags (also referred to as LDFLAGS in many cases online)
env.Append(LINKFLAGS=["-Wl,-Bsymbolic"])

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# .dev doesn't inhibit compatibility, so we don't need to key it.
# .universal just means "compatible with all relevant arches" so we don't need to key it.
suffix = env['suffix'].replace(".dev", "").replace(".universal", "")

lib_filename = "{}{}{}{}".format(env.subst('$SHLIBPREFIX'), libname, suffix, env.subst('$SHLIBSUFFIX'))

library = env.SharedLibrary(
    "bin/{}/{}".format(env['platform'], lib_filename),
    source=sources,
)

copy = env.Install("{}/bin/{}/".format(projectdir, env["platform"]), library)

default_args = [library, copy]
Default(*default_args)
