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
  startproject "PR03_MovableVector"

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
    "PR01_Vector",
    "PR02_CircularVector",
    "PR03_MovableVector",
    "PR04_List",
    "PR05_DLList",
    "PR06_CircularList",
    "PR07_CircularDLList",
    "PR08_Stack",
    "PR09_Queue",
    --"PR10_Logger",
    "PR11_Comparative",
    "PR12_Comparative_STD",
    "PR13_SortingAlgorithms",
    "PR14_CPP_MemoryNode",
    "PR15_CPP_Vector",
    "PR16_CPP_CircularVector",
    "PR17_CPP_MovableVector",
    "PR18_CPP_List",
    "PR19_CPP_DLList",
    "PR22_CPP_Stack",
    "PR23_CPP_Queue",
    "PR24_CPP_Logger",
  }

--[[************************* PROJECT GENERATOR FUNCTION *************************]]--
  for i, prj in ipairs(projects_names) do
    project(prj)
      if prj == "PR12_Comparative_STD" then
        language "C++"
      end
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

  project "PR01_Vector"
    files {
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c"),
      path.join(PROJ_DIR, "./include/adt_vector.h"),
      path.join(PROJ_DIR, "./src/adt_vector.c"),
      path.join(PROJ_DIR, "./tests/test_vector.c"),
    }

  project "PR03_MovableVector"
    files {
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./include/adt_movable_vector.h"),
      path.join(PROJ_DIR, "./include/adt_vector.h"),
      path.join(PROJ_DIR, "./src/adt_movable_vector.c"),
      path.join(PROJ_DIR, "./tests/test_movable_vector.c"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c")
    }

  project "PR02_CircularVector"
    files {
       path.join(PROJ_DIR, "./include/adt_memory_node.h"),
       path.join(PROJ_DIR, "./include/adt_vector.h"),
       path.join(PROJ_DIR, "./include/adt_circular_vector.h"),
       path.join(PROJ_DIR, "./tests/test_circular_vector.c"),
       path.join(PROJ_DIR, "./src/adt_circular_vector.c"),
       path.join(PROJ_DIR, "./src/adt_memory_node.c")
    }

  project "PR04_List"
    files {
        path.join(PROJ_DIR, "./include/adt_memory_node.h"),
        path.join(PROJ_DIR, "./src/adt_memory_node.c"),
        path.join(PROJ_DIR, "./include/adt_list.h"),
        path.join(PROJ_DIR, "./src/adt_list.c"),
        path.join(PROJ_DIR, "./tests/test_list.c"),
    }

  project "PR05_DLList"
    files {
        path.join(PROJ_DIR, "./include/adt_memory_node.h"),
        path.join(PROJ_DIR, "./src/adt_memory_node.c"),
        path.join(PROJ_DIR, "./include/adt_dllist.h"),
        path.join(PROJ_DIR, "./src/adt_dllist.c"),
        path.join(PROJ_DIR, "./tests/test_dllist.c"),
    }

  project "PR06_CircularList"
    files {
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c"),
      path.join(PROJ_DIR, "./include/adt_clist.h"),
      path.join(PROJ_DIR, "./src/adt_clist.c"),
      path.join(PROJ_DIR, "./tests/test_clist.c"),
    }
  project "PR07_CircularDLList"
    files {
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c"),
      path.join(PROJ_DIR, "./include/adt_cdllist.h"),
      path.join(PROJ_DIR, "./src/adt_cdllist.c"),
      path.join(PROJ_DIR, "./tests/test_cdllist.c"),
    }

  project "PR08_Stack"
    files {
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c"),
      path.join(PROJ_DIR, "./include/adt_vector.h"),
      path.join(PROJ_DIR, "./src/adt_vector.c"),
      path.join(PROJ_DIR, "./include/adt_stack.h"),
      path.join(PROJ_DIR, "./src/adt_stack.c"),
      path.join(PROJ_DIR, "./tests/test_stack.c"),
    }

  project "PR09_Queue"
    files {
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c"),
      path.join(PROJ_DIR, "./include/adt_queue.h"),
      path.join(PROJ_DIR, "./src/adt_queue.c"),
      path.join(PROJ_DIR, "./include/adt_list.h"),
      path.join(PROJ_DIR, "./src/adt_list.c"),
      path.join(PROJ_DIR, "./tests/test_queue.c"),
    }

    project "PR11_Comparative"
    files {
        path.join(PROJ_DIR, "./include/adt_memory_node.h"),
        path.join(PROJ_DIR, "./include/adt_vector.h"),
        path.join(PROJ_DIR, "./include/adt_list.h"),
        path.join(PROJ_DIR, "./include/adt_dllist.h"),
        path.join(PROJ_DIR, "./src/adt_vector.c"),
        path.join(PROJ_DIR, "./src/adt_list.c"),
        path.join(PROJ_DIR, "./src/adt_dllist.c"),
        path.join(PROJ_DIR, "./src/adt_memory_node.c") ,
        path.join(PROJ_DIR, "./tests/comparative.c"),
    }
    project "PR12_Comparative_STD"
    files {
        path.join(PROJ_DIR, "./include/adt_memory_node.h"),
        path.join(PROJ_DIR, "./include/adt_vector.h"),
        path.join(PROJ_DIR, "./include/adt_list.h"),
        path.join(PROJ_DIR, "./include/adt_dllist.h"),
        path.join(PROJ_DIR, "./src/adt_vector.c"),
        path.join(PROJ_DIR, "./src/adt_list.c"),
        path.join(PROJ_DIR, "./src/adt_dllist.c"),
        path.join(PROJ_DIR, "./src/adt_memory_node.c") ,
        path.join(PROJ_DIR, "./tests/comparative.cc"),
    }
    project "PR13_SortingAlgorithms"
    files {
        path.join(PROJ_DIR, "./include/adt_memory_node.h"),
        path.join(PROJ_DIR, "./include/adt_vector.h"),
        path.join(PROJ_DIR, "./include/adt_list.h"),
        path.join(PROJ_DIR, "./include/adt_dllist.h"),
        path.join(PROJ_DIR, "./src/adt_vector.c"),
        path.join(PROJ_DIR, "./src/adt_list.c"),
        path.join(PROJ_DIR, "./src/adt_dllist.c"),
        path.join(PROJ_DIR, "./src/adt_memory_node.c"),
        path.join(PROJ_DIR, "./tests/sorting.c")
    }

    project "PR14_CPP_MemoryNode"
      language "C++"
      files {
        path.join(PROJ_DIR, "./include/memory_node.h"),
        path.join(PROJ_DIR, "./src/memory_node.cc"),
        path.join(PROJ_DIR, "./tests/test_memory_node.cc"),
      }

    project "PR15_CPP_Vector"
      language "C++"
      files {
        path.join(PROJ_DIR, "./include/vector.h"),
        path.join(PROJ_DIR, "./src/vector.cc"),
        path.join(PROJ_DIR, "./tests/test_vector.cc"),
        path.join(PROJ_DIR, "./src/memory_node.cc"),
      }

    project "PR16_CPP_CircularVector"
      language "C++"
      files {
        path.join(PROJ_DIR, "./include/circular_vector.h"),
        path.join(PROJ_DIR, "./src/circular_vector.cc"),
        path.join(PROJ_DIR, "./tests/test_circular_vector.cc"),
        path.join(PROJ_DIR, "./src/memory_node.cc"),
      }
    project "PR17_CPP_MovableVector"
    language "C++"
    files {
      path.join(PROJ_DIR, "./include/movable_vector.h"),
      path.join(PROJ_DIR, "./src/movable_vector.cc"),
      path.join(PROJ_DIR, "./tests/test_movable_vector.cc"),
      path.join(PROJ_DIR, "./src/memory_node.cc"),
    }

    project "PR18_CPP_List"
    language "C++"
    files {
      path.join(PROJ_DIR, "./include/list.h"),
      path.join(PROJ_DIR, "./src/list.cc"),
      path.join(PROJ_DIR, "./tests/test_list.cc"),
      path.join(PROJ_DIR, "./src/memory_node.cc"),
    }
    
    project "PR19_CPP_DLList"
    language "C++"
    files {
      path.join(PROJ_DIR, "./include/dllist.h"),
      path.join(PROJ_DIR, "./src/dllist.cc"),
      path.join(PROJ_DIR, "./tests/test_dllist.cc"),
      path.join(PROJ_DIR, "./src/memory_node.cc"),
    }
    
    project "PR24_CPP_Logger"
    files {
      path.join(PROJ_DIR, "./include/logger.h"),
      path.join(PROJ_DIR, "./src/logger.c"),
      path.join(PROJ_DIR, "./tests/test_logger.c"),
      path.join(PROJ_DIR, "./include/adt_memory_node.h"),
      path.join(PROJ_DIR, "./src/adt_memory_node.c"),
      path.join(PROJ_DIR, "./include/adt_queue.h"),
      path.join(PROJ_DIR, "./src/adt_queue.c"),
      path.join(PROJ_DIR, "./include/adt_list.h"),
      path.join(PROJ_DIR, "./src/adt_list.c"),
    }

    project "PR23_CPP_Queue"
    language "C++"
    files {
      path.join(PROJ_DIR, "./src/memory_node.cc"),
      path.join(PROJ_DIR, "./src/list.cc"),
      path.join(PROJ_DIR, "./src/queue.cc"),
      path.join(PROJ_DIR, "./tests/test_queue.cc"),
    }
    
    project "PR22_CPP_Stack"
    language "C++"
    files {
        path.join(PROJ_DIR, "./src/memory_node.cc"),
        path.join(PROJ_DIR, "./src/vector.cc"),
        path.join(PROJ_DIR, "./src/stack.cc"),
        path.join(PROJ_DIR, "./tests/test_stack.cc"),
    }
