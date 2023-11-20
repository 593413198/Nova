
cmake_minimum_required(VERSION 2.8)

project(Nova)

find_package(OpenGL REQUIRED)

set(SRC_LIST
    Nova.h
    Log.cpp
    Log.h
    Platform/glad.c
    Platform/Windows/WindowsWindow.cpp Platform/Windows/WindowsWindow.h
    Platform/Windows/WindowsInput.cpp Platform/Windows/WindowsInput.h
    Platform/OpenGL/OpenGLContext.cpp
    Platform/OpenGL/OpenGLContext.h
    Platform/OpenGL/OpenGLBuffer.cpp
    Platform/OpenGL/OpenGLBuffer.h
    Platform/OpenGL/OpenGLVertexArray.cpp
    Platform/OpenGL/OpenGLVertexArray.h
    Platform/OpenGL/OpenGLRendererAPI.cpp Platform/OpenGL/OpenGLRendererAPI.h
    Platform/OpenGL/OpenGLShader.cpp Platform/OpenGL/OpenGLShader.h
    Platform/OpenGL/OpenGLTexture.cpp Platform/OpenGL/OpenGLTexture.h
    Renderer/GraphicsContext.h
    Renderer/Shader.cpp Renderer/Shader.h
    Renderer/Renderer.cpp
    Renderer/Renderer.h
    Renderer/Buffer.cpp
    Renderer/Buffer.h
    Renderer/VertexArray.cpp
    Renderer/VertexArray.h
    Renderer/texture.cpp Renderer/texture.h
    Renderer/RendererAPI.cpp Renderer/RendererAPI.h
    Renderer/RenderCommand.cpp Renderer/RenderCommand.h
    Renderer/OrthographicCamera.h
    Cores/Window.h
    Cores/Application.cpp
    Cores/Application.h
    Cores/Layer.h
    Cores/LayerStack.cpp
    Cores/LayerStack.h
    Cores/Input.h
    ImGui/ImGuiLayer.cpp
    ImGui/ImGuiLayer.h
    ../misc/stb_image/stb_image.h
    )

file(GLOB EVENTS_HEADERS Events/*.h)

file (GLOB SRC_LIST_IMGUI
        ../misc/imgui/*.h
        ../misc/imgui/*.cpp
)

set(SRC_LIST_IMGUI_BACKENDS
        ../misc/imgui/backends/imgui_impl_opengl3.h
        ../misc/imgui/backends/imgui_impl_opengl3.cpp
        ../misc/imgui/backends/imgui_impl_opengl3_loader.h
        ../misc/imgui/backends/imgui_impl_glfw.h
        ../misc/imgui/backends/imgui_impl_glfw.cpp
)

add_library(Nova STATIC
    ${SRC_LIST}
    ${EVENTS_HEADERS}
    ${SRC_LIST_IMGUI} ${SRC_LIST_IMGUI_BACKENDS} # IMGUI
)

add_subdirectory(../misc/GLFW ../glfw)

target_link_libraries(${PROJECT_NAME} glfw)

target_include_directories(${PROJECT_NAME} PUBLIC 
    .
    ../misc/spdlog/include
    ../misc/GLFW/include
    ../misc/imgui
    ../misc/imgui/backends
    ../misc/glm
    ../misc/stb_image
    Platform/include
    Events/
    Cores/
    Layer/
    )
