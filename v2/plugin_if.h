#ifndef __PLUGIN_PUB_H__
#define __PLUGIN_PUB_H__

#define FUNC_NAME_MAX_SIZE 32
#define FUNC_NAME_MAX_LENGTH 31

#define PLG_NULL 0
#define PLG_FUNC_INFO_NAME "plg_func_info"
#define PLG_FUNC_SIZE_NAME "plg_func_size"

typedef void* PLG_HANDLE;
typedef PLG_HANDLE (*PLG_FUNC)(const char* para);
typedef struct {
    char        name[FUNC_NAME_MAX_SIZE];
    PLG_FUNC    func;
} PLG_FUNC_INFO;


#if defined(__GNUC__)
    #define PLG_API __attribute__((cdecl))
    #define PLG_EXPORT __attribute__ ((visibility("default")))
#elif defined(_MSVC_VER)
    #define PLG_API __cdecl
    #define PLG_EXPORT __declspec(dllexport)
#endif

#define PLG_REG_BEGIN(size) PLG_EXPORT size_t plg_func_size = (size); \
    PLG_EXPORT PLG_FUNC_INFO plg_func_info[]={
#define PLG_REG_FUNC(name,func) {(name),(func)},
#define PLG_REG_END() };


#endif // __PLUGIN_PUB_H__