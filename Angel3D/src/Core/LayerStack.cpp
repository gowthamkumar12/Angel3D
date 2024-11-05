#include "Core/LayerStack.h"

namespace Angel3D::Core
{
  LayerStack::LayerStack()
  {
    m_LayerInsert = m_Layers.begin();
  }

  LayerStack::~LayerStack()
  {
    for(Layer* layer : m_Layers)
    {
      delete layer;
    }
  }

  void LayerStack::PushLayer(Layer* f_layer)
  {
    m_LayerInsert = m_Layers.emplace(m_LayerInsert, f_layer);
  }

  void LayerStack::PushOverlay(Layer* f_overlay)
  {
    m_Layers.emplace_back(f_overlay);
  }

  void LayerStack::PopLayer(Layer* f_layer)
  {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), f_layer);
    if(it != m_Layers.end())
    {
      m_Layers.erase(it);
      m_LayerInsert--;
    }
  }

  void LayerStack::PopOverlay(Layer* f_overlay)
  {
      auto it = std::find(m_Layers.begin(), m_Layers.end(), f_overlay);
    if(it != m_Layers.end())
    {
      m_Layers.erase(it);
    }
  }
} // namespace Angel3D
