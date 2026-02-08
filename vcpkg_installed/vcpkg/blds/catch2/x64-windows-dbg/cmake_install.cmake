# Install script for directory: C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/pkgs/catch2_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/x64-windows-dbg/src/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Catch2" TYPE FILE FILES
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/x64-windows-dbg/Catch2Config.cmake"
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/x64-windows-dbg/Catch2ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Catch2" TYPE FILE FILES
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/extras/ParseAndAddCatchTests.cmake"
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/extras/Catch.cmake"
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/extras/CatchAddTests.cmake"
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/extras/CatchShardTests.cmake"
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/extras/CatchShardTestsImpl.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catch2" TYPE FILE FILES
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/extras/gdbinit"
    "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/extras/lldbinit"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  set(install_pkgconfdir "lib/pkgconfig")
set(impl_pc_file "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/CMake/catch2.pc.in")
set(main_pc_file "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/src/v3.10.0-0c9c014064.clean/CMake/catch2-with-main.pc.in")
set(Catch2_VERSION 3.10.0)
set(include_dir "include")
set(lib_dir "lib")
         message(STATUS "DESTDIR: $ENV{DESTDIR}")
         set(DESTDIR_PREFIX "")
         if (DEFINED ENV{DESTDIR})
           set(DESTDIR_PREFIX "$ENV{DESTDIR}")
         endif ()
         message(STATUS "PREFIX: ${DESTDIR_PREFIX}")
         set(lib_name "Catch2d")
         configure_file(
           "${impl_pc_file}"
           "${DESTDIR_PREFIX}${CMAKE_INSTALL_PREFIX}/${install_pkgconfdir}/catch2.pc"
           @ONLY
         )

         set(lib_name "Catch2Maind")
         configure_file(
           "${main_pc_file}"
           "${DESTDIR_PREFIX}${CMAKE_INSTALL_PREFIX}/${install_pkgconfdir}/catch2-with-main.pc"
           @ONLY
         )
       
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/x64-windows-dbg/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/johnw/source/repos/Fluid_Simulation_Demo/vcpkg_installed/vcpkg/blds/catch2/x64-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
