#pragma once

// �Ӽ� Ȯ��(���̺귯��, ���� �� ������Ʈ)
// _WIN32�� 32/64-bit ���� �κ� ����
// _WIN64�� 64-bit������ ����
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