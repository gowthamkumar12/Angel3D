#include "Engine.h"
#include <Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Engine
{
  class EditorApp : public Core::Application
  {
    public:
      EditorApp()
      : Core::Application("Engine Editor")
      {
        PushLayer(Core::CreateRef<Editor>());
      }

      ~EditorApp()
      {
      }
  };
} // namespace Sandbox

Engine::Core::Application* Engine::Core::CreateApplication()
{
  return new Engine::EditorApp();
}