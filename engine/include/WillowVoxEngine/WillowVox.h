#pragma once

// For use by WillowVox Engine applications

// Application
#include <WillowVoxEngine/Version.h>
#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Application/Window.h>
// Core
#include <WillowVoxEngine/Core/Logger.h>
// Events
#include <WillowVoxEngine/Events/Event.h>
#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/WindowCloseEvent.h>
#include <WillowVoxEngine/Events/WindowResizeEvent.h>
#include <WillowVoxEngine/Events/KeyPressEvent.h>
#include <WillowVoxEngine/Events/KeyReleaseEvent.h>
#include <WillowVoxEngine/Events/MouseClickEvent.h>
#include <WillowVoxEngine/Events/MouseReleaseEvent.h>
#include <WillowVoxEngine/Events/MouseMoveEvent.h>
#include <WillowVoxEngine/Events/MouseScrollEvent.h>
// Input
#include <WillowVoxEngine/Input/Input.h>
// Math
#include <WillowVoxEngine/Math/Noise.h>
#include <WillowVoxEngine/Math/NoiseSettings.h>
// Physics
#include <WillowVoxEngine/Physics/Physics.h>
// Rendering
#include <WillowVoxEngine/Rendering/Camera.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/Texture.h>
#include <WillowVoxEngine/Rendering/Vertex.h>
// Resources
#include <WillowVoxEngine/Resources/Block.h>
#include <WillowVoxEngine/Resources/Blocks.h>
// World
#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/World/World.h>
#include <WillowVoxEngine/World/GameObject.h>
#include <WillowVoxEngine/World/Component.h>
#include <WillowVoxEngine/World/WorldGen.h>
#include <WillowVoxEngine/World/TerrainGen.h>
// Math (TODO: Don't expose any external libraries to client applications)
#include <glm/glm.hpp>

// --- Entry Point --- //
#include <WillowVoxEngine/Application/EntryPoint.h>
// ------------------- //