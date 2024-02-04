#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

std::unordered_set<std::string> profileHints = {
    "GJ_myLevelsTxt_001.png",
    "GJ_myListsTxt_001.png",
    "GJ_stuffTxt_001.png",
    "GJ_followTxt_001.png",
    "GJ_youtubeTxt_001.png",
    "GJ_twitterTxt_001.png",
    "GJ_twitchTxt_001.png"
};

std::unordered_set<std::string> headerSprites = {
    "featuredLabel_001.png",
	"topListsLabel_001.png"
};

class $modify(LevelSelectLayer) {
	bool init(int p0) {
		if (!LevelSelectLayer::init(p0)) return false;
        if (!Mod::get()->getSettingValue<bool>("enabled")) return true;
		if (!Mod::get()->getSettingValue<bool>("hideLevelSelectJunk")) return true;
		getChildOfType<CCMenu>(this, 0)->setScale(0);
		getChildOfType<GJGroundLayer>(this, 0)->setScale(0);
		typeinfo_cast<CCSpriteBatchNode*>(getChildOfType<BoomScrollLayer>(this, 0)->getChildren()->objectAtIndex(1))->setVisible(false);
		return true;
	}
};

class $modify(LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) return false;
        if (!(Mod::get()->getSettingValue<bool>("enabled"))) return true;
		if (Mod::get()->getSettingValue<bool>("hideClearSearch"))
			typeinfo_cast<CCMenuItemSpriteExtra*>(getChildOfType<CCMenu>(this, 1)->getChildren()->objectAtIndex(2))->setScale(0); // hide clear search
		return true;
	}
};

class $modify(CCSprite) {
	static CCSprite* createWithSpriteFrameName(char const* frameName) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(frameName);
        if (!(Mod::get()->getSettingValue<bool>("enabled"))) return sprite;
        if (profileHints.find(frameName) != profileHints.end() && Mod::get()->getSettingValue<bool>("hideProfileHints"))
            sprite->setScale(0); // hide profile hints
		if (headerSprites.find(frameName) != headerSprites.end() && Mod::get()->getSettingValue<bool>("hideHeaderSprites"))
            sprite->setScale(0); // hide header sprites
        return sprite;
    }
};

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
        if (!(Mod::get()->getSettingValue<bool>("enabled"))) return true;
		if (Mod::get()->getSettingValue<bool>("hideNG")) this->getChildByIDRecursive("newgrounds-button")->setScale(0); // hideNG
		if (Mod::get()->getSettingValue<bool>("hideAchievements")) this->getChildByIDRecursive("achievements-button")->setScale(0); // hideAchievements
		if (Mod::get()->getSettingValue<bool>("hideStats")) this->getChildByIDRecursive("stats-button")->setScale(0); // hideStats
		return true;
	}
};
