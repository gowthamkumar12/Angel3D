#pragma once

#include "Core/Layer.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

namespace Engine::ImGuiImpl
{
  class ImGuiLayer : public Engine::Core::Layer
  {
    public:
      ImGuiLayer();
      virtual ~ImGuiLayer() = default;

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnEvent(Engine::Events::Event& f_e) override;

      void Begin();
      void End();
      void BlockEvents(bool block) { m_BlockEvents = block; }

    private:
      bool m_BlockEvents = true;
  };
} // namespace Engine
