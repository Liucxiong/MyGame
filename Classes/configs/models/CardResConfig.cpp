#include "CardResConfig.h"

namespace card {

    // 在这里**定义并初始化**
    const std::map<CardSuitType, std::string> convertCardSuit = {
        { CST_CLUBS,    "club"    },
        { CST_DIAMONDS, "diamond" },
        { CST_HEARTS,   "heart"   },
        { CST_SPADES,   "spade"   }
    };

    const std::map<CardFaceType, std::string> convertCardFace = {
        { CFT_ACE,   "A"  },
        { CFT_TWO,   "2"  },
        { CFT_THREE, "3"  },
        { CFT_FOUR,  "4"  },
        { CFT_FIVE,  "5"  },
        { CFT_SIX,   "6"  },
        { CFT_SEVEN, "7"  },
        { CFT_EIGHT, "8"  },
        { CFT_NINE,  "9"  },
        { CFT_TEN,   "10" },
        { CFT_JACK,  "J"  },
        { CFT_QUEEN, "Q"  },
        { CFT_KING,  "K"  }
    };
	//将int值转成CardSuitType类型
    const std::map<int, card::CardSuitType> convertIntToCardSuit = {
        { 0, CST_CLUBS    },
        { 1, CST_DIAMONDS },
        { 2, CST_HEARTS   },
        { 3, CST_SPADES   }
	};
	//将int值转成CardFaceType类型
    const std::map<int, card::CardFaceType> convertIntToCardFace = {
        { 0, CFT_ACE   },
        { 1, CFT_TWO   },
        { 2, CFT_THREE },
        { 3, CFT_FOUR  },
        { 4, CFT_FIVE  },
        { 5, CFT_SIX   },
        { 6, CFT_SEVEN },
        { 7, CFT_EIGHT },
        { 8, CFT_NINE  },
        { 9, CFT_TEN   },
        { 10, CFT_JACK  },
        { 11, CFT_QUEEN },
        { 12, CFT_KING  }
	};

} // namespace card
