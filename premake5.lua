workspace "kx"
   architecture "x64"
   configurations { "Debug", "Release","Dist" }

outputdir = "%{cfg.bhidcfg}-%{cfg.system}-%{cfg.architecture}"
project "kx"
   location "kx"
   kind "SharedLib"
   language "C++"


   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

   files
   {
	   "%{prj.name}/Src/**.h",
	    "%{prj.name}/Src/**.cpp"
   }

   includedirs{
	   "%{prj.name}/vendor/spdlog/include",
	   "kx/Src"

   }
   filter "system:windows"
      cppdialect "c++17"
	  staticruntime "On"
	  systemversion "latest"

      defines{
	   "kx_PLATFORM_WINDOW",
	   "kx_BUILD_DLL"
      }
      
   filter "configurations:Debug"
         defines "kx_DEBUG"
	    
   filter "configurations:Release"
         defines "kx_RELEASE"
		 optimize "On"

   filter "configurations:Dist"
         defines "kx_Dist"
		 optimize "On"





   project "sand"
	location "sand"
    kind "ConsoleApp" 
    language "C++"


   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

   files
   {
	   "%{prj.name}/Src/**.h",
	    "%{prj.name}/Src/**.cpp"
   }

   includedirs{
	   "kx/vendor/spdlog/include",
	   "kx/Src"
   }
   links{
	   "kx"
   }
   filter "system:windows"
      cppdialect "c++17"
	  staticruntime "On"
	  systemversion "latest"

      defines{
	   "kx_PLATFORM_WINDOW"
	   
      }
    
   filter "configurations:Debug"
         defines "kx_DEBUG"
	    
   filter "configurations:Release"
         defines "kx_RELEASE"
		 optimize "On"

   filter "configurations:Dist"
         defines "kx_Dist"
		 optimize "On"
