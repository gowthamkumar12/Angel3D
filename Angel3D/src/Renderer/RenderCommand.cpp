#pragma once

#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Angel3D::Renderer
{
  RendererAPI* RenderCommand::s_RendererAPI = new Angel3D::Platform::OpenGL::OpenGLRendererAPI;
} // namespace Angel3D::Renderer
