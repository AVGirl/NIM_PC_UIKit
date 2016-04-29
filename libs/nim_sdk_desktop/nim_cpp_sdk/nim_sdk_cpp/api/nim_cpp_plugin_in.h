/** @file nim_cpp_plugin_in.h
  * @brief NIM SDK �ṩ��plugin����ӿ�
  * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/12/29
  */

#ifndef _NIM_SDK_CPP_PLUGIN_IN_H_
#define _NIM_SDK_CPP_PLUGIN_IN_H_

#include <string>
#include <functional>

/**
* @namespace nim
* @brief namespace nim
*/
namespace nim
{

#include "nim_plugin_in_def.h"

/** @class PluginIn
  * @brief NIM SDK �ṩ��plugin����ӿ���
  */
class PluginIn
{
public:
	typedef std::function<void(int error_code, const std::string& result)>	ChatRoomRequestEnterCallback;	/**<  ��ȡ�����ҵ�¼��Ϣ�ص�*/

public:
	/** @fn void ChatRoomRequestEnter(const __int64 room_id, const ChatRoomRequestEnterCallback &callback, const std::string& json_extension = "")
  * �첽��ȡ�������������Ϣ
  * @param[in] room_id				������ID
  * @param[in] callback				�ص�����
  * @param[in] json_extension		json��չ���������ã�Ŀǰ����Ҫ��
  * @return void �޷���ֵ
  */
	static void ChatRoomRequestEnterAsync(const __int64 room_id, const ChatRoomRequestEnterCallback &callback, const std::string& json_extension = "");
};

} 

#endif //_NIM_SDK_CPP_PLUGIN_IN_H_