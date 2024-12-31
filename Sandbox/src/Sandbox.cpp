#include "Angel3D.h"
#include <Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "Sandbox3D.h"

namespace Sandbox
{
  class SandboxApp : public Angel3D::Core::Application
  {
    public:
      SandboxApp()
      {
        PushLayer(new Sandbox2D());
      }

      ~SandboxApp()
      {
      }
  };
} // namespace Sandbox

Angel3D::Core::Application* Angel3D::Core::CreateApplication()
{
  return new Sandbox::SandboxApp();
}