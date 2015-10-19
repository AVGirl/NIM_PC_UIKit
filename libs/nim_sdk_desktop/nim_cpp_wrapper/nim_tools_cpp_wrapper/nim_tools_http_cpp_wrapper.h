﻿#ifndef HTTP_EXPORT_C_PLUS_PLUS_WRAPPER_H_
#define HTTP_EXPORT_C_PLUS_PLUS_WRAPPER_H_

#include "net/export/nim_tools_http.h"

namespace nim_http
{

typedef std::function<void(bool, int)> CompletedCallback;
typedef std::function<void(bool, int, const std::string&)> ResponseCallback;
typedef std::function<void(double, double, double, double)> ProgressCallback;
class HttpRequest;

/** @fn void nim_http_init()
* NIM HTTP 初始化
* @return void 无返回值
*/
void Init();

/** @fn void nim_http_uninit()
* NIM HTTP 反初始化
* @return void 无返回值
*/
void Uninit();

/** @fn int nim_http_post_request(HttpRequestHandle)
* NIM HTTP 发起任务
* @param[in] request_handle	http任务句柄
* @return int					任务id
*/
int PostRequest(const HttpRequest& http_request);

/** @fn void nim_http_remove_request(int http_request_id)
* NIM HTTP 取消任务
* @param[in] http_request_id	任务id
* @return void				无返回值
*/
void RemoveRequest(int http_request_id);

/** @class HttpRequest
* @brief NIM HTTP提供的http传输相关接口
* @copyright (c) 2015, NetEase Inc. All rights reserved
* @author towik
* @date 2015/4/30
*/
class HttpRequest
{
public:
	/** 
	* NIM HTTP 创建下载文件任务
	* @param[in] url					资源地址
	* @param[in] download_file_path	下载文件保存的本地路径
	* @param[in] complete_cb			结束回调
	* @return HttpRequestHandle		http任务句柄
	*/
	HttpRequest(const std::string& url, const std::string& download_file_path,
		const CompletedCallback& complete_cb, const ProgressCallback& progress_cb = ProgressCallback());

	/** 
	* NIM HTTP 创建下载文件任务，支持断点续传
	* @param[in] url					资源地址
	* @param[in] download_file_path	下载文件保存的本地路径
	* @param[in] range_start			下载文件的起始点
	* @param[in] complete_cb			结束回调
	* @return HttpRequestHandle		http任务句柄
	*/
	HttpRequest(const std::string& url, const std::string& download_file_path,
		__int64 range_start, const CompletedCallback& complete_cb, const ProgressCallback& progress_cb = ProgressCallback());
	HttpRequest(const std::string& url, const char* post_body, size_t post_body_size, 
		const ResponseCallback& response_cb, const ProgressCallback& progress_cb = ProgressCallback());

	/** 
	* NIM HTTP 创建任务
	* @param[in] request_handle	http任务句柄
	* @param[in] key				头的key
	* @param[in] value			头的value
	* @return void				无返回值
	*/
	void AddHeader(const std::string& key, const std::string& value);

	/** 
	* NIM HTTP 创建任务
	* @param[in] request_handle	http任务句柄
	* @param[in] key				头的key
	* @param[in] value			头的value
	* @return void				无返回值
	*/
	void AddHeader(const std::map<std::string, std::string>& headers_map);

	/** 
	* NIM HTTP 强制设置http请求方法为post
	* @param[in] request_handle	http任务句柄
	* @return void				无返回值
	*/
	void SetMethodAsPost();

	/** 
	* NIM HTTP 设置超时
	* @param[in] request_handle	http任务句柄
	* @param[in] timeout_ms		超时时间，单位是毫秒
	* @return void				无返回值
	*/
	void SetTimeout(int timeout_ms);

private:
	static void CompletedCallbackWrapper(const void* user_data, bool is_ok, int response_code);
	static void ResponseCallbackWrapper(const void* user_data, bool is_ok, int response_code, const char* content);
	static void ProgressCallbackWrapper(const void* user_data, double upload_size, double uploaded_size, double download_size, double downloaded_size);

private:
	friend int PostRequest(const HttpRequest& http_request);
	HttpRequestHandle http_reuqest_handle_;
};

}


#endif // HTTP_EXPORT_C_PLUS_PLUS_WRAPPER_H_
