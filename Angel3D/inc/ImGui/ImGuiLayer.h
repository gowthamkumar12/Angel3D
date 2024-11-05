#pragma once

#include "Core/Layer.h"

namespace Angel3D
{
  namespace ImGuiImpl
  {
    class ANGEL3D_API ImGuiLayer : public Angel3D::Core::Layer
    {
      public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Angel3D::Events::Event& f_e) override;

      private:
        float m_Time = 0.0f;
    };
  } // namespace ImGuiImpl
} // namespace Angel3D
