/** @file nim_sysmsg_helper.h
  * @brief sysmsg �������������ݽṹ����
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/10/20
  */

#ifndef _NIM_SDK_CPP_SYSMSG_HELPER_H_
#define _NIM_SDK_CPP_SYSMSG_HELPER_H_

#include <string>
#include <list>
#include <functional>
#include "json.h"
#include "nim_common_helper.h"

/**
* @namespace nim
* @brief namespace nim
*/
namespace nim
{

#include "nim_sysmsg_def.h"
#include "nim_msglog_def.h"
#include "nim_res_code_def.h"

/** @struct ϵͳ��Ϣ���Զ���֪ͨ���� */
struct SysMessage
{
	__int64		timetag_;			/**< ֪ͨʱ��������룩 */
	NIMSysMsgType	type_;			/**< ֪ͨ���� */
	std::string	receiver_accid_;	/**< ������ID */
	std::string sender_accid_;		/**< ������ID */
	std::string content_;			/**< ֪ͨ���� */
	std::string	attach_;			/**< ֪ͨ���� */
	__int64		id_;				/**< ֪ͨID */
	BoolStatus	support_offline_;	/**< �Ƿ�֧��������Ϣ*/
	std::string	apns_text_;			/**< ����֪ͨ���� */
	NIMSysMsgStatus	status_;		/**< ֪ͨ״̬ */

	Json::Value push_payload_;		/**< �������Զ�����������ԣ�������������Json������2048 */
	BoolStatus	push_enable_;		/**< �Ƿ���Ҫ����*/
	BoolStatus	push_need_badge_;	/**< �����Ƿ���Ҫ����Ϣ����*/
	BoolStatus	push_need_nick_;	/**< �����Ƿ���Ҫ�ǳ�*/

	NIMResCode	rescode_;			/**< ֪ͨ������ */
	NIMMessageFeature	feature_;	/**< ֪ͨ���� */
	int			total_unread_count_;/**< �ܼƵ�֪ͨδ���� */
	std::string client_msg_id_;		/**< ֪ͨID���ͻ��ˣ� */

	/** ���캯�� */
	SysMessage() : timetag_(0)
		, id_(0)
		, support_offline_(BS_NOT_INIT)
		, total_unread_count_(0)
		, type_(kNIMSysMsgTypeUnknown)
		, status_(kNIMSysMsgStatusNone)
		, feature_(kNIMMessageFeatureDefault) 
		, push_enable_(BS_NOT_INIT)
		, push_need_badge_(BS_NOT_INIT)
		, push_need_nick_(BS_NOT_INIT) {}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string	ToJsonString() const
	{
		Json::Value values;
		values[kNIMSysMsgKeyToAccount] = receiver_accid_;
		values[kNIMSysMsgKeyFromAccount] = sender_accid_;
		values[kNIMSysMsgKeyType] = type_;
		values[kNIMSysMsgKeyAttach] = attach_;
		values[kNIMSysMsgKeyMsg] = content_;
		values[kNIMSysMsgKeyLocalClientMsgId] = client_msg_id_;
		if (support_offline_ != BS_NOT_INIT)
			values[kNIMSysMsgKeyCustomSaveFlag] = support_offline_ == BS_TRUE ? 1 : 0;
		values[kNIMSysMsgKeyCustomApnsText] = apns_text_;
		values[kNIMSysMsgKeyTime] = timetag_;
		values[kNIMSysMsgKeyMsgId] = id_;
		values[kNIMSysMsgKeyLocalStatus] = status_;
		if (push_enable_ != BS_NOT_INIT)
			values[kNIMSysMsgKeyPushEnable] = push_enable_ == BS_TRUE ? 1 : 0;
		if (push_need_nick_ != BS_NOT_INIT)
			values[kNIMSysMsgKeyPushNeedNick] = push_need_nick_ == BS_TRUE ? 1 : 0;
		if (push_need_badge_ != BS_NOT_INIT)
			values[kNIMSysMsgKeyNeedBadge] = push_need_badge_ == BS_TRUE ? 1 : 0;
		if (!push_payload_.empty())
			values[kNIMSysMsgKeyPushPayload] = push_payload_.toStyledString();
		return values.toStyledString();
	}
};

/** @fn bool ParseSysMessage(const std::string& sysmsg_json, SysMessage& msg)
  * @brief ����ϵͳ��Ϣ���Զ���֪ͨ
  * @param[in] sysmsg_json ϵͳ��Ϣ���Զ���֪ͨ(Json Value�����ַ���)
  * @param[out] msg ϵͳ��Ϣ���Զ���֪ͨ
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseSysMessage(const std::string& sysmsg_json, SysMessage& msg);

/** @fn bool ParseSysMessages(const std::string& sysmsgs_json, std::list<SysMessage>& msgs, int* unread)
  * @brief ����ϵͳ��Ϣ���Զ���֪ͨ
  * @param[in] sysmsgs_json ϵͳ��Ϣ���Զ���֪ͨ(Json Value�����ַ���)
  * @param[out] msgs ϵͳ��Ϣ���Զ���֪ͨ
  * @param[out] unread ��ǰ�ܼƵ�δ����
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseSysMessages(const std::string& sysmsgs_json, std::list<SysMessage>& msgs, int* unread);

/** @fn void ParseSysMessageContent(const Json::Value& content_json, SysMessage& msg)
  * @brief ����ϵͳ��Ϣ���Զ���֪ͨ������
  * @param[in] content_json ϵͳ��Ϣ���Զ���֪ͨ������(Json Value����)
  * @param[out] msg ϵͳ��Ϣ���Զ���֪ͨ
  * @return void
  */
void ParseSysMessageContent(const Json::Value& content_json, SysMessage& msg);
} //namespace nim

#endif //_NIM_SDK_CPP_SYSMSG_HELPER_H_