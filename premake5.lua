workspace "LexBrush"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "LexBrush/vendor/GLFW/include"
IncludeDir["Glad"] = "LexBrush/vendor/Glad/include"
IncludeDir["glm"] = "LexBrush/vendor/glm"
IncludeDir["stb_image"] = "LexBrush/vendor/stb_image"


include "LexBrush/vendor/GLFW"
include "LexBrush/vendor/Glad"

project "LexBrush"
	location "LexBrush"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lbpch.h"
	pchsource "LexBrush/src/lbpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"opengl32.lib"
	}
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "LB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LB_RELEASE"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"LexBrush/src",
		"LexBrush/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"LexBrush"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "LB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LB_RELEASE"
		runtime "Release"
		optimize "on"

