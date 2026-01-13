workspace "Tic-Tac-Toe"
	language "C++"
	cppdialect "C++23"

	configurations {
		"Debug",
		"Release"
	}
	platforms {
		"x32",
		"x64"
	}

	startproject "GameApp"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "modules/EngineCore/EngineCore-premake5.lua"
include "modules/Renderer/Renderer-premake5.lua"
include "modules/GameApp/GameApp-premake5.lua"