#pragma once

#include "Core/Layer.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

namespace Angel3D::ImGuiImpl
{
  class ANGEL3D_API ImGuiLayer : public Angel3D::Core::Layer
  {
    public:
      ImGuiLayer();
      ~ImGuiLayer();

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnImGuiRender() override;

      void Begin();
      void End();
  };
} // namespace Angel3D
