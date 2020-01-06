project "Externals"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	
	staticruntime "on"
	
	targetdir ("Build/bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("Build/obj/" .. outputDirectory .. "/%{prj.name}")
	
	files {
		"glad/include/KHR/khrplatform.h",
		"glad/include/glad/glad.h",
		"glad/src/glad.c",
		
		"glfw3/include/GLFW/glfw3.h",
		"glfw3/include/GLFW/glfw3native.h",
		"glfw3/src/glfw_config.h",
		"glfw3/src/context.c",
		"glfw3/src/init.c",
		"glfw3/src/input.c",
		"glfw3/src/monitor.c",
		"glfw3/src/vulkan.c",
		"glfw3/src/window.c",
		
		"imgui/include/imgui/imconfig.h",
		"imgui/include/imgui/imgui.h",
		"imgui/include/imgui/imgui_internal.h",
		"imgui/include/imgui/imgui_impl_glfw.h",
		"imgui/include/imgui/imgui_impl_opengl3.h",
		"imgui/include/imgui/imstb_rectpack.h",
		"imgui/include/imgui/imstb_textedit.h",
		"imgui/include/imgui/imstb_truetype.h",
		"imgui/include/imgui/imgui.cpp",
		"imgui/include/imgui/imgui_demo.cpp",
		"imgui/include/imgui/imgui_draw.cpp",
		"imgui/include/imgui/imgui_impl_glfw.cpp",
		"imgui/include/imgui/imgui_impl_opengl3.cpp",
		"imgui/include/imgui/imgui_widgets.cpp"
	}
	
	includedirs {
		"glad/include",
		"glfw3/include",
		"glm/include",
		"imgui/include/imgui"
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
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"