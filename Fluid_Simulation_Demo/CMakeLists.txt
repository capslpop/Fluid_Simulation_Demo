add_executable (Fluid_Simulation_Demo 
    "main.cpp" 
    "main.h"
    "MBG/OpenGL/Memory/DescriptorSetBuffer.hpp"
    "MBG/OpenGL/Memory/ElementBuffer.hpp"
    "MBG/OpenGL/Memory/IndirectDrawBuffer.hpp"
    "MBG/OpenGL/Memory/InstancedElementBuffer.hpp"
    "MBG/OpenGL/Memory/TextureBuffer.hpp"
    "MBG/OpenGL/Memory/TextureCubeMapBuffer.hpp"
    "MBG/OpenGL/Memory/Texture2DArrayBuffer.hpp"
    "MBG/OpenGL/Memory/Texture2DBuffer.hpp"
    "MBG/OpenGL/Memory/Texture3DBuffer.hpp"
    "MBG/OpenGL/Memory/UniformBuffer.hpp"
    "MBG/OpenGL/Memory/VertexBuffer.hpp"
    "MBG/OpenGL/CommandBuffer.hpp"
    "MBG/OpenGL/FrameGraph.hpp"
    "MBG/OpenGL/FrameGraph.cpp"
    "MBG/OpenGL/Info.hpp"
    "MBG/OpenGL/MBG.hpp"
    "MBG/OpenGL/RenderPass.hpp"
    "MBG/OpenGL/RenderPass.cpp"
    "MBG/OpenGL/Window.hpp"
    "MBG/OpenGL/Window.cpp"
     "Camera/Camera.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Fluid_Simulation_Demo PROPERTY CXX_STANDARD 20)
endif()

# If we are in debug mode declate that
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
endif()

find_package (glfw3 REQUIRED)
target_link_libraries (Fluid_Simulation_Demo PRIVATE glfw)

find_package (glm REQUIRED)
target_link_libraries (Fluid_Simulation_Demo PRIVATE glm::glm)

find_package(glad REQUIRED)
target_link_libraries(Fluid_Simulation_Demo PRIVATE glad::glad)

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy_shaders.cmake
)
add_dependencies(Fluid_Simulation_Demo copy_shaders)

