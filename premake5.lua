workspace "Oriecon"
	architecture "amd64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

GLFWDir = ""
GladDir = "Oriecon/vendor/Glad"

project "Oriecon"
	location "Oriecon"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	-- buildoptions "/utf-8"
	buildoptions { "/utf-8" }

	links
	{
		"glfw3",
		"opengl32",
	}
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/GLFW/include",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
	
		defines 
		{
			"ORIECON_PLATFORM_WINDOWS",
			"ORIECON_BUILD_DLL"
		}
	
		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/%{cfg.buildtarget.name}")
		}

	filter "action:vs2015"
		libdirs { "%{prj.name}/vendor/GLFW/lib-vc2015" }
	filter "action:vs2017"
		libdirs { "%{prj.name}/vendor/GLFW/lib-vc2017" }
	filter "action:vs2019"
		libdirs { "%{prj.name}/vendor/GLFW/lib-vc2019" }
	filter "action:vs2022"
		libdirs { "%{prj.name}/vendor/GLFW/lib-vc2022" }

	filter "configurations:Debug"
		defines "ORIECON_CONFIG_DEBUG"
		-- buildoptions "/MDd"
		buildoptions { "/MDd" }
		symbols "on"
	
	filter "configurations:Release"
		defines "ORIECON_CONFIG_RELEASE"
		-- buildoptions "/MD"
		buildoptions { "/MD" }
		optimize "on"

project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- buildoptions "/utf-8"
	buildoptions { "/utf-8" }

	links { "Oriecon" }
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Oriecon/src",
		"Oriecon/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"
		
		defines 
		{
			"ORIECON_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "ORIECON_CONFIG_DEBUG"
		-- buildoptions "/MDd"
		buildoptions { "/MDd" }
		symbols "on"
	
	filter "configurations:Release"
		defines "ORIECON_CONFIG_RELEASE"
		-- buildoptions "/MD"
		buildoptions { "/MD" }
		optimize "on"