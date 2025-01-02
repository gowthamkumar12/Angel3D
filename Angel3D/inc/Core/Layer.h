#pragma once

#include "Core/Core.h"
#include "Core/Timestep.h"
#include "Events/Event.h"

namespace Angel3D::Core
{
  class Layer
  {
    public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer() = default;

      virtual void OnAttach() {}
      virtual void OnDetach() {}
      virtual void OnUpdate(Timestep f_ts) {}
      virtual void OnImGuiRender() {}
      virtual void OnEvent(Angel3D::Events::Event& f_e) {}

      inline const std::string& GetName() { return m_Name; }

    private:
      std::string m_Name;
  };
} // namespace Angel3D::Core
