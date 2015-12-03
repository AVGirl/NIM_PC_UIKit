/** @file nim_sysmsg_helper.cpp
  * @brief sysmsg �������������ݽṹ����
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/10/20
  */

#include "assert.h"
#include "nim_sysmsg_helper.h"

namespace nim
{

bool ParseSysMessage(const std::string& sysmsg_json, SysMessage& msg)
{
	Json::Value values;
	Json::Reader reader;
	if (reader.parse(sysmsg_json, values) && values.isObject())
	{
		msg.rescode_ = (NIMResCode)values[kNIMSysMsgKeyLocalRescode].asUInt();
		msg.feature_ = (NIMMessageFeature)values[kNIMSysMsgKeyLocalFeature].asUInt();
		msg.total_unread_count_ = values[kNIMSysMsgKeyLocalUnreadCount].asUInt();

		Json::Value content = values[kNIMSysMsgKeyLocalContent];
		ParseSysMessageContent(content, msg);

		return true;
	}

	return false;
}

bool ParseSysMessages(const std::string& sysmsgs_json, std::list<SysMessage>& msgs, int* unread)
{
	Json::Value values;
	Json::Reader reader;
	if (reader.parse(sysmsgs_json, values) && values.isObject())
	{
		*unread = values[kNIMSysMsglogQueryKeyUnreadCount].asUInt();
		Json::Value content = values[kNIMSysMsglogQueryKeyContent];
		int len = content.size();
		for (int i = 0; i < len; i++)
		{
			SysMessage msg;
			ParseSysMessageContent(content[i], msg);
			msgs.push_back(msg);
		}
		return true;
	}

	return false;
}

void ParseSysMessageContent(const Json::Value& content_json, SysMessage& msg)
{
	msg.timetag_ = content_json[kNIMSysMsgKeyTime].asUInt64();
	msg.type_ = (NIMSysMsgType)content_json[kNIMSysMsgKeyType].asUInt();
	msg.receiver_accid_ = content_json[kNIMSysMsgKeyToAccount].asString();
	msg.sender_accid_ = content_json[kNIMSysMsgKeyFromAccount].asString();
	msg.content_ = content_json[kNIMSysMsgKeyMsg].asString();
	msg.attach_ = content_json[kNIMSysMsgKeyAttach].asString();
	msg.id_ = content_json[kNIMSysMsgKeyMsgId].asUInt64();
	if (content_json[kNIMSysMsgKeyCustomSaveFlag].isUInt())
		msg.support_offline_ = content_json[kNIMSysMsgKeyCustomSaveFlag].asInt() == 1 ? BS_TRUE : BS_FALSE;
	msg.apns_text_ = content_json[kNIMSysMsgKeyCustomApnsText].asString();
	msg.status_ = (NIMSysMsgStatus)content_json[kNIMSysMsgKeyLocalStatus].asUInt();
	if (content_json[kNIMSysMsgKeyPushEnable].isUInt())
		msg.push_enable_ = content_json[kNIMSysMsgKeyPushEnable].asInt() == 1 ? BS_TRUE : BS_FALSE;
	if (content_json[kNIMSysMsgKeyNeedBadge].isUInt())
		msg.push_need_badge_ = content_json[kNIMSysMsgKeyNeedBadge].asInt() == 1 ? BS_TRUE : BS_FALSE;
	if (content_json[kNIMSysMsgKeyPushNeedNick].isUInt())
		msg.push_need_nick_ = content_json[kNIMSysMsgKeyPushNeedNick].asInt() == 1 ? BS_TRUE : BS_FALSE;
	Json::Reader reader;
	std::string payload = content_json[kNIMSysMsgKeyPushPayload].asString();
	if (!payload.empty() && (!reader.parse(payload, msg.push_payload_) || !msg.push_payload_.isObject()))
		assert(0);
}

}