#pragma once

// 속성 확인(라이브러리, 게임 각 프로젝트)
// _WIN32는 32/64-bit 공통 부분 정의
// _WIN64는 64-bit에서만 정의
#ifdef _WIN32
#ifdef _WIN64			/// 64-bit  only
#ifdef _DEBUG			/// 64-bit debug
#pragma comment(lib, "..\\x64\\fmodL_vc.lib")
#else					/// 64-bit release
#pragma comment(lib, "..\\x64\\fmod_vc.lib")
#endif					// 64-bit _DEBUG
#else					/// 32-bit  only
#ifdef _DEBUG			/// 32-bit debug
#pragma comment(lib, "..\\x86\\fmodL_vc.lib")
#else					/// 32-bit release
#pragma comment(lib, "..\\x86\\fmod_vc.lib")
#endif					// 32-bit _DEBUG
#endif					// _WIN64
/// 32/64 common def
#endif					// _WIN32