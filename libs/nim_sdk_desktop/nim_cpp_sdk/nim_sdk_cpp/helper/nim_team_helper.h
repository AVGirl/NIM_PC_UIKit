/** @file nim_team_helper.h
  * @brief Team �������������ݽṹ����
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/10/14
  */

#ifndef _NIM_SDK_CPP_TEAM_HELPER_H_
#define _NIM_SDK_CPP_TEAM_HELPER_H_

#include <string>
#include <list>
#include <functional>
#include "json.h"
#include "nim_sdk_helper.h"
#include "nim_user_helper.h"

/**
* @namespace nim
* @brief namespace nim
*/
namespace nim
{

#include "nim_team_def.h"
#include "nim_msglog_def.h"
#include "nim_res_code_def.h"

/** @struct Ⱥ����Ϣ���ݱ��Key,���Ա�Ƕ�Ӧ���ݵ���Ч�� */
enum TeamInfoKey
{
	kTeamInfoKeyNone = 0,					/**< ������ */	
	kTeamInfoKeyName = 1,					/**< Ⱥ������ */
	kTeamInfoKeyType = 1 << 1,				/**< Ⱥ������ */
	kTeamInfoKeyOwnerID = 1 << 2,			/**< Ⱥ��ӵ����ID */
	kTeamInfoKeyLevel = 1 << 3,				/**< Ⱥ��ȼ� */
	kTeamInfoKeyProperty = 1 << 4,			/**< Ⱥ������ */
	kTeamInfoKeyIntro = 1 << 5,				/**< Ⱥ���� */
	kTeamInfoKeyAnnouncement = 1 << 6,		/**< Ⱥ�鹫�� */
	kTeamInfoKeyJoinMode = 1 << 7,			/**< Ⱥ����֤���� */
	kTeamInfoKeyConfigBits = 1 << 8,		/**< Ⱥ�������� */
	kTeamInfoKeyCustom = 1 << 9,			/**< Ⱥ����չ�� */
	kTeamInfoKeyAll = (1 << 10) - 1			/**< ������ */
};

/** @struct Ⱥ����Ϣ */
struct TeamInfo
{
public:
	/** ���캯�����Ƽ�ʹ�� */
	TeamInfo(const std::string& team_id) : member_list_timetag_(0)
		, create_timetag_(0)
		, update_timetag_(0)
		, member_count_(0)
		, config_bits_(0)
		, level_(0)
		, valid_(false)
		, type_(kNIMTeamTypeNormal)
		, member_valid_(false)
		, join_mode_(kNIMTeamJoinModeNoAuth) 
		, value_available_flag_(0)
	{
		id_ = team_id;
	}

	/** ���캯�� */
	TeamInfo() : member_list_timetag_(0)
			, create_timetag_(0)
			, update_timetag_(0)
			, member_count_(0)
			, config_bits_(0)
			, level_(0)
			, valid_(false)
			, type_(kNIMTeamTypeNormal)
			, member_valid_(false)
			, join_mode_(kNIMTeamJoinModeNoAuth) 
			, value_available_flag_(0) {}

public:
	/** ����Ⱥ��ID */
	void SetTeamID(const std::string& id)
	{
		id_ = id;
	}

	/** ��ȡȺ��ID */
	std::string GetTeamID() const
	{
		return id_;
	}

	/** ����Ⱥ������ */
	void SetName(const std::string& name)
	{
		name_ = name;
		value_available_flag_ |= kTeamInfoKeyName;
	}

	/** ��ȡȺ������ */
	std::string GetName() const
	{
		return name_;
	}

	/** ����Ⱥ������ */
	void SetType(nim::NIMTeamType type)
	{
		type_ = type;
		value_available_flag_ |= kTeamInfoKeyType;
	}

	/** ��ȡȺ������ */
	nim::NIMTeamType GetType() const
	{
		return type_;
	}

	/** ����Ⱥ��ӵ����ID */
	void SetOwnerID(const std::string& id)
	{
		owner_id_ = id;
		value_available_flag_ |= kTeamInfoKeyOwnerID;
	}

	/** ��ȡȺ��ӵ����ID */
	std::string GetOwnerID() const
	{
		return owner_id_;
	}

	/** ����Ⱥ��ȼ� */
	void SetLevel(int level)
	{
		level_ = level;
		value_available_flag_ |= kTeamInfoKeyLevel;
	}

	/** ��ȡȺ��ȼ� */
	int GetLevel() const
	{
		return level_;
	}

	/** ����Ⱥ������ */
	void SetProperty(const std::string& prop)
	{
		property_ = prop;
		value_available_flag_ |= kTeamInfoKeyProperty;
	}

	/** ��ȡȺ������ */
	std::string GetProperty() const
	{
		return property_;
	}

	/** ����Ⱥ����Ч�� */
	void SetValid(bool valid)
	{
		valid_ = valid;
	}

	/** ��ȡȺ����Ч�� */
	bool IsValid() const
	{
		return valid_;
	}

	/** ����Ⱥ���Ա���� */
	void SetMemberCount(int count)
	{
		member_count_ = count;
	}

	/** ��ȡȺ���Ա���� */
	int GetMemberCount() const
	{
		return member_count_;
	}

	/** ����Ⱥ���Ա����ʱ���(����) */
	void SetMemberListTimetag(__int64 timetag)
	{
		member_list_timetag_ = timetag;
	}

	/** ��ȡȺ���Ա����ʱ���(����) */
	__int64 GetMemberListTimetag() const
	{
		return member_list_timetag_;
	}

	/** ����Ⱥ�鴴��ʱ���(����) */
	void SetCreateTimetag(__int64 timetag)
	{
		create_timetag_ = timetag;
	}

	/** ��ȡȺ�鴴��ʱ���(����) */
	__int64 GetCreateTimetag() const
	{
		return create_timetag_;
	}

	/** ����Ⱥ�����ʱ���(����) */
	void SetUpdateTimetag(__int64 timetag)
	{
		update_timetag_ = timetag;
	}

	/** ��ȡȺ�����ʱ���(����) */
	__int64 GetUpdateTimetag() const
	{
		return update_timetag_;
	}

	/** ����Ⱥ���Ա��Ч�� */
	void SetMemberValid(bool valid)
	{
		member_valid_ = valid;
	}

	/** ��ȡȺ���Ա��Ч�� */
	bool IsMemberValid() const
	{
		return member_valid_;
	}

	/** ����Ⱥ���� */
	void SetIntro(const std::string& intro)
	{
		intro_ = intro;
		value_available_flag_ |= kTeamInfoKeyIntro;
	}

	/** ��ȡȺ���� */
	std::string GetIntro() const
	{
		return intro_;
	}

	/** ����Ⱥ�鹫�� */
	void SetAnnouncement(const std::string& announcement)
	{
		announcement_ = announcement;
		value_available_flag_ |= kTeamInfoKeyAnnouncement;
	}

	/** ��ȡȺ�鹫�� */
	std::string GetAnnouncement() const
	{
		return announcement_;
	}

	/** ����Ⱥ����֤ģʽ */
	void SetJoinMode(nim::NIMTeamJoinMode mode)
	{
		join_mode_ = mode;
		value_available_flag_ |= kTeamInfoKeyJoinMode;
	}

	/** ��ȡȺ����֤ģʽ */
	nim::NIMTeamJoinMode GetJoinMode() const
	{
		return join_mode_;
	}

	/** ����Ⱥ�������� */
	void SetConfigBits(__int64 bit)
	{
		config_bits_ = bit;
		value_available_flag_ |= kTeamInfoKeyConfigBits;
	}

	/** ��ȡȺ�������� */
	__int64 GetConfigBits() const
	{
		return config_bits_;
	}

	/** ����Ⱥ��ͻ�����չ���� */
	void SetCustom(const std::string& custom)
	{
		custom_ = custom;
		value_available_flag_ |= kTeamInfoKeyCustom;
	}

	/** ��ȡȺ��ͻ�����չ���� */
	std::string GetCustom() const
	{
		return custom_;
	}

	/** ����Ⱥ�����������չ���� */
	void SetServerCustom(const std::string& custom)
	{
		server_custom_ = custom;
	}

	/** ��ȡȺ�����������չ���� */
	std::string GetServerCustom() const
	{
		return server_custom_;
	}

	/** @fn bool ExistValue(TeamInfoKey value_key) const
	  * @brief Ⱥ����Ϣ���ݱ��Key��Ӧ�������Ƿ���Ч�����ڣ��ǳ�ʼֵ״̬��
	  * @param[in] value_key Ⱥ����Ϣ���ݱ��Key
	  * @return bool ��Ч�� 
	  */
	bool ExistValue(TeamInfoKey value_key) const
	{
		return (value_available_flag_ & value_key) != 0;
	}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString() const
	{
		Json::Value json;
		json[nim::kNIMTeamInfoKeyID] = id_;
		if (ExistValue(nim::kTeamInfoKeyName))
			json[nim::kNIMTeamInfoKeyName] = name_;
		if (ExistValue(nim::kTeamInfoKeyType))
			json[nim::kNIMTeamInfoKeyType] = (unsigned int)type_;
		if (ExistValue(nim::kTeamInfoKeyOwnerID))
			json[nim::kNIMTeamInfoKeyCreator] = owner_id_;
		if (ExistValue(nim::kTeamInfoKeyLevel))
			json[nim::kNIMTeamInfoKeyLevel] = level_;
		if (ExistValue(nim::kTeamInfoKeyProperty))
			json[nim::kNIMTeamInfoKeyProperty] = property_;
		json[nim::kNIMTeamInfoKeyValidFlag] = valid_ ? 1 : 0;
		if (member_count_ > 0)
			json[nim::kNIMTeamInfoKeyMemberCount] = member_count_;
		if (member_list_timetag_ > 0)
			json[nim::kNIMTeamInfoKeyListTime] = member_list_timetag_;
		if (create_timetag_ > 0)
			json[nim::kNIMTeamInfoKeyCreateTime] = create_timetag_;
		if (update_timetag_ > 0)
			json[nim::kNIMTeamInfoKeyUpdateTime] = update_timetag_;
		json[nim::kNIMTeamInfoKeyMemberValid] = member_valid_ ? 1 : 0;
		if (ExistValue(nim::kTeamInfoKeyIntro))
			json[nim::kNIMTeamInfoKeyIntro] = intro_;
		if (ExistValue(nim::kTeamInfoKeyAnnouncement))
			json[nim::kNIMTeamInfoKeyAnnouncement] = announcement_;
		if (ExistValue(nim::kTeamInfoKeyJoinMode))
			json[nim::kNIMTeamInfoKeyJoinMode] = (unsigned int)join_mode_;
		if (ExistValue(nim::kTeamInfoKeyConfigBits))
			json[nim::kNIMTeamInfoKeyBits] = config_bits_;
		if (ExistValue(nim::kTeamInfoKeyCustom))
			json[nim::kNIMTeamInfoKeyCustom] = custom_;
		json[nim::kNIMTeamInfoKeyServerCustom] = server_custom_;

		return json.toStyledString();
	}

private:
	std::string		id_;
	bool			valid_;
	int				member_count_;
	__int64			member_list_timetag_;
	__int64			create_timetag_;
	__int64			update_timetag_;
	std::string		server_custom_;

private:
	std::string		name_;
	nim::NIMTeamType	type_;
	std::string		owner_id_;
	int				level_;
	std::string		property_;
	bool			member_valid_;
	std::string		intro_;
	std::string		announcement_;
	nim::NIMTeamJoinMode join_mode_;
	__int64			config_bits_;
	std::string		custom_;

	unsigned int	value_available_flag_;
};

/** @struct Ⱥ��Ա��Ϣ���ݱ��Key,���Ա�Ƕ�Ӧ���ݵ���Ч�� */
enum TeamMemberValueKey
{
	kTeamMemberPropertyKeyNone = 0,				/**< ������ */
	kTeamMemberPropertyKeyUserType = 1,			/**< Ⱥ��Ա���� */
	kTeamMemberPropertyKeyNickName = 1 << 1,	/**< Ⱥ��Ա�ǳ� */
	kTeamMemberPropertyKeyBits = 1 << 2,		/**< Ⱥ��Ա������ */
	kTeamMemberPropertyKeyValid = 1 << 3,		/**< Ⱥ��Ա��Ч�� */
	kTeamMemberPropertyKeyAll = (1 << 4) - 1	/**< ������ */
};

/** @struct Ⱥ���Ա��Ϣ */
struct TeamMemberProperty
{
public:
	/** ���캯�����Ƽ�ʹ�� */
	TeamMemberProperty(const std::string& team_id, const std::string& accid) : type_(kNIMTeamUserTypeNomal), valid_(false), bits_(0), create_timetag_(0), update_timetag_(0), value_available_flag_(0)
	{
		team_id_ = team_id;
		account_id_ = accid;
	}

	/** ���캯�� */
	TeamMemberProperty() : type_(kNIMTeamUserTypeNomal), valid_(false), bits_(0), create_timetag_(0), update_timetag_(0), value_available_flag_(0) {}

public:
	/** ����Ⱥ��ID */
	void SetTeamID(const std::string& id)
	{
		team_id_ = id;
	}

	/** ��ȡȺ��ID */
	std::string GetTeamID() const
	{
		return team_id_;
	}

	/** ����Ⱥ��ԱID */
	void SetAccountID(const std::string& id)
	{
		account_id_ = id;
	}

	/** ��ȡȺ��ԱID */
	std::string GetAccountID() const
	{
		return account_id_;
	}

	/** ����Ⱥ��Ա���� */
	void SetUserType(nim::NIMTeamUserType type)
	{
		type_ = type;
		value_available_flag_ |= kTeamMemberPropertyKeyUserType;
	}

	/** ��ȡȺ��Ա���� */
	nim::NIMTeamUserType GetUserType() const
	{
		return type_;
	}

	/** ����Ⱥ��Ա�ǳ� */
	void SetNick(const std::string& nick)
	{
		nick_ = nick;
		value_available_flag_ |= kTeamMemberPropertyKeyNickName;
	}

	/** ��ȡȺ��Ա�ǳ� */
	std::string GetNick() const
	{
		return nick_;
	}

	/** ����Ⱥ��Ա������ */
	void SetBits(__int64 bit)
	{
		bits_ = bit;
		value_available_flag_ |= kTeamMemberPropertyKeyBits;
	}

	/** ��ȡȺ��Ա������ */
	__int64 GetBits() const
	{
		return bits_;
	}

	/** ����Ⱥ��Ա��Ч�� */
	void SetValid_(bool valid)
	{
		valid_ = valid;
		value_available_flag_ |= kTeamMemberPropertyKeyValid;
	}

	/** ��ȡȺ��Ա��Ч�� */
	bool IsValid() const
	{
		return valid_;
	}

	/** ����Ⱥ��Ա����ʱ���(����) */
	void SetCreateTimetag(__int64 timetag)
	{
		create_timetag_ = timetag;
	}

	/** ��ȡȺ��Ա����ʱ���(����) */
	__int64 GetCreateTimetag() const
	{
		return create_timetag_;
	}

	/** ����Ⱥ��Ա����ʱ���(����) */
	void SetUpdateTimetag(__int64 timetag)
	{
		update_timetag_ = timetag;
	}

	/** ��ȡȺ��Ա����ʱ���(����) */
	__int64 GetUpdateTimetag() const
	{
		return update_timetag_;
	}

	/** @fn bool ExistValue(TeamMemberValueKey value_key) const
	  * @brief Ⱥ��Ա��Ϣ��Ϣ���ݱ��Key��Ӧ�������Ƿ���Ч�����ڣ��ǳ�ʼֵ״̬��
	  * @param[in] value_key Ⱥ��Ա��Ϣ���ݱ��Key
	  * @return bool ��Ч�� 
	  */
	bool ExistValue(TeamMemberValueKey value_key) const
	{
		return (value_available_flag_ & value_key) != 0;
	}

	/** @fn std::string ToJsonString() const
	  * @brief ��װJson Value�ַ���
	  * @return string Json Value�ַ��� 
      */
	std::string ToJsonString() const
	{
		Json::Value json;
		json[nim::kNIMTeamUserKeyID] = team_id_;
		json[nim::kNIMTeamUserKeyAccID] = account_id_;
		if (ExistValue(nim::kTeamMemberPropertyKeyUserType))
			json[nim::kNIMTeamUserKeyType] = (unsigned int)type_;
		if (ExistValue(nim::kTeamMemberPropertyKeyNickName))
			json[nim::kNIMTeamUserKeyNick] = nick_;
		if (ExistValue(nim::kTeamMemberPropertyKeyBits))
			json[nim::kNIMTeamUserKeyBits] = bits_;
		if (ExistValue(nim::kTeamMemberPropertyKeyValid))
			json[nim::kNIMTeamUserKeyValidFlag] = valid_ ? 1 : 0;
		if (create_timetag_ > 0)
			json[nim::kNIMTeamUserKeyCreateTime] = create_timetag_;
		if (update_timetag_ > 0)
			json[nim::kNIMTeamUserKeyUpdateTime] = update_timetag_;

		return json.toStyledString();
	}

private:
	bool			valid_;
	__int64			create_timetag_;
	__int64			update_timetag_;

private:
	std::string		team_id_;
	std::string		account_id_;
	nim::NIMTeamUserType type_;
	std::string		nick_;
	__int64			bits_;

	unsigned int	value_available_flag_;
};

/** @struct Ⱥ���¼�֪ͨ */
struct TeamEvent
{
	NIMResCode res_code_;					/**< ������ */
	NIMNotificationId notification_id_;		/**< ֪ͨ����ID */
	std::string team_id_;					/**< Ⱥ��ID */
	std::list<std::string> ids_;			/**< ֪ͨ�����漰����Ⱥ��ԱID */
	std::list<UserNameCard> namecards_;		/**< ֪ͨ�����漰����Ⱥ��Ա���û���Ƭ */
	TeamInfo	team_info_;					/**< ֪ͨ�����漰����Ⱥ��Ϣ */
};

/** @fn void ParseTeamEvent(int rescode, const std::string& team_id, const NIMNotificationId notification_id, const std::string& team_event_json, TeamEvent& team_event)
  * @brief ����Ⱥ���¼�֪ͨ
  * @param[in] rescode ������
  * @param[in] team_id Ⱥ��ID
  * @param[in] notification_id ֪ͨ����ID
  * @param[in] team_event_json ֪ͨ���ݣ�Json Value���ݣ�
  * @param[out] team_event Ⱥ���¼�֪ͨ
  * @return void 
  */
void ParseTeamEvent(int rescode, const std::string& team_id, const NIMNotificationId notification_id, const std::string& team_event_json, TeamEvent& team_event);

/** @fn ParseTeamInfoJson(const Json::Value& team_info_json, TeamInfo& team_info)
  * @brief ����Ⱥ����Ϣ
  * @param[in] team_info_json Ⱥ����Ϣ��Json Value���ݣ�
  * @param[out] team_info Ⱥ����Ϣ
  * @return void 
  */
void ParseTeamInfoJson(const Json::Value& team_info_json, TeamInfo& team_info);

/** @fn ParseTeamInfoJson(const std::string& team_info_json, TeamInfo& team_info)
  * @brief ����Ⱥ����Ϣ
  * @param[in] team_info_json Ⱥ����Ϣ��Json Value�����ַ�����
  * @param[out] team_info Ⱥ����Ϣ
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseTeamInfoJson(const std::string& team_info_json, TeamInfo& team_info);

/** @fn const std::string& team_infos_json, bool include_invalid_team, std::list<TeamInfo>& team_infos
  * @brief ����Ⱥ����Ϣ
  * @param[in] team_info_json Ⱥ����Ϣ��Json Value�����ַ�����
  * @param[in] include_invalid_team �Ƿ������ЧȺ�飨����Ⱥ��
  * @param[out] team_infos Ⱥ����Ϣ
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseTeamInfosJson(const std::string& team_infos_json, bool include_invalid_team, std::list<TeamInfo>& team_infos);

/** @fn void ParseTeamMemberPropertyJson(const Json::Value& team_member_prop_json, TeamMemberProperty& team_member_property)
  * @brief ����Ⱥ��Ա��Ϣ
  * @param[in] team_member_prop_json Ⱥ��Ա��Ϣ��Json Value���ݣ�
  * @param[out] team_member_property Ⱥ��Ա��Ϣ
  * @return void 
  */
void ParseTeamMemberPropertyJson(const Json::Value& team_member_prop_json, TeamMemberProperty& team_member_property);

/** @fn bool ParseTeamMemberPropertyJson(const std::string& team_member_prop_json, TeamMemberProperty& team_member_property)
  * @brief ����Ⱥ��Ա��Ϣ
  * @param[in] team_member_prop_json Ⱥ��Ա��Ϣ��Json Value�����ַ�����
  * @param[out] team_member_property Ⱥ��Ա��Ϣ
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseTeamMemberPropertyJson(const std::string& team_member_prop_json, TeamMemberProperty& team_member_property);

/** @fn bool ParseTeamMemberPropertysJson(const std::string& team_member_props_json, std::list<TeamMemberProperty>& team_member_propertys)
  * @brief ����Ⱥ��Ա��Ϣ
  * @param[in] team_member_props_json Ⱥ��Ա��Ϣ��Json Value�����ַ�����
  * @param[out] team_member_propertys Ⱥ��Ա��Ϣ
  * @return bool �����ɹ���ʧ�� 
  */
bool ParseTeamMemberPropertysJson(const std::string& team_member_props_json, std::list<TeamMemberProperty>& team_member_propertys);
}//namespace nim

#endif //_NIM_SDK_CPP_TEAM_HELPER_H_