--
-- GENIe solution to build the EDK STD projects.
-- Ivan Sancho, Escuela Superior de Arte y Tecnologia (ESAT) Valencia, 2020/21
-- Algorithms & Data Structures
--
-- All rights are reserved.
--
--

PROJ_DIR = path.getabsolute("./../")

solution("DS_ALG_AI1" .. _ACTION)
  location(PROJ_DIR .. "/build/")
  language "C"
  kind "ConsoleApp"
  startproject "PR00_MemoryNode"

  defines {
    "_CRT_SECURE_NO_WARNINGS",
  }

  configurations {
    "Debug",
    "Release"
  }

  configuration { "Debug" }
    defines {
      "DEBUG",
    }
    flags {
      "Symbols",
      "ExtraWarnings",
    }
    targetsuffix "_d"

  configuration { "Release" }
    defines {
      "NDEBUG",
    }
    flags {
      "Optimize",
      "OptimizeSize",
      "No64BitChecks",
      "NoPCH",
    }

  projects_names = {
    "PR00_MemoryNode",
    --"PR01_Vector",
    --"PR02_CircularVector",
    --"PR03_MovableVector",
    --"PR04_List",
    --"PR05_DLList",
    --"PR06_CircularList",
    --"PR07_CircularDLList",
    --"PR08_Stack",
    --"PR09_Queue",
    --"PR10_Logger",
    --"PR11_Comparative",
    --"PR12_SortingAlgorithms",
  }

--[[************************* PROJECT GENERATOR FUNCTION *************************]]--
  for i, prj in ipairs(projects_names) do
    project(prj)
      location (PROJ_DIR .. "/build/" .. prj .. "/" .. _ACTION)
      platforms {
        "x32",
        "x64",
        "Native",
      }
      includedirs {
        path.join(PROJ_DIR, "./include/"),
        path.join(PROJ_DIR, "./deps/include/"),
      }
      files {
        path.join(PROJ_DIR, "./include/*.h"),
        path.join(PROJ_DIR, "./include/common_def.h"),
        path.join(PROJ_DIR, "./deps/include/EDK_MemoryManager/*.h"),
      }

      --[[
      configuration "vs2017"
        windowstargetplatformversion "10.0.16299.0"
      configuration "vs2019"
        windowstargetplatformversion "10.0.18362.0"
      ]]--
      libdirs { path.join(PROJ_DIR, "./deps/lib/EDK_MemoryManager") }

      configuration { "Debug", "x32" }
        targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Debug"))
        targetsuffix "_d"
        links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x32/EDK_MemoryManager_Windows_d") }
      configuration { "Debug", "x64" }
        targetdir (path.join(PROJ_DIR, "bin/Debug/x64"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Debug"))
        targetsuffix "_d"
        links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x64/EDK_MemoryManager_Windows_d") }
      configuration { "Release", "x32" }
        targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Release"))
        links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x32/EDK_MemoryManager_Windows") }
      configuration { "Release", "x64" }
        targetdir (path.join(PROJ_DIR, "bin/Release/x64/"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Release"))
        links { path.join(PROJ_DIR, "deps/lib/EDK_MemoryManager/x64/EDK_MemoryManager_Windows") }
	end

  project "PR00_MemoryNode"
  	files {
  	  path.join(PROJ_DIR, "./include/adt_memory_node.h"),
  	  path.join(PROJ_DIR, "./src/adt_memory_node.c"),
  	  path.join(PROJ_DIR, "./tests/test_memory_node.c"),
    }

  --[[
  project "PR01_Vector"
    files {
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c"),
      path.join(PROJ_DIR, "./include/adt_vector.h"),
      path.join(PROJ_DIR, "./src/adt_vector.c"),
      path.join(PROJ_DIR, "./tests/test_vector.c"),
    }
  ]]--
