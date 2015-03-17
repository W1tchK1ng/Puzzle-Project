#include "AnimatedButtons.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace cocos2d::gui;

void AnimatedButtons::Init(cocos2d::gui::UIButton* btn, cocos2d::gui::UILabelBMFont* lbl, cocos2d::gui::UIImageView* img)
	{
		button_down = false;
		button_time_to_update = 0;
		changed = false;		
		UIBtn = btn;
		if (btn != NULL) basal_scale = CCPoint(btn->getScaleX(), btn->getScaleY());
		if (btn != NULL) basal_size = btn->getContentSize();
		label_flag = false;
		image_flag = false;
		Set(false, 1);
		if (lbl != NULL) {label_flag = true; UILbl = lbl;}
		if (img != NULL) {image_flag = true; UIImg = img;}
	}

void AnimatedButtons::Set(bool buttondown, float timettu)
	{
   button_down = buttondown;
   button_time_to_update = timettu;
   changed = true;
	}

void AnimatedButtons::Update(float dt)
	{
		if (changed == true)
			{
			button_time_to_update +=dt;

			if (button_time_to_update > 1)
				{
					if (button_down == true)
					{
					UIBtn->stopAllActions();					
					UIBtn->runAction(create_button_animation2());					
					}

					if (button_down == false)
					{					
					UIBtn->stopAllActions();
					CCRepeatForever *acc = CCRepeatForever::create(create_button_animation1());
					UIBtn->runAction(acc);											
					}

				button_time_to_update = 0;
				changed = false;
			
				}
					
			}
	}

cocos2d::CCSequence* AnimatedButtons::create_button_animation1()
{		
	CCScaleTo *scaleHorDown1 = CCScaleTo::create(15/30.f,basal_scale.x - 0.05f,basal_scale.y);
	CCEaseSineInOut *scaleHorBouncing1 = CCEaseSineInOut::create(scaleHorDown1);
	CCScaleTo *scaleVerDown1 = CCScaleTo::create(15/30.f,basal_scale.x, basal_scale.y-0.05f);
	CCEaseSineInOut *scaleVerBouncing1 = CCEaseSineInOut::create(scaleVerDown1);
	CCSequence *shrink1 = CCSequence::create(scaleHorBouncing1,scaleVerBouncing1, NULL);	
	//CCScaleTo *swell1 = CCScaleTo::create(10/30.f,1);
	//CCEaseSineInOut *swellEase1 = CCEaseSineInOut::create(swell1);			
	return CCSequence::create(shrink1, NULL);
}

cocos2d::CCSequence* AnimatedButtons::create_button_animation2()
{	
	CCScaleTo *scaleHorDown1 = CCScaleTo::create(5/30.f,basal_scale.x - 0.35f,basal_scale.y);
	CCEaseBounceIn *scaleHorBouncing1 = CCEaseBounceIn::create(scaleHorDown1);
	CCScaleTo *scaleVerDown1 = CCScaleTo::create(5/30.f,basal_scale.x, basal_scale.y - 0.35f);
	CCEaseBounceInOut *scaleVerBouncing1 = CCEaseBounceInOut::create(scaleVerDown1);
	CCSequence *shrink1 = CCSequence::create(scaleHorBouncing1,scaleVerBouncing1, NULL);
	CCScaleTo *swell1 = CCScaleTo::create(15/30.f,basal_scale.x - 0.10f);
	CCEaseElasticOut *swellEase1 = CCEaseElasticOut::create(swell1);
	CCScaleTo *resetScale1 = CCScaleTo::create(1/30.f, basal_scale.x - 0.15f);
	CCEaseInOut *resetScaleBouncing1 = CCEaseInOut::create(resetScale1, 1);		
	return CCSequence::create(resetScaleBouncing1, shrink1, swellEase1, NULL);
}

cocos2d::CCSequence* AnimatedButtons::create_button_animation3()
{	
	CCScaleTo *scaleHorDown1 = CCScaleTo::create(5/30.f,basal_scale.x - 0.35f, basal_scale.y);
	CCEaseSineInOut *scaleHorBouncing1 = CCEaseSineInOut::create(scaleHorDown1);
	CCScaleTo *scaleVerDown1 = CCScaleTo::create(5/30.f,basal_scale.x, basal_scale.y - 0.35f);
	CCEaseSineInOut *scaleVerBouncing1 = CCEaseSineInOut::create(scaleVerDown1);
	CCSequence *shrink1 = CCSequence::create(scaleHorBouncing1,scaleVerBouncing1, NULL);	
	return CCSequence::create(shrink1, NULL);
}

void AnimatedButtons::FadeOut(float time)
{
	CCActionInterval *seq1 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(time), NULL); 
	UIBtn->runAction(seq1);
	if (label_flag == true)
		{
		CCActionInterval *seq2 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(time), NULL); 
		UILbl->runAction(seq2);
		}
	if (image_flag == true)
		{
		CCActionInterval *seq3 = (CCActionInterval*)CCSequence::create(CCFadeOut::create(time), NULL); 
		UIImg->runAction(seq3);
		}
}
void AnimatedButtons::Show()
{	
	UIBtn->setEnabled(true);
	UIBtn->setVisible(true);
	UIBtn->setTouchEnabled(true);
	if (label_flag == true)
		{
		UILbl->setEnabled(true);
		UILbl->setVisible(true);
		}
	if (image_flag == true)
		{
		UIImg->setEnabled(true);
		UIImg->setVisible(true);
		}
}

void AnimatedButtons::Hide()
{
	UIBtn->setEnabled(false);
	UIBtn->setVisible(false);
	UIBtn->setTouchEnabled(false);
	if (label_flag == true)
		{
		UILbl->setEnabled(false);
		UILbl->setVisible(false);
		}
	if (image_flag == true)
		{
		UIImg->setEnabled(false);
		UIImg->setVisible(false);
		}
}