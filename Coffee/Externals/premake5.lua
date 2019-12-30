project "Externals"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	
	staticruntime "on"
	
	targetdir ("Build/bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("Build/obj/" .. outputDirectory .. "/%{prj.name}")
	
	files {
		"glfw3/include/GLFW/glfw3.h",
        "glfw3/include/GLFW/glfw3native.h",
        "glfw3/src/glfw_config.h",
        "glfw3/src/context.c",
        "glfw3/src/init.c",
        "glfw3/src/input.c",
        "glfw3/src/monitor.c",
        "glfw3/src/vulkan.c",
        "glfw3/src/window.c"
	}
	
	filter "system:windows"		
        systemversion "latest"
        
        files {
            "glfw3/src/win32_init.c",
            "glfw3/src/win32_joystick.c",
            "glfw3/src/win32_monitor.c",
            "glfw3/src/win32_time.c",
            "glfw3/src/win32_thread.c",
            "glfw3/src/win32_window.c",
            "glfw3/src/wgl_context.c",
            "glfw3/src/egl_context.c",
            "glfw3/src/osmesa_context.c"
        }

		defines { 
            "_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines {
			"CF_DEBUG=1",
			"CF_RELEASE=0",
			"CF_DIST=0"
		}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines {
			"CF_DEBUG=0",
			"CF_RELEASE=1",
			"CF_DIST=0"
		}
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines {
			"CF_DEBUG=0",
			"CF_RELEASE=0",
			"CF_DIST=1"
		}
		runtime "Release"
		optimize "on"