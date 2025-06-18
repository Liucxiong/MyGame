#ifndef __CARD_ENUMS_H__
#define __CARD_ENUMS_H__

#include <map>
#include <string>


//卡牌的枚举信息定义
namespace card {

    // 花色类型
    enum CardSuitType {
        CST_NONE = -1,  //无类型
        CST_CLUBS = 0,      //梅花
        CST_DIAMONDS,   //方块
		CST_HEARTS,     //红桃
		CST_SPADES,     //黑桃
        CST_NUM_CARD_SUIT_TYPES
    };
    // 点数类型
    enum CardFaceType {
        CFT_NONE = -1,
        CFT_ACE = 0,    //A
        CFT_TWO,        //2
		CFT_THREE,      //3
		CFT_FOUR,       //4
        CFT_FIVE,       //5
        CFT_SIX,        //6
        CFT_SEVEN,      //7
        CFT_EIGHT,      //8
        CFT_NINE,       //9
        CFT_TEN,        //10
        CFT_JACK,       //J
        CFT_QUEEN,      //Q
        CFT_KING,       //K
        CFT_NUM_CARD_FACE_TYPES
    };

    static int totalCardFaceNumer = 13;    //全部卡片数字数量
	static int totalCardSuitNumer = 4;    //全部花色数量

    // 只做 extern 声明，不带初始化！使用at安全访问
    extern const std::map<CardSuitType, std::string> convertCardSuit; //转成形如"K"的字符串
    extern const std::map<CardFaceType, std::string> convertCardFace; //便于转成文件名符号

	extern const std::map<int, CardSuitType> convertIntToCardSuit;  ////数字转emnu
	extern const std::map<int, CardFaceType> convertIntToCardFace;
} // namespace card

#endif // __CARD_ENUMS_H__
