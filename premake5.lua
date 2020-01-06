workspace "CoffeeEngine"
	defines "_CRT_SECURE_NO_WARNINGS"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputDirectory = "%{cfg.system}/%{cfg.buildcfg}-%{cfg.architecture}"

include "Coffee/Externals"

project "Coffee"
	location "Coffee"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	
	staticruntime "on"
	
	targetdir ("Build/bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("Build/obj/" .. outputDirectory .. "/%{prj.name}")
	
	pchheader "CoffeePCH.h"
	pchsource "%{prj.name}/src/CoffeePCH.cpp"
	
	defines { "GLFW_INCLUDE_NONE" }
	
	includedirs {
		"%{prj.name}/Externals/glad/include",
		"%{prj.name}/Externals/glfw3/include",
		"%{prj.name}/Externals/glm/include",
		"%{prj.name}/Externals/imgui/include",
		"%{prj.name}/Externals/imgui/include/imgui",
		"%{prj.name}/Externals/spdlog/include",
		"%{prj.name}/include"
	}
	
	links {
		"Externals",
		"opengl32"
	}
	
	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/src/**.cpp"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines {
			"CF_PLATFORM_WINDOWS",
			"CF_BUILD_DLL",
		}
		
	filter "configurations:Debug"
		defines {
			"CF_DEBUG=1",
			"CF_RELEASE=0",
			"CF_DIST=0",
			"CF_ENABLE_ASSERTS=1"
		}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines {
			"CF_DEBUG=0",
			"CF_RELEASE=1",
			"CF_DIST=0",
			"CF_ENABLE_ASSERTS=0"
		}
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines {
			"CF_DEBUG=0",
			"CF_RELEASE=0",
			"CF_DIST=1",
			"CF_ENABLE_ASSERTS=0"
		}
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	
	staticruntime "on"
	
	targetdir ("Build/bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("Build/obj/" .. outputDirectory .. "/%{prj.name}")
	
	includedirs {
		"Coffee/Externals/glad/include",
		"Coffee/Externals/glfw3/include",
		"Coffee/Externals/glm/include",
		"Coffee/Externals/imgui/include",
		"Coffee/Externals/spdlog/include",
		
		"Coffee/include"
	}
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}
	
	links {
		"Coffee"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines {
			"CF_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines {
			"CF_DEBUG=1",
			"CF_RELEASE=0",
			"CF_DIST=0",
			"CF_ENABLE_ASSERTS=1"
		}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines {
			"CF_DEBUG=0",
			"CF_RELEASE=1",
			"CF_DIST=0",
			"CF_ENABLE_ASSERTS=0"
		}
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines {
			"CF_DEBUG=0",
			"CF_RELEASE=0",
			"CF_DIST=1",
			"CF_ENABLE_ASSERTS=0"
		}
		runtime "Release"
		optimize "on"