﻿#include "stdafx.h"
#include "PlayerInfoPanel.h"
#include "Rectangle.h"
#include "UI.h"
#include "Champion.h"
#include "ItemshopPanel.h"
// Control
#include "Label.h"
#include "OutlinedSlot.h"
#include "Button.h"

PlayerInfoPanel* pPlayerInfoPanel = nullptr;

PlayerInfoPanel::PlayerInfoPanel()
{
    screenW = MainGame::GetWidth();
    screenH = MainGame::GetHeight();

// this
    Texture* mainPanelTex = RenderManager::GetTexture(L"panel (5)");
    this->SetLocation((screenW * 0.5f) - mainPanelTex->GetSpriteWidth() * 0.5f, (float)(screenH - mainPanelTex->GetSpriteHeight()));

// StatPanel
    statPanel = AddChild<UI>(L"statPanel", new UI(L"stat_panel (5)_icon", Vector2(-293, 21)));
    statLabel[0] = statPanel->AddChild<Label>(L"stat1", new Label(18));
    statLabel[1] = statPanel->AddChild<Label>(L"stat2", new Label(18));
    statLabel[2] = statPanel->AddChild<Label>(L"stat3", new Label(18));
    statLabel[3] = statPanel->AddChild<Label>(L"stat4", new Label(18));
    statLabel[4] = statPanel->AddChild<Label>(L"stat5", new Label(18));
    statLabel[5] = statPanel->AddChild<Label>(L"stat6", new Label(18));
    statLabel[6] = statPanel->AddChild<Label>(L"stat7", new Label(18));
    statLabel[7] = statPanel->AddChild<Label>(L"stat8", new Label(18));
    int statstartx = 45;
    int statstarty = 31;
    int statinvx = 105;
    int statinvy = 33;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 2; ++x) {
            int index = x + y * 2;

            statLabel[index]->SetText(0);
            statLabel[index]->SetLocation(Vector2(statstartx + statinvx * x, statstarty + statinvy * y));
            statLabel[index]->align = Label::Align::Left;
            statLabel[index]->valign = Label::VAlign::Middle;
            statLabel[index]->foreColor = D3DCOLOR_ARGB(255, 255, 255, 255);
        }
    }

// InvenPanel
    invenPanel = AddChild<UI>(L"invenPanel", new UI(L"panel (2)", Vector2(558, 6)));
    invenPanel->AddChild<OutlinedSlot>(L"wardSlot", new OutlinedSlot(L"border_skill (5)", Vector2(176, 30)));
    invenPanel->AddChild<OutlinedSlot>(L"recallSlot", new OutlinedSlot(L"border_skill (6)", Vector2(176, 82)));
    auto itemshopBtn = invenPanel->AddChild<Button>(L"itemsshopBtn", new Button(L"button_gold (2)", Vector2(16, 130)));
    itemshopBtn->SetTextureDisable(L"button_gold (1)");
    itemshopBtn->SetTextureHover(L"button_gold (3)");
    itemshopBtn->SetTexturePressed(L"button_gold (4)");
    itemshopBtn->Click += Engine::Handler(&ItemshopPanel::ToggleVisible);

	Label* Item1Label = invenPanel->AddChild<Label>(L"Item1Label", new Label(15));
    Item1Label->SetText(1);
    Item1Label->SetLocation(Vector2(16, 68));
    Item1Label->foreColor = D3DCOLOR_ARGB(255, 255, 255, 255);
    Item1Label->align = Label::Align::Center;
    Item1Label->valign = Label::VAlign::Middle;

	Label* Item2Label = invenPanel->AddChild<Label>(L"Item2Label", new Label(15));
	Item2Label->SetText(2);
	Item2Label->SetLocation(Vector2(68, 68));
	Item2Label->foreColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	Item2Label->align = Label::Align::Center;
	Item2Label->valign = Label::VAlign::Middle;

	Label* Item3Label = invenPanel->AddChild<Label>(L"Item3Label", new Label(15));
	Item3Label->SetText(3);
	Item3Label->SetLocation(Vector2(120, 68));
	Item3Label->foreColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	Item3Label->align = Label::Align::Center;
	Item3Label->valign = Label::VAlign::Middle;

	Label* Item5Label = invenPanel->AddChild<Label>(L"Item5Label", new Label(15));
	Item5Label->SetText(5);
	Item5Label->SetLocation(Vector2(16, 120));
	Item5Label->foreColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	Item5Label->align = Label::Align::Center;
	Item5Label->valign = Label::VAlign::Middle;

	Label* Item6Label = invenPanel->AddChild<Label>(L"Item6Label", new Label(15));
	Item6Label->SetText(6);
	Item6Label->SetLocation(Vector2(68, 120));
	Item6Label->foreColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	Item6Label->align = Label::Align::Center;
	Item6Label->valign = Label::VAlign::Middle;

	Label* Item7Label = invenPanel->AddChild<Label>(L"Item7Label", new Label(15));
	Item7Label->SetText(7);
	Item7Label->SetLocation(Vector2(120, 120));
	Item7Label->foreColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	Item7Label->align = Label::Align::Center;
	Item7Label->valign = Label::VAlign::Middle;


	Label* Item4Label = invenPanel->AddChild<Label>(L"Item4Label", new Label(15));
	Item4Label->SetText(4);
	Item4Label->SetLocation(Vector2(180, 60));
	Item4Label->foreColor = D3DCOLOR_ARGB(255, 244, 214, 108);
	Item4Label->align = Label::Align::Center;
	Item4Label->valign = Label::VAlign::Middle;

	Label* RecallLabel = invenPanel->AddChild<Label>(L"RecallLabel", new Label(15));
	RecallLabel->SetText(L"B");
	RecallLabel->SetLocation(Vector2(180, 111));
	RecallLabel->foreColor = D3DCOLOR_ARGB(255, 244, 214, 108);
	RecallLabel->align = Label::Align::Center;
	RecallLabel->valign = Label::VAlign::Middle;

// mainPanel
    mainPanel = AddChild<UI>(L"mainPanel", new UI(L"panel (5)", Vector2(0, 0)));
    auto HPBar = mainPanel->AddChild<UI>(L"HPBar", new UI(L"bar_big1", Vector2(74, 123)));
    auto MPBar = mainPanel->AddChild<UI>(L"MPBar", new UI(L"bar_big2", Vector2(74, 143)));
    mainPanel->AddChild<UI>(L"HPBarTipL", new UI(L"bar_tip (1)", Vector2(71, 123)));
    mainPanel->AddChild<UI>(L"HPBarTipR", new UI(L"bar_tip (2)", Vector2(534, 123)));
    mainPanel->AddChild<UI>(L"MPBarTipL", new UI(L"bar_tip (1)", Vector2(71, 143)));
    mainPanel->AddChild<UI>(L"MPBarTipR", new UI(L"bar_tip (2)", Vector2(534, 143)));

    slotSpell1    = mainPanel->AddChild<OutlinedSlot>(L"Spell1",  new OutlinedSlot(L"border_skill (1)", Vector2(125, 30)));
    slotSpell2    = mainPanel->AddChild<OutlinedSlot>(L"Spell2",  new OutlinedSlot(L"border_skill (1)", Vector2(199, 30)));
    slotSpell3    = mainPanel->AddChild<OutlinedSlot>(L"Spell3",  new OutlinedSlot(L"border_skill (1)", Vector2(273, 30)));
    slotSpell4    = mainPanel->AddChild<OutlinedSlot>(L"Spell4",  new OutlinedSlot(L"border_skill (1)", Vector2(347, 30)));
    slotPassive   = mainPanel->AddChild<OutlinedSlot>(L"SpellP",  new OutlinedSlot(L"border_skill (2)", Vector2(69,  30)));
    slotSummoner1 = mainPanel->AddChild<OutlinedSlot>(L"SpellS1", new OutlinedSlot(L"border_skill (2)", Vector2(432, 30)));
    slotSummoner2 = mainPanel->AddChild<OutlinedSlot>(L"SpellS2", new OutlinedSlot(L"border_skill (2)", Vector2(488, 30)));
    slotPassive->icon->transform->scale = { 0.71f, 0.71f, 0 };
    slotSummoner1->icon->transform->scale = { 0.71f, 0.71f, 0 };
    slotSummoner2->icon->transform->scale = { 0.71f, 0.71f, 0 };

	Label* QLabel = mainPanel->AddChild<Label>(L"QLabel", new Label(15));
	Label* WLabel = mainPanel->AddChild<Label>(L"WLabel", new Label(15));
	Label* ELabel = mainPanel->AddChild<Label>(L"ELabel", new Label(15));
	Label* RLabel = mainPanel->AddChild<Label>(L"RLabel", new Label(15));
	Label* DLabel = mainPanel->AddChild<Label>(L"DLabel", new Label(15));
	Label* FLabel = mainPanel->AddChild<Label>(L"FLabel", new Label(15));
	QLabel->SetLocation(Vector2(129, 96));
	WLabel->SetLocation(Vector2(203, 96));
	ELabel->SetLocation(Vector2(277, 96));
	RLabel->SetLocation(Vector2(351, 96));
	DLabel->SetLocation(Vector2(436, 78));
	FLabel->SetLocation(Vector2(492, 78));
	QLabel->SetText(L"Q");
	WLabel->SetText(L"W");
	ELabel->SetText(L"E");
	RLabel->SetText(L"R");
	DLabel->SetText(L"D");
	FLabel->SetText(L"F");
	QLabel->align = Label::Align::Center;
	WLabel->align = Label::Align::Center;
	ELabel->align = Label::Align::Center;
	RLabel->align = Label::Align::Center;
	DLabel->align = Label::Align::Center;
	FLabel->align = Label::Align::Center;
	QLabel->valign = Label::VAlign::Middle;
	WLabel->valign = Label::VAlign::Middle;
	ELabel->valign = Label::VAlign::Middle;
	RLabel->valign = Label::VAlign::Middle;
	DLabel->valign = Label::VAlign::Middle;
	FLabel->valign = Label::VAlign::Middle;
    QLabel->foreColor = D3DCOLOR_ARGB(255, 231, 203, 102);
	WLabel->foreColor = D3DCOLOR_ARGB(255, 231, 203, 102);
	ELabel->foreColor = D3DCOLOR_ARGB(255, 231, 203, 102);
	RLabel->foreColor = D3DCOLOR_ARGB(255, 231, 203, 102);
	DLabel->foreColor = D3DCOLOR_ARGB(255, 231, 203, 102);
	FLabel->foreColor = D3DCOLOR_ARGB(255, 231, 203, 102);
	QLabel->outline = true;
	WLabel->outline = true;
	ELabel->outline = true;
	RLabel->outline = true;
	DLabel->outline = true;
	FLabel->outline = true;

    facePanel = mainPanel->AddChild<UI>(L"champFace", new UI(Vector2(-80, 30)));
    mainPanel->AddChild<UI>(L"expBar", new UI(L"bar_exp", Vector2(14, 21)));
    auto champBorder = mainPanel->AddChild<UI>(L"champBorder", new UI(L"panel (1)", Vector2(-93, 11)));
    level = champBorder->AddChild<Label>(L"level", new Label(15));
    level->SetText(L"1");
    level->SetLocation(112, 137);
    level->align = Label::Align::Center;
    level->valign = Label::VAlign::Middle;
    mainPanel->AddChild<UI>(L"statBtnBorder", new UI(L"stat_panel (4)", Vector2(-107, 86)));
    Button* statBtn1 = mainPanel->AddChild<Button>(L"statBtn1", new Button(L"stat_panel (1)", Vector2(-100, 92)));
    Button* statBtn2 = mainPanel->AddChild<Button>(L"statBtn2", new Button(L"stat_panel (2)", Vector2(-88, 114)));
    Button* statBtn3 = mainPanel->AddChild<Button>(L"statBtn3", new Button(L"stat_panel (3)", Vector2(-57, 131)));
    statBtn1->SetTextureHover(L"stat_panel (1)_hover");
    statBtn1->SetTexturePressed(L"stat_panel (1)_pressed");
    statBtn1->Click += Engine::Handler(this, &PlayerInfoPanel::PlayerPanel_OnClick);
}

PlayerInfoPanel::~PlayerInfoPanel()
{
}

PlayerInfoPanel* PlayerInfoPanel::GetInstance()
{
    if (pPlayerInfoPanel == nullptr)
    {
        pPlayerInfoPanel = new PlayerInfoPanel();
    }
    return pPlayerInfoPanel;
}

void PlayerInfoPanel::DestroyInstance()
{
    if (pPlayerInfoPanel)
    {
        delete pPlayerInfoPanel;
        pPlayerInfoPanel = nullptr;
    }
}

void PlayerInfoPanel::Initialize()
{
}

void PlayerInfoPanel::Release()
{
}

void PlayerInfoPanel::Update()
{
    //if (Input::GetKeyDown(VK_UP))
    //{
    //    barTipOffset1.y -= 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}
    //if (Input::GetKeyDown(VK_DOWN))
    //{
    //    barTipOffset1.y += 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}
    //if (Input::GetKeyDown(VK_LEFT))
    //{
    //    barTipOffset1.x -= 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}
    //if (Input::GetKeyDown(VK_RIGHT))
    //{
    //    barTipOffset1.x += 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}

    GameObject::Update();
    //mainPanel->Update();
    //invenPanel->Update();
    //faceBorder->Update();
    //facePanel->Update();
    //statPanel->Update();
    //
    //hpLabel->Update();
    //mpLabel->Update();
    //
    //slotSpell1->Update();
    //slotSpell2->Update();
    //slotSpell3->Update();
    //slotSpell4->Update();
    //slotPassive->Update();
    //slotSummoner1->Update();
    //slotSummoner2->Update();
    //
    //for (int i = 0; i < 8; i++)
    //{
    //    statLabel[i]->Update();
    //}
}
//
//void PlayerInfoPanel::Render()
//{
//    
//
//    GameObject::Render();
//    RenderStat();
//    miniPanel->Render();
//    
//    mainPanel->Render();
//    invenPanel->Render();
//    
//
//    if (champion != nullptr)
//    {
//        facePanel->Render();
//        RenderBar();
//        slotSpell1->Render();
//        slotSpell2->Render();
//        slotSpell3->Render();
//        slotSpell4->Render();
//        slotPassive->Render();
//        slotSummoner1->Render();
//        slotSummoner2->Render();
//    }
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset1, 0);
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset2, 0);
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset3, 0);
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset4, 0);
//
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset4, 0);
//
//    faceBorder->Render();
//}
//
//void PlayerInfoPanel::RenderStat()
//{
//    statPanel->Render();
//
//    Vector3 offset = { 15,15,0 };
//    int iconSize = 20;
//    int padding = 15;
//    Vector3 labelPos[8];
//
//    RenderManager::DrawUI(L"stat_icon (7)", statPanelPos +offset, 0);
//    labelPos[0] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (11)", statPanelPos + offset, 0);
//    labelPos[1] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (13)", statPanelPos + offset, 0);
//    labelPos[2] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (1)", statPanelPos + offset, 0);
//    labelPos[3] = statPanelPos + offset;
//    offset.x = 110;
//    offset.y = 15;
//    RenderManager::DrawUI(L"stat_icon (8)", statPanelPos + offset, 0);
//    labelPos[4] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (12)", statPanelPos + offset, 0);
//    labelPos[5] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (16)", statPanelPos + offset, 0);
//    labelPos[6] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (3)", statPanelPos + offset, 0);
//    labelPos[7] = statPanelPos + offset;
//
//    WCHAR wstr[32] = {};
//    if (champion != nullptr)
//    {
//        
//        _itow_s((int)champion->GetAttackDamage(), wstr, 10);
//        statLabel[0]->text = wstr;
//        _itow_s((int)champion->GetArmor(), wstr, 10);
//        statLabel[1]->text = wstr;
//        swprintf_s(wstr, L"%.02f", champion->GetAttackPerSec());
//        statLabel[2]->text = wstr;
//        _itow_s((int)champion->GetCriticalPer(), wstr, 10);
//        statLabel[3]->text = wstr;
//        _itow_s((int)champion->GetAbilityPower(), wstr, 10);
//        statLabel[4]->text = wstr;
//        _itow_s((int)champion->GetMagicResistance(), wstr, 10);
//        statLabel[5]->text = wstr;
//        _itow_s((int)champion->GetCooldownReduction(), wstr, 10);
//        statLabel[6]->text = wstr;
//        _itow_s((int)(champion->GetMovementSpeed() * 100), wstr, 10);
//        statLabel[7]->text = wstr;
//    }
//    for (int i = 0; i < 8; i++)
//    {
//        labelPos[i].x += 25;
//        statLabel[i]->transform->position = labelPos[i];
//        statLabel[i]->Render();
//    }
//}
//
//void PlayerInfoPanel::RenderMini()
//{
//}
//
//void PlayerInfoPanel::RenderBar()
//{
//    float ratioHP = 0.f;
//    float ratioMP = 0.f;
//    float maxHp = champion->GetMaxHP();
//    float maxMp = champion->GetMaxMP();
//    float hpBar = champion->GetHP();
//    float mpBar = champion->GetMP();
//    WCHAR hpText[32] = {};
//    WCHAR mpText[32] = {};
//
//    if (maxHp != 0.f)
//    {
//        ratioHP = hpBar / maxHp;
//        swprintf_s(hpText, L"%d / %d", (int)hpBar, (int)maxHp);
//        hpLabel->text = hpText;
//    }
//    if (maxMp != 0.f)
//    {
//        ratioMP = mpBar / maxMp;
//        swprintf_s(mpText, L"%d / %d", (int)mpBar, (int)maxMp);
//        mpLabel->text = mpText;
//    }
//
//    if (ratioHP < 0.f) ratioHP = 0.f;
//    if (ratioMP < 0.f) ratioMP = 0.f;
//
//    RenderManager::DrawUIHorizontal(textureKeyHP, mainPanelPos + hpOffsetPos, scaleHP, 0, ratioHP);
//    hpLabel->Render();
//    RenderManager::DrawUIHorizontal(textureKeyMP, mainPanelPos + mpOffsetPos, scaleMP, 0, ratioMP);
//    mpLabel->Render();
//}

void PlayerInfoPanel::SetTarget(Champion* _target)
{
    champion = _target;
    if (_target == nullptr) return;
    facePanel->SetTexture(champion->faceCircleTexkey);
    
    slotSpell1->SetIcon(champion->qTexKey);
    slotSpell2->SetIcon(champion->wTexKey);
    slotSpell3->SetIcon(champion->eTexKey);
    slotSpell4->SetIcon(champion->rTexKey);
    slotPassive->SetIcon(champion->passiveTexKey);
}

void PlayerInfoPanel::PlayerPanel_OnClick(GameObject* sender, MouseEventArg* arg)
{
    ClickStatButton();
}

void PlayerInfoPanel::ClickStatButton()
{
    pPlayerInfoPanel->statPanel->visible ? 
    pPlayerInfoPanel->statPanel->Hide() :
    pPlayerInfoPanel->statPanel->Show();
}
