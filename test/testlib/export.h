#pragma once
#ifdef WIN32
#ifdef MAO_TEST_LIB_EXPORTS_H
#define MAO_TEST_LIB_EXPORTS __declspec(dllexport)
#else
#define MAO_TEST_LIB_EXPORTS __declspec(dllimport)
#endif  // MAO_TEST_LIB_EXPORTS_H
#else
#define MAO_TEST_LIB_EXPORTS
#endif  // WIN32