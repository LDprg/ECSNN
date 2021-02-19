workspace "ECSNN"
	architecture "x64"
	startproject "Sandbox"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ECSNN"
	location "ECSNN"
	kind "StaticLib"
	language "C++"	

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/entt/include",
	}

	filter "system:windows"
		cppdialect "C++latest"
		staticruntime "on"
		systemversion "latest"

		--postbuildcommands{
		--	("{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/Sandbox")
		--}

	filter "configurations:Debug"
		runtime "Debug"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		buildoptions "/MT"
		optimize "on"
	
project "Sandbox"
	location "Sandbox"

	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{wks.location}/ECSNN/src",
		"%{wks.location}/ECSNN/vendor/entt/include"
	}

	links{
		"ECSNN"
	}

	filter "system:windows"
		cppdialect "C++latest"
		staticruntime "on"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		buildoptions "/MT"
		optimize "on"