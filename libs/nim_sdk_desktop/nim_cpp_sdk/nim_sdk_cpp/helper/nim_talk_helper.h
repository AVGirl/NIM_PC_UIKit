/** @file nim_talk_helper.h
  * @brief Talk �������������ݽṹ����
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/10/16
  */

#ifndef _NIM_SDK_CPP_TALK_HELPER_H_
#define _NIM_SDK_CPP_TALK_HELPER_H_

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

#include "nim_talk_def.h"
#include "nim_session_def.h"
#include "nim_msglog_def.h"
#include "nim_res_code_def.h"

/** @struct ��Ϣ�������� */
struct MessageSetting
{
	BoolStatus server_history_saved_;	/**< ����Ϣ�Ƿ�洢�ƶ���ʷ */
	BoolStatus roaming_;				/**< ����Ϣ�Ƿ�֧������ */
	BoolStatus self_sync_;				/**< ����Ϣ�Ƿ�֧�ַ����߶��ͬ�� */
	BoolStatus persist_enable_;			/**< ��Ϣ�Ƿ�Ҫ������ */
	BoolStatus be_muted_;				/**< ����Ϣ�Ƿ��ڽ��շ����������� */
	BoolStatus need_push_; 				/**< �Ƿ���Ҫ���� */
	BoolStatus push_need_badge_;		/**< �Ƿ�Ҫ����Ϣ���� */
	BoolStatus push_need_nick_;			/**< ��Ҫ�����ǳ� */

	/** ���캯�� */
	MessageSetting() : server_history_saved_(BS_NOT_INIT)
		, roaming_(BS_NOT_INIT)
		, self_sync_(BS_NOT_INIT)
		, persist_enable_(BS_NOT_INIT)
		, be_muted_(BS_NOT_INIT)
		, need_push_(BS_NOT_INIT)
		, push_need_badge_(BS_NOT_INIT)
		, push_need_nick_(BS_NOT_INIT) {}

	/** @fn void ToJsonValue(Json::Value& message) const
	  * @brief ��װJson Value�ַ���
	  * @param[out] message ��ϢJson
	  * @return void
      */
	void ToJsonValue(Json::Value& message) const
	{
		if (server_history_saved_ != BS_NOT_INIT)
			message[kNIMMsgKeyHistorySave] = server_history_saved_== BS_TRUE;
		if (roaming_ != BS_NOT_INIT)
			message[kNIMMsgKeyMsgRoaming] = roaming_== BS_TRUE;
		if (self_sync_ != BS_NOT_INIT)
			message[kNIMMsgKeyMsgSync] = self_sync_== BS_TRUE;
		if (push_need_badge_ != BS_NOT_INIT)
			message[kNIMMsgKeyNeedBadge] = push_need_badge_== BS_TRUE;
		if (need_push_ != BS_NOT_INIT)
			message[kNIMMsgKeyPushEnable] = need_push_== BS_TRUE;
		if (push_need_nick_ != BS_NOT_INIT)
			message[kNIMMsgKeyNeedPushNick] = push_need_nick_== BS_TRUE;
	}

	/** @fn void ParseMessageSetting(const Json::Value& message)
	  * @brief ��Json Value��������Ϣ��������
	  * @param[in] message ��ϢJson
	  * @return void
      */
	void ParseMessageSetting(const Json::Value& message)
	{
		if (message.isMember(kNIMMsgKeyHistorySave))
			server_history_saved_ = (BoolStatus)message[kNIMMsgKeyHistorySave].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyMsgRoaming))
			roaming_ = (BoolStatus)message[kNIMMsgKeyMsgRoaming].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyMsgSync))
			self_sync_ = (BoolStatus)message[kNIMMsgKeyMsgSync].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyNeedBadge))
			push_need_badge_ = (BoolStatus)message[kNIMMsgKeyNeedBadge].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyPushEnable))
			need_push_ = (BoolStatus)message[kNIMMsgKeyPushEnable].asInt() == 1 ? BS_TRUE : BS_FALSE;
		if (message.isMember(kNIMMsgKeyNeedPushNick))
			push_need_nick_ = (BoolStatus)message[kNIMMsgKeyNeedPushNick].asInt() == 1 ? BS_TRUE : BS_FALSE;
	}
};

/** @struct P2P��Ⱥ����Ϣ */
struct IMMessage
{
public:
	NIMResCode	rescode_;						/**< ������ */
	NIMMessageFeature	feature_;				/**< ��Ϣ���� */

public:
	NIMSessionType	session_type_;				/**< �Ự���� */
	std::string		receiver_accid_;			/**< ������ID */
	std::string		sender_accid_;				/**< ������ID */
	__int64			timetag_;					/**< ��Ϣʱ��������룩 */
	std::string		content_;					/**< ��Ϣ���� */
	NIMMessageType	type_;						/**< ��Ϣ���� */
	std::string		attach_;					/**< ��Ϣ���� */
	std::string		client_msg_id_;				/**< ��ϢID���ͻ��ˣ� */
	bool			resend_flag_;				/**< �ط���� */
	Json::Value		push_payload_;				/**< �������Զ�����������ԣ����ݸ�ʽ����ΪJson String������2048 */
	std::string		push_content_;				/**< �Զ��������İ�����������200�ֽ� */
	Json::Value		server_ext_;				/**< ��������չ�ֶ�, ���ݸ�ʽ����ΪJson String����������1024 */
	std::string		local_ext_;					/**< ������չ�ֶ�, ��ʽ���� */
	MessageSetting	msg_setting_;				/**< ��Ϣ�������� */

public:
	std::string	   local_res_path_;				/**< ý���ļ����ؾ���·�����ͻ��ˣ� */
	std::string	   local_talk_id_;				/**< �ỰID���ͻ��ˣ� */
	std::string	   local_res_id_;				/**< ý���ļ�ID���ͻ��ˣ� */
	NIMMsgLogStatus	status_;					/**< ��Ϣ״̬���ͻ��ˣ� */
	NIMMsgLogSubStatus	sub_status_;			/**< ��Ϣ��״̬���ͻ��ˣ� */

public:
	int			   readonly_sender_client_type_;	/**< �����߿ͻ������ͣ�ֻ���� */
	std::string	   readonly_sender_device_id_;		/**< �����߿ͻ����豸ID��ֻ���� */
	std::string	   readonly_sender_nickname_;		/**< �������ǳƣ�ֻ���� */
	__int64		   readonly_server_id_;				/**< ��ϢID����������ֻ���� */

	/** ���캯�� */
	IMMessage() : resend_flag_(false)
				, readonly_sender_client_type_(0) 
				, readonly_server_id_(0)
				, feature_(kNIMMessageFeatureDefault)
				, session_type_(kNIMSessionTypeP2P)
				, timetag_(0)
				, status_(nim::kNIMMsgLogStatusNone)
				, sub_status_(nim::kNIMMsgLogSubStatusNone) {}

	/** ���캯�� */
	IMMessage(const std::string &json_msg) : resend_flag_(false)
		, readonly_sender_client_type_(0) 
		, readonly_server_id_(0)
		, feature_(kNIMMessageFeatureDefault)
		, session_type_(kNIMSessionTypeP2P)
		, timetag_(0)
		, status_(nim::kNIMMsgLogStatusNone)
		, sub_status_(nim::kNIMMsgLogSubStatusNone) 
	{
		Json::Value values;
		Json::Reader reader;
		if (reader.parse(json_msg, values) && values.isObject())
		{
			session_type_ = (NIMSessionType)values[kNIMMsgKeyToType].asUInt();
			receiver_accid_ = values[kNIMMsgKeyToAccount].asString();
			sender_accid_ = values[kNIMMsgKeyFromAccount].asString();
			readonly_sender_client_type_ = values[kNIMMsgKeyFromClientType].asUInt();
			readonly_sender_device_id_ = values[kNIMMsgKeyFromDeviceId].asString();
			readonly_sender_nickname_ = values[kNIMMsgKeyFromNick].asString();
			timetag_ = values[kNIMMsgKeyTime].asUInt64();

			type_ = (NIMMessageType)values[kNIMMsgKeyType].asUInt();
			content_ = values[kNIMMsgKeyBody].asString();
			attach_ = values[kNIMMsgKeyAttach].asString();
			client_msg_id_ = values[kNIMMsgKeyClientMsgid].asString();
			readonly_server_id_ = values[kNIMMsgKeyServerMsgid].asUInt64();
			resend_flag_ = values[kNIMMsgKeyResendFlag].asUInt() > 0;

			local_res_path_ = values[kNIMMsgKeyLocalFilePath].asString();
			local_talk_id_ = values[kNIMMsgKeyLocalTalkId].asString();
			local_res_id_ = values[kNIMMsgKeyLocalResId].asString();
			status_ = (NIMMsgLogStatus)values[kNIMMsgKeyLocalLogStatus].asUInt();
			sub_status_ = (NIMMsgLogSubStatus)values[kNIMMsgKeyLocalLogSubStatus].asUInt();

			if (!reader.parse(values[kNIMMsgKeyLocalExt].asString(), server_ext_) || !server_ext_.isObject())
				assert(0);
			if (!reader.parse(values[kNIMMsgKeyPushPayload].asString(), push_payload_) || !push_payload_.isObject())
				assert(0);
			local_ext_ = values[kNIMMsgKeyLocalExt].asString();
			push_content_ = values[kNIMMsgKeyPushContent].asString();

			msg_setting_.ParseMessageSetting(values);
		}
	}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string		ToJsonString(bool use_to_send) const
	{
		Json::Value values;
		values[kNIMMsgKeyToType] = session_type_;
		values[kNIMMsgKeyToAccount] = receiver_accid_;
		values[kNIMMsgKeyFromAccount] = sender_accid_;
		values[kNIMMsgKeyTime] = timetag_;
		values[kNIMMsgKeyType] = type_;
		values[kNIMMsgKeyBody] = content_;
		values[kNIMMsgKeyAttach] = attach_;
		values[kNIMMsgKeyClientMsgid] = client_msg_id_;
		values[kNIMMsgKeyResendFlag] = resend_flag_ ? 1 : 0;
		values[kNIMMsgKeyLocalFilePath] = local_res_path_;
		values[kNIMMsgKeyLocalTalkId] = receiver_accid_;
		values[kNIMMsgKeyLocalResId] = local_res_id_;
		values[kNIMMsgKeyLocalLogStatus] = status_;
		values[kNIMMsgKeyLocalLogSubStatus] = sub_status_;
		values[kNIMMsgKeyLocalExt] = local_ext_;
		if (!server_ext_.empty())
			values[kNIMMsgKeyServerExt] = server_ext_.toStyledString();
		values[kNIMMsgKeyPushContent] = push_content_;
		if (!push_payload_.empty())
			values[kNIMMsgKeyPushPayload] = push_payload_.toStyledString();

		msg_setting_.ToJsonValue(values);

		if (!use_to_send)
		{
			values[kNIMMsgKeyFromClientType] = readonly_sender_client_type_;
			values[kNIMMsgKeyFromDeviceId] = readonly_sender_device_id_;
			values[kNIMMsgKeyFromNick] = readonly_sender_nickname_;
			values[kNIMMsgKeyServerMsgid] = readonly_server_id_;
		}
		return values.toStyledString();
	}
};

/** @struct �ļ���Ϣ���� */
struct IMFile
{
	std::string	md5_;				/**< �ļ�����MD5 */
	__int64		size_;				/**< �ļ���С */
	std::string url_;				/**< �ϴ��ƶ˺�õ����ļ����ص�ַ */
	std::string display_name_;		/**< ������ʾ���ļ����� */
	std::string file_extension_;	/**< �ļ���չ�� */

	/** ���캯�� */
	IMFile() : size_(0) {}

	/** @fn std::string ToJsonString(Json::Value &attach) const
	  * @brief ��װJson Value�ַ���
	  * @param[in] attach Json Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString(Json::Value &attach) const
	{
		//���¿ͻ��˿���ѡ��
		if (!display_name_.empty())
			attach[kNIMFileMsgKeyDisplayName] = display_name_;
		if (!file_extension_.empty())
			attach[kNIMFileMsgKeyExt] = file_extension_;
		if (!md5_.empty())
			attach[kNIMFileMsgKeyMd5] = md5_;
		if (size_ > 0)
			attach[kNIMFileMsgKeySize] = size_;

		return attach.toStyledString();
	}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMFileMsgKeyDisplayName] = display_name_;

		return ToJsonString(attach);
	}
};

/** @struct ͼƬ��Ϣ���� */
struct IMImage : IMFile
{
	int			width_;			/**< ͼƬ��� */
	int			height_;		/**< ͼƬ�߶� */

	/** ���캯�� */
	IMImage() : width_(0), height_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMImgMsgKeyWidth] = width_;
		attach[kNIMImgMsgKeyHeight] = height_;
		attach[kNIMImgMsgKeyDisplayName] = display_name_;

		return __super::ToJsonString(attach);
	}
};

/** @struct λ����Ϣ���� */
struct IMLocation
{
	std::string	description_;		/**< λ���������� */
	double		latitude_;			/**< λ��γ�� */
	double		longitude_;			/**< λ�þ��� */

	/** ���캯�� */
	IMLocation() : latitude_(0), longitude_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMLocationMsgKeyTitle] = description_;
		attach[kNIMLocationMsgKeyLatitude] = latitude_;
		attach[kNIMLocationMsgKeyLongitude] = longitude_;

		return attach.toStyledString();
	}
};

/** @struct ������Ϣ���� */
struct IMAudio : IMFile
{
	int			duration_;			/**< ����ʱ�� */

	/** ���캯�� */
	IMAudio() : duration_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMAudioMsgKeyDisplayName] = display_name_;

		return __super::ToJsonString(attach);
	}
};

/** @struct С��Ƶ��Ϣ���� */
struct IMVideo : IMFile
{
	int			duration_;			/**< ��Ƶʱ�� */
	int			width_;				/**< ��Ƶ������ */
	int			height_;			/**< ��Ƶ����߶� */

	/** ���캯�� */
	IMVideo() : duration_(0), width_(0), height_(0) {}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString() const
	{
		Json::Value attach;
		attach[kNIMVideoMsgKeyWidth] = width_;
		attach[kNIMVideoMsgKeyHeight] = height_;
		attach[kNIMVideoMsgKeyDuration] = duration_;

		return __super::ToJsonString(attach);
	}
};

/** @fn bool ParseMessage(const std::string& msg_json, IMMessage& message)
  * @brief ������Ϣ
  * @param[in] msg_json ��Ϣ(Json Value�����ַ���)
  * @param[out] message ��Ϣ
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseMessage(const std::string& msg_json, IMMessage& message);

/** @fn bool ParseReceiveMessage(const std::string& msg_json, IMMessage& message)
  * @brief ������Ϣ
  * @param[in] msg_json ��Ϣ(Json Value�����ַ���)
  * @param[out] message ��Ϣ
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseReceiveMessage(const std::string& msg_json, IMMessage& message);

/** @fn void ParseReceiveMessage(const Json::Value& msg_json, IMMessage& message)
  * @brief ������Ϣ
  * @param[in] msg_json ��Ϣ(Json Value����)
  * @param[out] message ��Ϣ
  * @return void 
  */
void ParseMessage(const Json::Value& msg_json, IMMessage& message);

} //namespace nim

#endif //_NIM_SDK_CPP_TALK_HELPER_H_