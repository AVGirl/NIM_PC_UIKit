#include "nim_team_helper.h"

namespace nim
{

void ParseTeamEvent(int rescode, const std::string& team_id, const NIMNotificationId notification_id, const std::string& team_event_json, TeamEvent& team_event)
{
	team_event.res_code_ = (NIMResCode)rescode;
	team_event.team_id_ = team_id;
	team_event.notification_id_ = notification_id;
	switch (notification_id)
	{
	case kNIMNotificationIdTeamInvite:
	case kNIMNotificationIdTeamKick:
	case kNIMNotificationIdTeamAddManager:
	case kNIMNotificationIdTeamRemoveManager:
	case kNIMNotificationIdLocalCreateTeam:
		{
			//ids
			Json::Reader reader;
			Json::Value values;
			if (reader.parse(team_event_json, values) && values.isObject())
			{
				Json::Value ids = values[kNIMNotificationKeyData][kNIMNotificationKeyDataIds];
				int len = ids.size();
				for (int i = 0; i < len; i++)
				{
					team_event.ids_.push_back(ids[i].asString());
				}
			}
		}
		break;
	case kNIMNotificationIdTeamLeave:
	case kNIMNotificationIdTeamApplyPass:
	case kNIMNotificationIdTeamInviteAccept:
	case kNIMNotificationIdLocalRejectApply:
	case kNIMNotificationIdLocalRejectInvite:
		{
			//id
			Json::Reader reader;
			Json::Value values;
			if (reader.parse(team_event_json, values) && values.isObject())
			{
				team_event.ids_.push_back(values[kNIMNotificationKeyData][kNIMNotificationKeyDataId].asString());
			}
		}
		break;
	case kNIMNotificationIdTeamUpdate:
	case kNIMNotificationIdTeamSyncCreate:
	case kNIMNotificationIdLocalGetTeamInfo:
		{
			//info
			Json::Reader reader;
			Json::Value values;
			if (reader.parse(team_event_json, values) && values.isObject())
			{
				ParseTeamInfoJson(values[kNIMNotificationKeyData][kNIMNotificationKeyTeamInfo], team_event.team_info_);
			}
		}
		break;
	case kNIMNotificationIdTeamDismiss:
	case kNIMNotificationIdLocalApplyTeam:
	case kNIMNotificationIdLocalUpdateOtherNick:
	case kNIMNotificationIdLocalGetTeamList:
		{
			//��
			//��������Ҫ����
		}
		break;
	case kNIMNotificationIdTeamOwnerTransfer:
		{
			//id bool
			//�������Ƿ��뿪Ⱥ�飬�ϲ��յ�֪ͨ������ýӿ��ж��Ƿ�Ҫ�뿪
			Json::Reader reader;
			Json::Value values;
			if (reader.parse(team_event_json, values) && values.isObject())
			{
				team_event.ids_.push_back(values[kNIMNotificationKeyData][kNIMNotificationKeyDataId].asString());
			}
		}
		break;
	case kNIMNotificationIdTeamMemberChanged:
		{
			//team member property
			//����id���ϲ��յ�֪ͨ����ýӿ���ȡteam member property
			Json::Reader reader;
			Json::Value values;
			if (reader.parse(team_event_json, values) && values.isObject())
			{
				team_event.ids_.push_back(values[kNIMNotificationKeyData][kNIMNotificationKeyTeamMember][kNIMTeamUserKeyAccID].asString());
			}
		}
		break;
	case kNIMNotificationIdTeamSyncUpdateTlist:
	case kNIMNotificationIdLocalUpdateTlist:
		{
			//member
			//���������ϲ��յ�֪ͨ������ýӿ���ȡteam_member_property
		}
		break;
	default:
		break;
	}
}


void ParseTeamInfoJson(const Json::Value& team_info_json, TeamInfo& team_info)
{
	team_info.SetType((nim::NIMTeamType)(team_info_json[nim::kNIMTeamInfoKeyType].asInt()));
	team_info.SetTeamID(team_info_json[nim::kNIMTeamInfoKeyID].asString());
	team_info.SetOwnerID(team_info_json[nim::kNIMTeamInfoKeyCreator].asString());
	team_info.SetName(team_info_json[nim::kNIMTeamInfoKeyName].asString());
	team_info.SetIntro(team_info_json[nim::kNIMTeamInfoKeyIntro].asString());
	team_info.SetAnnouncement(team_info_json[nim::kNIMTeamInfoKeyAnnouncement].asString());
	team_info.SetJoinMode((NIMTeamJoinMode)(team_info_json[nim::kNIMTeamInfoKeyJoinMode].asInt()));
	team_info.SetServerCustom(team_info_json[nim::kNIMTeamInfoKeyServerCustom].asString());
	team_info.SetCreateTimetag(team_info_json[nim::kNIMTeamInfoKeyCreateTime].asUInt64());
	team_info.SetUpdateTimetag(team_info_json[nim::kNIMTeamInfoKeyUpdateTime].asUInt64());
	team_info.SetCustom(team_info_json[nim::kNIMTeamInfoKeyCustom].asString());
	team_info.SetMemberCount(team_info_json[nim::kNIMTeamInfoKeyMemberCount].asUInt());
	team_info.SetProperty(team_info_json[nim::kNIMTeamInfoKeyProperty].asString());
	team_info.SetValid(team_info_json[nim::kNIMTeamInfoKeyValidFlag].asUInt() == 0 ? false : true);
	team_info.SetConfigBits(team_info_json[nim::kNIMTeamInfoKeyBits].asUInt64());
	team_info.SetMemberValid(team_info_json[nim::kNIMTeamInfoKeyMemberValid].asUInt() == 0 ? false : true);
}

bool ParseTeamInfoJson(const std::string& team_info_json, TeamInfo& team_info)
{
	Json::Value json;
	Json::Reader reader;
	if (reader.parse(team_info_json, json) && json.isObject())
	{
		ParseTeamInfoJson(json, team_info);
		return true;
	}
	
	return false;
}

bool ParseTeamInfosJson(const std::string& team_infos_json, bool include_invalid_team, std::list<TeamInfo>& team_infos)
{
	Json::Value json;
	Json::Reader reader;
	if (reader.parse(team_infos_json, json) && json.isArray())
	{
		int len = json.size();
		for (int i = 0; i < len; i++)
		{
			TeamInfo info;
			ParseTeamInfoJson(json[i], info);
			if (info.IsValid() || (!info.IsValid() && include_invalid_team))
				team_infos.push_back(info);
		}
		return true;
	}

	return false;
}

void ParseTeamMemberPropertyJson(const Json::Value& team_member_prop_json, TeamMemberProperty& team_member_property)
{
	team_member_property.SetUserType((nim::NIMTeamUserType)team_member_prop_json[nim::kNIMTeamUserKeyType].asInt());
	if (team_member_property.GetUserType() != nim::kNIMTeamUserTypeApply && team_member_property.GetUserType() != nim::kNIMTeamUserTypeLocalWaitAccept)
	{
		team_member_property.SetAccountID(team_member_prop_json[nim::kNIMTeamUserKeyAccID].asString());
		team_member_property.SetNick(team_member_prop_json[nim::kNIMTeamUserKeyNick].asString());
		team_member_property.SetBits(team_member_prop_json[nim::kNIMTeamUserKeyBits].asUInt64());
		team_member_property.SetCreateTimetag(team_member_prop_json[nim::kNIMTeamUserKeyCreateTime].asUInt64());
		team_member_property.SetUpdateTimetag(team_member_prop_json[nim::kNIMTeamUserKeyUpdateTime].asUInt64());
		team_member_property.SetTeamID(team_member_prop_json[nim::kNIMTeamUserKeyID].asString());
		team_member_property.SetValid_(team_member_prop_json[nim::kNIMTeamUserKeyValidFlag].asUInt() == 0 ? false : true);
	}
}

bool ParseTeamMemberPropertyJson(const std::string& team_member_prop_json, TeamMemberProperty& team_member_property)
{
	Json::Value json;
	Json::Reader reader;
	if (reader.parse(team_member_prop_json, json) && json.isObject())
	{
		ParseTeamMemberPropertyJson(json, team_member_property);
		return true;
	}

	return false;
}

bool ParseTeamMemberPropertysJson(const std::string& team_member_props_json, std::list<TeamMemberProperty>& team_member_propertys)
{
	Json::Value json;
	Json::Reader reader;
	if (reader.parse(team_member_props_json, json) && json.isArray())
	{
		int len = json.size();
		for (int i = 0; i < len; i++)
		{
			TeamMemberProperty prop;
			ParseTeamMemberPropertyJson(json[i], prop);
			team_member_propertys.push_back(prop);
		}
		return true;
	}
	return false;
}

}