/** @file nim_common_helper.h
  * @brief SDK��������
  * @copyright (c) 2015, NetEase Inc. All rights reserved
  * @author Oleg
  * @date 2015/09/08
  */

#ifndef _NIM_SDK_CPP_COMMON_HELPER_H_
#define _NIM_SDK_CPP_COMMON_HELPER_H_

#include <string>
#include <list>
#include "assert.h"
#include "json.h"

/**
* @namespace nim
* @brief namespace nim
*/
namespace nim
{
/** @enum �Զ���Ĳ���ֵ�������ݵ������������ */
enum BoolStatus
{
	BS_NOT_INIT = -1,	/**< δ��ʼ�� */
	BS_FALSE	= 0,	/**< false */
	BS_TRUE		= 1		/**< true */
};

/** @fn bool StrListToJsonString(const std::list<std::string>& list, std::string& out)
  * @brief ��һ��string���͵�list��װ��һ��Json Array
  * @param[in] list string���͵�list
  * @param[out] out Json Array
  * @return bool �ɹ� ��ʧ��
  */
bool StrListToJsonString(const std::list<std::string>& list, std::string& out);

/** @fn bool JsonStrArrayToList(const Json::Value& array_str, std::list<std::string>& out)
  * @brief ��һ��string���͵�Json Array������һ��string���͵�list
  * @param[in] array_str string���͵�Json Array
  * @param[out] out string���͵�list
  * @return bool �����ɹ� ��ʧ��
  */
bool JsonStrArrayToList(const Json::Value& array_str, std::list<std::string>& out);

/** @fn std::string PCharToString(const char* str)
  * @brief �ַ�ָ��תΪ�ַ������ӿ��ڲ����nullpty�����ж�
  * @param[in] str �ַ�ָ��
  * @return string �ַ���
  */
std::string PCharToString(const char* str);

}

#endif //_NIM_SDK_CPP_COMMON_HELPER_H_