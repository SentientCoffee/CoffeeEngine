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
	
project "Coffee"
	location "Coffee"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	
	staticruntime "off"
	
	targetdir ("Build/bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("Build/obj/" .. outputDirectory .. "/%{prj.name}")
	
	includedirs {
		"%{prj.name}/Externals/spdlog/include",
		"%{prj.name}/include"
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
			"CF_BUILD_DLL"
		}
		
	filter "configurations:Debug"
		defines "CF_DEBUG=1"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "CF_RELEASE=1"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "CF_DIST=1"
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
		
		postbuildcommands {
			("{COPY} ../Build/bin/" .. outputDirectory .. "/Coffee/Coffee.dll %{cfg.buildtarget.directory}")
		}
	
	filter "configurations:Debug"
		defines "CF_DEBUG=1"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "CF_RELEASE=1"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "CF_DIST=1"
		runtime "Release"
		optimize "on"