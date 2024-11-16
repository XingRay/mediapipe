// Windows DLL
#if _WIN32
#define MP_CPP_EXPORT __declspec(dllexport)  // DLL Export
#if defined(COMPILING_DLL)
#define MP_CPP_API __declspec(dllexport)  // DLL Export
#else
#define MP_CPP_API __declspec(dllimport)  // DLL Import
#endif
#else
// Linux SO
#define MP_CPP_EXPORT __attribute__((visibility("default")))  
#define MP_CPP_API
#endif