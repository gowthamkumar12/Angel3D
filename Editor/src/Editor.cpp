#include "Angel3D.h"
#include <Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Angel3D
{
  class EditorApp : public Core::Application
  {
    public:
      EditorApp()
      : Core::Application("Angel3D Editor")
      {
        PushLayer(Core::CreateRef<Editor>());
      }

      ~EditorApp()
      {
      }
  };
} // namespace Sandbox

Angel3D::Core::Application* Angel3D::Core::CreateApplication()
{
  return new Angel3D::EditorApp();
}