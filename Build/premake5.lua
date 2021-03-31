-- Define a project name.
local PROJECT = "DrawKit"

-- Define DrawKit's root directory.
local ROOTDIR = "/Users/davidspry/Library/Mobile Documents/com~apple~CloudDocs/Development/Frameworks/DrawKit/"

-- Define the project's directory.
local PROJDIR = ROOTDIR .. "Projects/" .. PROJECT .. "/"

-- #MARK
-- =====
os.execute("mkdir -p -v \"" .. PROJDIR .. "\"src")
os.execute("cp \"" .. ROOTDIR .. "Templates/Project/main.cpp\" \"" .. PROJDIR .. "src/main.cpp\"")
os.execute("cp \"" .. ROOTDIR .. "Templates/Project/Sketch.hpp\" \"" .. PROJDIR .. "src/Sketch.hpp\"")
os.execute("cp \"" .. ROOTDIR .. "Templates/Project/Sketch.cpp\" \"" .. PROJDIR .. "src/Sketch.cpp\"")

-- WORKSPACE
-- =====================
workspace      (PROJECT)
location       (PROJDIR)
system         "macosx"
systemversion  "10.15"
architecture   "x86_64"
configurations { "Debug", "Release" }
-- =====================

-- PROJECT
-- =====================
project        (PROJECT)
location       (PROJDIR)
targetdir      (PROJDIR .. "bin/%{cfg.buildcfg}")
kind           "WindowedApp"
staticruntime  "off"
toolset        "clang"
language       "C++"
cppdialect     "C++17"
pchheader      (ROOTDIR .. "DrawKit/DrawKit/Utilities/dk.pch")
-- =====================

sysincludedirs
{
	(ROOTDIR .. "DrawKit/vendor/libsoundio/include"),
	(ROOTDIR .. "DrawKit/vendor/glfw/include"),
	(ROOTDIR .. "DrawKit/vendor/glad/include"),
	(ROOTDIR .. "DrawKit/vendor/glm"),
	(ROOTDIR .. "DrawKit/DrawKit/**")
}

files
{
	(PROJDIR .. "src/**.h"),
	(PROJDIR .. "src/**.hpp"),
	(PROJDIR .. "src/**.cpp"),
	
	(ROOTDIR .. "DrawKit/DrawKit/**.h"),
	(ROOTDIR .. "DrawKit/DrawKit/**.hpp"),
	(ROOTDIR .. "DrawKit/DrawKit/**.cpp"),
	(ROOTDIR .. "DrawKit/DrawKit/**.pch"),

	(ROOTDIR .. "DrawKit/DrawKit/**.frag"),
	(ROOTDIR .. "DrawKit/DrawKit/**.vert"),
	(ROOTDIR .. "DrawKit/DrawKit/**.geom"),
	
	(ROOTDIR .. "DrawKit/vendor/glad/src/**.c"),
	(ROOTDIR .. "DrawKit/vendor/glad/include/**.h")
}

libdirs
{
	(ROOTDIR .. "DrawKit/vendor/libsoundio/lib-macos"),
	(ROOTDIR .. "DrawKit/vendor/glfw/lib-macos-intel")
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

filter      "system:macosx"
defines     "GL_SILENCE_DEPRECATION"

filter      "files:**.frag"
buildaction "Embed"

filter      "files:**.vert" 
buildaction "Embed" 

filter      "files:**.geom" 
buildaction "Embed"

filter      "configurations:Debug"
symbols     "On"

filter      "configurations:Release"
optimize    "Speed"