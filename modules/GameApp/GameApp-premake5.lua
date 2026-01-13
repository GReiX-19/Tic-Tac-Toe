project "GameApp"
	kind "ConsoleApp"

	files {
		"source/**.cpp",
		"include/**.h"
	}

	includedirs {
		"include",
		"../EngineCore/include",
		"../Renderer/include"
	}

	links {
		"EngineCore",
		"Renderer"
	}

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. OutputDir .. "/%{prj.name}")

	postbuildcommands {
		"{COPYFILE} %[%{wks.location}/SFML/dll/*.dll] %[%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}]"
	}

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