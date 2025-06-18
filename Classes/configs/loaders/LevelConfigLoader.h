#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

//配置关卡数据加载方式，从json文件加载
#include "json/document.h"
#include "json/filereadstream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "cocos2d.h"
#include "../../models/CardModel.h"
#include <vector>
#include <cstdio>

/// <summary>
/// 从JSON文件中加载关卡配置数据
/// </summary> 
/// <param name="filename">文件名</param>
/// <param name="key">取JSON哪个字段，Playfield为桌面，Stack为手牌区</param>
/// <returns> CardModel*构成的vector,默认均可点击true </returns>
std::vector<CardModel*> loadCardsFromJson(const std::string& filename, const std::string& key);


#endif