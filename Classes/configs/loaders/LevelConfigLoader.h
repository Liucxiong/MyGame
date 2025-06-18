#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

//���ùؿ����ݼ��ط�ʽ����json�ļ�����
#include "json/document.h"
#include "json/filereadstream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "cocos2d.h"
#include "../../models/CardModel.h"
#include <vector>
#include <cstdio>

/// <summary>
/// ��JSON�ļ��м��عؿ���������
/// </summary> 
/// <param name="filename">�ļ���</param>
/// <param name="key">ȡJSON�ĸ��ֶΣ�PlayfieldΪ���棬StackΪ������</param>
/// <returns> CardModel*���ɵ�vector,Ĭ�Ͼ��ɵ��true </returns>
std::vector<CardModel*> loadCardsFromJson(const std::string& filename, const std::string& key);


#endif