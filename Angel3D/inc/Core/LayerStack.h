#pragma once

#include "Core/Core.h"
#include "Core/Layer.h"

namespace Angel3D::Core
{
  class LayerStack
  {
    public:
      LayerStack() = default;
      ~LayerStack();

      void PushLayer(Ref<Layer> f_layer);
      void PushOverlay(Ref<Layer> f_overlay);

      void PopLayer(Ref<Layer> f_layer);
      void PopOverlay(Ref<Layer> f_overlay);

      std::vector<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }
      std::vector<Ref<Layer>>::iterator end()   { return m_Layers.end(); }

    private:
      std::vector<Ref<Layer>> m_Layers;
      unsigned int m_LayerInsertIndex = 0;
  };
} // namespace Angel3D::Core
