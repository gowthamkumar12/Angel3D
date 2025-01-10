#pragma once

#include "Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Engine::Core
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
#define CORE_TRACE(...)     ::Engine::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)      ::Engine::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)      ::Engine::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)     ::Engine::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)  ::Engine::Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define OUTER_TRACE(...)    ::Engine::Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OUTER_INFO(...)     ::Engine::Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define OUTER_WARN(...)     ::Engine::Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OUTER_ERROR(...)    ::Engine::Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define OUTER_CRITICAL(...) ::Engine::Core::Log::GetClientLogger()->critical(__VA_ARGS__)