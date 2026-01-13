project "EngineCore"
	kind "StaticLib"

	files {
		"source/**.cpp",
		"include/**.h"
	}

	includedirs {
		"include"
	}

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. OutputDir .. "/%{prj.name}")

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "On"
		symbols "Off"

	filter "platforms:x32"
		system "Windows"
		architecture "x86"

	filter "platforms:x64"
		system "Windows"
		architecture "x86_64"