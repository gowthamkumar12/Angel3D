#pragma once

#include "Core/Core.h"
#include "Events/Event.h"

namespace Angel3D::Core
{
  class ANGEL3D_API Layer
  {
    public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer();

      virtual void OnAttach() {}
      virtual void OnDetach() {}
      virtual void OnUpdate() {}
      virtual void OnEvent(Angel3D::Events::Event& f_e) {}
      virtual void OnImGuiRender() {}

      inline const std::string& GetName() { return m_Name; }

    private:
      std::string m_Name;
  };
} // namespace Angel3D::Core
