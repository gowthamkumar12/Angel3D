#pragma once

#include "Core/Core.h"
#include "Core/Layer.h"

namespace Angel3D
{
  namespace Core
  {
    class ANGEL3D_API LayerStack
    {
      public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* f_layer);
        void PushOverlay(Layer* f_overlay);

        void PopLayer(Layer* f_layer);
        void PopOverlay(Layer* f_overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end()   { return m_Layers.end(); }

      private:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*>::iterator m_LayerInsert;
    };
  } // namespace Core
} // namespace Angel3D
