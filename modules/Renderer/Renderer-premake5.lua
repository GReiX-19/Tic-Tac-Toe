project "Renderer"
	kind "StaticLib"

	files {
		"source/**.cpp",
		"include/**.h"
	}

	includedirs {
		"include",
		"../EngineCore/include",
		"%{wks.location}/SFML/include"
	}
	
	links {
		"EngineCore"
	}

	libdirs {
		"%{wks.location}/SFML/lib"
	}

	targetdir ("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. OutputDir .. "/%{prj.name}")

	filter "configurations:Debug"
		defines {
			"DEBUG"
		}
		runtime "Debug"
		symbols "On"
		links {
			"sfml-system-d",
			"sfml-window-d",
			"sfml-graphics-d"
		}

	filter "configurations:Release"
		defines {
			"NDEBUG"
		}
		runtime "Release"
		optimize "On"
		symbols "Off"
		links {
			"sfml-system",
			"sfml-window",
			"sfml-graphics"
		}

	filter "platforms:x32"
		system "Windows"
		architecture "x86"

	filter "platforms:x64"
		system "Windows"
		architecture "x86_64"