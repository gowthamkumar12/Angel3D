#include "Engine.h"
#include <Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "Sandbox3D.h"

namespace Sandbox
{
  class SandboxApp : public Engine::Core::Application
  {
    public:
      SandboxApp()
      {
        PushLayer(Engine::Core::CreateRef<Sandbox2D>());
      }

      ~SandboxApp()
      {
      }
  };
} // namespace Sandbox

Engine::Core::Application* Engine::Core::CreateApplication()
{
  return new Sandbox::SandboxApp();
}