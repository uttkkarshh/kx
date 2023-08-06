workspace "kx"
	architecture "x64"
	startproject "sand"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "kx/vendor/GLFW/include"
IncludeDir["Glad"] = "kx/vendor/Glad/include"
IncludeDir["ImGui"] = "kx/vendor/imgui"
IncludeDir["glm"] = "kx/vendor/glm"
IncludeDir["stb_image"] = "kx/vendor/stb_image"

include "kx/vendor/GLFW"
include "kx/vendor/Glad"
include "kx/vendor/imgui"

project "kx"
	location "kx"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	

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
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"kx_PLATFORM_WINDOW",
			"kx_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
			
		}

	filter "configurations:Debug"
		defines "kx_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "kx_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "kx_DIST"
		runtime "Release"
		optimize "on"

project "sand"
	location "sand"
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
		"kx/vendor/spdlog/include",
		"kx/src",
		"kx/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"kx"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"kx_PLATFORM_WINDOW"
		}

	filter "configurations:Debug"
		defines "kx_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "kx_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "kx_DIST"
		runtime "Release"
		optimize "on"