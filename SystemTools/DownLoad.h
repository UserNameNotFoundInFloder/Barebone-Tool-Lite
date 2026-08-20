#pragma once

#ifdef DOWNLOAD_EXPORTS
#define DOWNLOAD_API __declspec(dllexport)
#else
#define DOWNLOAD_API __declspec(dllimport)
#endif

extern "C" DOWNLOAD_API bool DownloadFileMulti(const char* url, const char* output, int threads);
extern "C" DOWNLOAD_API const char* GetLastErrorMsg();