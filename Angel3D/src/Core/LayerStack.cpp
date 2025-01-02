#include "Core/LayerStack.h"

namespace Angel3D::Core
{
  LayerStack::~LayerStack()
  {
    for(Ref<Layer> layer : m_Layers)
    {
			layer->OnDetach();
    }
  }

  void LayerStack::PushLayer(Ref<Layer> f_layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, f_layer);
		m_LayerInsertIndex++;
		f_layer->OnAttach();
	}

	void LayerStack::PushOverlay(Ref<Layer> f_overlay)
	{
		m_Layers.emplace_back(f_overlay);
		f_overlay->OnAttach();
	}

  void LayerStack::PopLayer(Ref<Layer> f_layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, f_layer);
		if (it != m_Layers.end())
		{
			f_layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

  void LayerStack::PopOverlay(Ref<Layer> f_overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), f_overlay);
		if (it != m_Layers.end())
		{
			f_overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
} // namespace Angel3D
