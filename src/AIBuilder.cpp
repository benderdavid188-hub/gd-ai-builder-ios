#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/binding/Level.hpp>
#include <Geode/binding/GameObject.hpp>
#include <Geode/utils/web.hpp>
#include <vector>
#include <string>
#include <json.hpp>

using json = nlohmann::json;

$on_mod(Loaded) {
  Mod::get()->logInfo("AI Builder iOS loaded!");
}

class AIBuilderUI : public cocos2d::CCLayer {
public:
  static AIBuilderUI* create() {
    auto pRet = new AIBuilderUI();
    if (pRet && pRet->init()) {
      pRet->autorelease();
      return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
  }

  bool init() {
    if (!CCLayer::init()) return false;

    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    
    auto bg = cocos2d::CCLayerColor::create(ccc4(0, 0, 0, 200));
    this->addChild(bg);

    auto size = cocos2d::CCSizeMake(320, 400);
    auto container = cocos2d::CCLayer::create();
    container->setPosition(winSize.width / 2 - 160, winSize.height / 2 - 200);
    this->addChild(container);

    auto titleLabel = cocos2d::CCLabelBMFont::create("AI SUGGESTIONS", "bigFont.fnt");
    titleLabel->setScale(0.6f);
    titleLabel->setPosition(160, 370);
    container->addChild(titleLabel);

    auto suggestionBG = cocos2d::CCLayerColor::create(ccc4(30, 30, 30, 255), 300, 250);
    suggestionBG->setPosition(10, 80);
    container->addChild(suggestionBG);

    m_suggestionLabel = cocos2d::CCLabelBMFont::create("Click 'Get Suggestion'", "bigFont.fnt");
    m_suggestionLabel->setScale(0.4f);
    m_suggestionLabel->setPosition(150, 200);
    suggestionBG->addChild(m_suggestionLabel);

    auto getSuggestionBtn = cocos2d::CCMenuItemImage::create(
      "GJ_button_01.png", "GJ_button_02.png", this, menu_selector(AIBuilderUI::onGetSuggestion));
    getSuggestionBtn->setScale(0.7f);
    getSuggestionBtn->setPosition(80, 30);

    auto acceptBtn = cocos2d::CCMenuItemImage::create(
      "GJ_button_01.png", "GJ_button_02.png", this, menu_selector(AIBuilderUI::onAccept));
    acceptBtn->setScale(0.6f);
    acceptBtn->setPosition(160, 30);

    auto denyBtn = cocos2d::CCMenuItemImage::create(
      "GJ_button_01.png", "GJ_button_02.png", this, menu_selector(AIBuilderUI::onDeny));
    denyBtn->setScale(0.6f);
    denyBtn->setPosition(240, 30);

    auto menu = cocos2d::CCMenu::create(getSuggestionBtn, acceptBtn, denyBtn, nullptr);
    menu->setPosition(0, 0);
    container->addChild(menu);

    auto closeBtn = cocos2d::CCMenuItemImage::create(
      "GJ_button_01.png", "GJ_button_02.png", this, menu_selector(AIBuilderUI::onClose));
    closeBtn->setScale(0.5f);
    closeBtn->setPosition(310, 370);
    auto closeMenu = cocos2d::CCMenu::create(closeBtn, nullptr);
    closeMenu->setPosition(0, 0);
    container->addChild(closeMenu);

    return true;
  }

  void onGetSuggestion(cocos2d::CCObject* pSender) {
    auto editorLayer = LevelEditorLayer::get();
    if (!editorLayer) return;
    auto level = editorLayer->m_level;
    if (!level) return;
    std::string levelData = level->m_levelString;
    fetchAISuggestion(levelData);
  }

  void onAccept(cocos2d::CCObject* pSender) {
    if (m_currentSuggestion.isEmpty()) return;
    m_suggestionLabel->setString("Suggestion accepted!");
  }

  void onDeny(cocos2d::CCObject* pSender) {
    m_currentSuggestion = "";
    m_suggestionLabel->setString("Suggestion denied. Get a new one!");
  }

  void onClose(cocos2d::CCObject* pSender) {
    this->removeFromParent();
  }

private:
  cocos2d::CCLabelBMFont* m_suggestionLabel = nullptr;
  std::string m_currentSuggestion = "";

  void fetchAISuggestion(const std::string& levelData) {
    std::string prompt = "You are a Geometry Dash level designer. Suggest decoration or mechanics for this level. Respond with JSON.";
    
    web::WebTask(web::WebRequest(
      "https://text.pollinations.ai/",
      web::RequestMethod::Post
    )).text([this](std::string response) {
      m_currentSuggestion = response;
      m_suggestionLabel->setString(response.substr(0, 100).c_str());
    }).error([this](std::string error) {
      m_suggestionLabel->setString("Error fetching suggestion");
    });
  }
};

class $modify(EditorUI) {
  bool init(LevelEditorLayer* editorLayer) {
    if (!EditorUI::init(editorLayer)) return false;
    return true;
  }
};