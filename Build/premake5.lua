local ROOT = "../"

workspace      (ROOT .. "DrawKit")
architecture   "x64"
system         "macosx"
systemversion  "10.15"
configurations { "Debug", "Release" }	

project        "DrawKit"
location       (ROOT .. "DrawKit")
kind           "WindowedApp"
toolset        "clang"
language       "C++"
cppdialect     "C++17"
staticruntime  "off"
targetdir      (ROOT .. "bin/%{cfg.buildcfg}")

pchheader      "$(PROJECT_DIR)/src/DrawKit/Utilities/dk.pch"

sysincludedirs
{
	(ROOT .. "DrawKit/vendor/glfw/include"),
	(ROOT .. "DrawKit/vendor/glad/include"),
	(ROOT .. "DrawKit/vendor/glm")
}

files
{
	(ROOT .. "DrawKit/src/**.h"),
	(ROOT .. "DrawKit/src/**.hpp"),
	(ROOT .. "DrawKit/src/**.cpp"),
	(ROOT .. "DrawKit/src/**.pch"),

	(ROOT .. "DrawKit/vendor/glad/src/**.c"),
	(ROOT .. "DrawKit/vendor/glad/include/**.h")
}
libdirs
{
	(ROOT .. "DrawKit/vendor/glfw/lib-macos")
}

links
{
	"glfw3",
	"Cocoa.framework",
	"IOKit.framework",
	"OpenGL.framework"
}

filter         "system:macosx"
defines        "GL_SILENCE_DEPRECATION"

filter         "configurations:Debug"
symbols        "On"

filter         "configurations:Release"
optimize       "Speed"