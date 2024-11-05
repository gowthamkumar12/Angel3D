#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Angel3D::Core
{
	class ANGEL3D_API Log
	{
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
			{
				return s_CoreLogger;
			}

			inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
			{
				return s_ClientLogger;
			}

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
		};
}

// Core log macros
#define ANGEL3D_CORE_TRACE(...)    ::Angel3D::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ANGEL3D_CORE_INFO(...)     ::Angel3D::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ANGEL3D_CORE_WARN(...)     ::Angel3D::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ANGEL3D_CORE_ERROR(...)    ::Angel3D::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ANGEL3D_CORE_CRITICAL(...) ::Angel3D::Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ANGEL3D_TRACE(...)         ::Angel3D::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ANGEL3D_INFO(...)          ::Angel3D::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define ANGEL3D_WARN(...)          ::Angel3D::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ANGEL3D_ERROR(...)         ::Angel3D::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define ANGEL3D_CRITICAL(...)      ::Angel3D::Core::Log::GetClientLogger()->critical(__VA_ARGS__)