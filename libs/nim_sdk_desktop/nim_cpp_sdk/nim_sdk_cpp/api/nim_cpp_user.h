﻿#ifndef _NIM_SDK_CPP_USER_H_
#define _NIM_SDK_CPP_USER_H_

#include <string>
#include <list>
#include <functional>
#include "nim_user_helper.h"

namespace nim
{
/** @class User
  * @brief NIM SDK提供的用户相关接口
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author towik, Oleg
  * @date 2015/8/17
  */

#include "nim_user_def.h"
#include "nim_res_code_def.h"

class User
{

public:
	typedef std::function<void(const SpecialRelationshipChangeEvent&)> SpecialRelationshipChangedCallback;

	typedef std::function<void(NIMResCode res_code, const std::string& accid, bool set_opt)> SetRelationCallback;
	typedef SetRelationCallback SetBlackCallback;
	typedef SetRelationCallback SetMuteCallback;

	typedef std::function<void(NIMResCode res_code, const std::list<MuteListInfo>&)> GetMuteListCallback;
	typedef std::function<void(NIMResCode res_code, const std::list<BlackListInfo>&)> GetBlackListCallback;

	typedef std::function<void(const std::list<UserNameCard>&)> UserNameCardChangedCallback;
	typedef std::function<void(const std::list<UserNameCard>&)> GetUserNameCardCallback;
	typedef std::function<void(NIMResCode res_code)> UpdateUserNameCardCallback;

	/** @fn static void RegSpecialRelationshipChangedCb(const SpecialRelationshipChangedCallback& cb, const std::string& json_extension = "")
	* 统一注册用户属性变更通知回调函数（多端同步黑名单、静音名单变更）
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @param[in] cb
	* @return void 无返回值
	*/
	static void RegSpecialRelationshipChangedCb(const SpecialRelationshipChangedCallback& cb, const std::string& json_extension = "");

	/** @fn static bool SetBlack(const std::string& accid, bool set_black, const SetBlackCallback& cb, const std::string& json_extension = "")
	* 设置、取消设置黑名单
	* @param[in] accid 好友id
	* @param[in] set_black 取消或设置
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @param[in] cb
	* @return bool 检查参数如果不符合要求则返回失败
	*/
	static bool SetBlack(const std::string& accid, bool set_black, const SetBlackCallback& cb, const std::string& json_extension = "");

	/** @fn static bool SetMute(const std::string& accid, bool set_mute, const SetMuteCallback& cb, const std::string& json_extension = "")
	* 设置、取消设置静音名单
	* @param[in] accid 好友id
	* @param[in] set_mute 取消或设置
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @param[in] cb
	* @return bool 检查参数如果不符合要求则返回失败
	*/
	static bool SetMute(const std::string& accid, bool set_mute, const SetMuteCallback& cb, const std::string& json_extension = "");

	/** @fn static void GetMutelist(const GetMuteListCallback& cb, const std::string& json_extension = "")
	* 获得静音名单列表 
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @param[in] cb
	* @return bool 检查参数如果不符合要求则返回失败
	*/
	static void GetMutelist(const GetMuteListCallback& cb, const std::string& json_extension = "");

	/** @fn static void GetBlacklist(const GetBlackListCallback& cb, const std::string& json_extension = "")
	* 获得黑名单名单
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @param[in] cb
	* @return void 无返回值
	*/
	static void GetBlacklist(const GetBlackListCallback& cb, const std::string& json_extension = "");

	/** @fn static void RegUserNameCardChangedCb(const UserNameCardChangedCallback& cb, const std::string& json_extension = "")
	* 统一注册用户名片变更通知回调函数
	* @param[in] cb 操作结果回调
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @return void 无返回值
	*/
	static void RegUserNameCardChangedCb(const UserNameCardChangedCallback& cb, const std::string& json_extension = "");

	/** @fn static bool GetUserNameCard(const std::list<std::string>& accids, const GetUserNameCardCallback& cb, const std::string& json_extension = "")
	* 获取本地的指定帐号的用户名片
	* @param[in] accids 
	* @param[in] cb 操作结果回调
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @return void 无返回值
	*/
	static bool GetUserNameCard(const std::list<std::string>& accids, const GetUserNameCardCallback& cb, const std::string& json_extension = "");

	/** @fn static bool GetUserNameCardOnline(const std::list<std::string>& accids, const GetUserNameCardCallback& cb, const std::string& json_extension = "")
	* 在线查询指定帐号的用户名片
	* @param[in] accids 
	* @param[in] cb 操作结果回调
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @return bool 检查参数如果不符合要求则返回失败
	*/
	static bool GetUserNameCardOnline(const std::list<std::string>& accids, const GetUserNameCardCallback& cb, const std::string& json_extension = "");

	/** @fn static bool UpdateUserNameCard(const UserNameCard& namecard, const UpdateUserNameCardCallback& cb, const std::string& json_extension = "")
	* 更新用户名片
	* @param[in] namecard 用户名片内容
	* @param[in] cb 操作结果回调
	* @param[in] json_extension json扩展参数（备用，目前不需要）
	* @return bool 检查参数如果不符合要求则返回失败
	*/
	static bool UpdateUserNameCard(const UserNameCard& namecard, const UpdateUserNameCardCallback& cb, const std::string& json_extension = "");

	/** @fn static bool ParseBlackListInfoChange(const SpecialRelationshipChangeEvent& change_event, BlackListUserNameCard& user_info)
	* 解析黑名单变更通知
	* @param[in] change_event 特殊关系变更通知
	* @param[out] info   解析结果
	* @return bool 解析是否成功
	*/
	static bool ParseBlackListInfoChange(const SpecialRelationshipChangeEvent& change_event, BlackListInfo& info);

	/** @fn static bool ParseMuteListInfoChange(const SpecialRelationshipChangeEvent& change_event, MuteListInfo& user_info)
	* 解析静音名单变更通知
	* @param[in] change_event 特殊关系变更通知
	* @param[out] info   解析结果
	* @return bool 解析是否成功
	*/
	static bool ParseMuteListInfoChange(const SpecialRelationshipChangeEvent& change_event, MuteListInfo& info);

	/** @fn static bool ParseSyncSpecialRelationshipChange(const SpecialRelationshipChangeEvent& change_event, std::list<BlackListInfo>& black_list, std::list<MuteListInfo>& mute_list)
	* 解析多端同步特殊关系通知
	* @param[in] change_event 特殊关系变更通知
	* @param[out] black_list  黑名单列表
	* @param[out] mute_list   静音列表
	* @return bool 解析是否成功
	*/
	static bool ParseSyncSpecialRelationshipChange(const SpecialRelationshipChangeEvent& change_event, std::list<BlackListInfo>& black_list, std::list<MuteListInfo>& mute_list);

};

}

#endif //_NIM_SDK_CPP_USER_H_