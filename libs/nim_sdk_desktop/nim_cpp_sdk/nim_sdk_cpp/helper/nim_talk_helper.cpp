/** @file nim_talk_helper.cpp
  * @brief Talk �������������ݽṹ����
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/10/16
  */

#include "nim_talk_helper.h"

namespace nim
{

bool ParseMessage(const std::string& msg_json, IMMessage& message)
{
	Json::Value values;
	Json::Reader reader;
	if (reader.parse(msg_json, values) && values.isObject())
	{
		ParseMessage(values, message);
		return true;
	}
	return false;
}

bool ParseReceiveMessage(const std::string& msg_json, IMMessage& message)
{
	Json::Value values;
	Json::Reader reader;
	if (reader.parse(msg_json, values) && values.isObject())
	{
		message.rescode_ = (NIMResCode)values[kNIMMsgKeyLocalRescode].asUInt();
		message.feature_ = (NIMMessageFeature)values[kNIMMsgKeyLocalMsgFeature].asUInt();

		ParseMessage(values[kNIMMsgKeyLocalReceiveMsgContent], message);
		return true;
	}
	
	return false;
}

void ParseMessage(const Json::Value& msg_json, IMMessage& message)
{
	message.session_type_ = (NIMSessionType)msg_json[kNIMMsgKeyToType].asUInt();
	message.receiver_accid_ = msg_json[kNIMMsgKeyToAccount].asString();
	message.sender_accid_ = msg_json[kNIMMsgKeyFromAccount].asString();
	message.readonly_sender_client_type_ = msg_json[kNIMMsgKeyFromClientType].asUInt();
	message.readonly_sender_device_id_ = msg_json[kNIMMsgKeyFromDeviceId].asString();
	message.readonly_sender_nickname_ = msg_json[kNIMMsgKeyFromNick].asString();
	message.timetag_ = msg_json[kNIMMsgKeyTime].asUInt64();

	message.type_ = (NIMMessageType)msg_json[kNIMMsgKeyType].asUInt();
	message.content_ = msg_json[kNIMMsgKeyBody].asString();
	message.attach_ = msg_json[kNIMMsgKeyAttach].asString();
	message.client_msg_id_ = msg_json[kNIMMsgKeyClientMsgid].asString();
	message.readonly_server_id_ = msg_json[kNIMMsgKeyServerMsgid].asUInt64();
	message.resend_flag_ = msg_json[kNIMMsgKeyResendFlag].asInt() > 0;

	message.local_res_path_ = msg_json[kNIMMsgKeyLocalFilePath].asString();
	message.local_talk_id_ = msg_json[kNIMMsgKeyLocalTalkId].asString();
	message.local_res_id_ = msg_json[kNIMMsgKeyLocalResId].asString();
	message.status_ = (NIMMsgLogStatus)msg_json[kNIMMsgKeyLocalLogStatus].asUInt();
	message.sub_status_ = (NIMMsgLogSubStatus)msg_json[kNIMMsgKeyLocalLogSubStatus].asUInt();

	std::string local_ext = msg_json[kNIMMsgKeyLocalExt].asString();
	Json::Reader reader;
	reader.parse(msg_json[kNIMMsgKeyServerExt].asString(), message.server_ext_);
	reader.parse(msg_json[kNIMMsgKeyPushPayload].asString(), message.push_payload_);

	message.local_ext_ = msg_json[kNIMMsgKeyLocalExt].asString();
	message.push_content_ = msg_json[kNIMMsgKeyPushContent].asString();

	message.msg_setting_.ParseMessageSetting(msg_json);
}
}