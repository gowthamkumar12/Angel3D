#pragma once

#include "Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Angel3D::Core
{
	class Log
	{
		public:
			static void Init();

			inline static Ref<spdlog::logger>& GetCoreLogger()
			{
				return s_CoreLogger;
			}

			inline static Ref<spdlog::logger>& GetClientLogger()
			{
				return s_ClientLogger;
			}

		private:
			static Ref<spdlog::logger> s_CoreLogger;
			static Ref<spdlog::logger> s_ClientLogger;
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