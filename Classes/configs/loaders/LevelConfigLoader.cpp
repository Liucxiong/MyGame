#include "LevelConfigLoader.h"
#include "../models/CardResConfig.h"

USING_NS_CC;

std::vector<CardModel*> loadCardsFromJson(const std::string& filename, const std::string& key) {
    std::vector<CardModel*> cards;

    std::string path = FileUtils::getInstance()->fullPathForFilename(filename);
    std::string fileContent = FileUtils::getInstance()->getStringFromFile(path);

    rapidjson::Document doc;
    doc.Parse(fileContent.c_str());

    if (!doc.IsObject() || !doc.HasMember(key.c_str()) || !doc[key.c_str()].IsArray()) {
        CCLOG("JSON format error or missing key: %s", key.c_str());
        return cards;
    }

    const rapidjson::Value& cardArray = doc[key.c_str()];
    for (rapidjson::SizeType i = 0; i < cardArray.Size(); ++i) {
        const auto& cardObj = cardArray[i];
        if (cardObj.HasMember("CardFace") &&
            cardObj.HasMember("CardSuit") &&
            cardObj.HasMember("Position")) {

			int face = cardObj["CardFace"].GetInt();
            int suit = cardObj["CardSuit"].GetInt();
            const auto& pos = cardObj["Position"];
			Vec2 position(pos["x"].GetFloat(), pos["y"].GetFloat());
            
            CardModel* acard = new CardModel(card::convertIntToCardSuit.at(suit), card::convertIntToCardFace.at(face), true,i, position);

            cards.push_back(acard);
        }
    }

    return cards;
}