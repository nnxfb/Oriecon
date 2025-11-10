project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.h",
        "src/**.c",
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

    filter "configurations:Debug"
		-- buildoptions "/MDd"
		buildoptions { "/MDd" }
		symbols "on"
	
	filter "configurations:Release"
		-- buildoptions "/MD"
		buildoptions { "/MD" }
		optimize "on"


