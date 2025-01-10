#pragma once

namespace Engine::Core
{
  class Timestep
  {
    public:
      Timestep(float f_time)
      : m_Time(f_time)
      {
      }

      operator float() const { return m_Time; }

      float GetSeconds() const { return m_Time; }
      float GetMilliSeconds() const { return m_Time * 1000.0f; }
    private:
      float m_Time;
  };
} // namespace Engine::Core
