#pragma once

#include "Core/Core.h"

namespace Engine::Renderer
{
  struct FramebufferSpecification
	{
		uint32_t Width;
		uint32_t Height;
		uint32_t Samples         = 1;
		bool     SwapChainTarget = false;
	};

	class Framebuffer
	{
    public:
      virtual void Bind() = 0;
      virtual void Unbind() = 0;

      virtual uint32_t GetColorAttachmentRendererID() const = 0;
      virtual const FramebufferSpecification& GetSpecification() const = 0;

      static Engine::Core::Ref<Framebuffer> Create(const FramebufferSpecification& f_specifications);
	};
} // namespace Engine::Renderer
