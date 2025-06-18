#ifndef __CARD_ENUMS_H__
#define __CARD_ENUMS_H__

#include <map>
#include <string>


//���Ƶ�ö����Ϣ����
namespace card {

    // ��ɫ����
    enum CardSuitType {
        CST_NONE = -1,  //������
        CST_CLUBS = 0,      //÷��
        CST_DIAMONDS,   //����
		CST_HEARTS,     //����
		CST_SPADES,     //����
        CST_NUM_CARD_SUIT_TYPES
    };
    // ��������
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

    static int totalCardFaceNumer = 13;    //ȫ����Ƭ��������
	static int totalCardSuitNumer = 4;    //ȫ����ɫ����

    // ֻ�� extern ������������ʼ����ʹ��at��ȫ����
    extern const std::map<CardSuitType, std::string> convertCardSuit; //ת������"K"���ַ���
    extern const std::map<CardFaceType, std::string> convertCardFace; //����ת���ļ�������

	extern const std::map<int, CardSuitType> convertIntToCardSuit;  ////����תemnu
	extern const std::map<int, CardFaceType> convertIntToCardFace;
} // namespace card

#endif // __CARD_ENUMS_H__
