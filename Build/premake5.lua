local ROOTDIR = "/Users/davidspry/Library/Mobile Documents/com~apple~CloudDocs/Development/Creative Frameworks/DrawKit/"
local PROJDIR = ROOTDIR .. "DrawKit/"
local PROJECT = "DrawKit"

workspace      (PROJECT)
location       (PROJDIR)
system         "macosx"
systemversion  "10.15"
architecture   "x64"

configurations { "Debug", "Release" }

project        (PROJECT)
location       (PROJDIR)
basedir        (ROOTDIR)
targetdir      (ROOTDIR .. "bin/%{cfg.buildcfg}")
kind           "WindowedApp"
staticruntime  "off"
toolset        "clang"
language       "C++"
cppdialect     "C++17"

pchheader      (ROOTDIR .. "DrawKit/src/DrawKit/Utilities/dk.pch")

sysincludedirs
{
	(ROOTDIR .. "DrawKit/vendor/libsoundio/include"),
	(ROOTDIR .. "DrawKit/vendor/glfw/include"),
	(ROOTDIR .. "DrawKit/vendor/glad/include"),
	(ROOTDIR .. "DrawKit/vendor/glm")
}

files
{
	(ROOTDIR .. "DrawKit/src/**.h"),
	(ROOTDIR .. "DrawKit/src/**.hpp"),
	(ROOTDIR .. "DrawKit/src/**.cpp"),
	(ROOTDIR .. "DrawKit/src/**.pch"),

	(ROOTDIR .. "DrawKit/vendor/glad/src/**.c"),
	(ROOTDIR .. "DrawKit/vendor/glad/include/**.h")
}
libdirs
{
	(ROOTDIR .. "DrawKit/vendor/libsoundio/lib-macos"),
	(ROOTDIR .. "DrawKit/vendor/glfw/lib-macos")
}

links
{
	"glfw3",
	"soundio",
	"Cocoa.framework",
	"IOKit.framework",
	"OpenGL.framework",
	"CoreAudio.framework",
	"AudioToolbox.framework"
}

filter         "system:macosx"
defines        "GL_SILENCE_DEPRECATION"

filter         "configurations:Debug"
symbols        "On"

filter         "configurations:Release"
optimize       "Speed"