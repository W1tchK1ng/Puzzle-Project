#include "AnimatedButtons.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace cocos2d::gui;

#define TIME_LIMIT 1

void AnimatedButtons::Init(cocos2d::gui::UIButton* btn, cocos2d::gui::UILabelBMFont* lbl, cocos2d::gui::UIImageView* img, float psx, float psy)
	{		
		button_pressed = false;
		button_pressed_changed = false;
		button_going_down = false;
		button_going_up = false;
		button_time_to_update_down = 0;
		button_time_to_update_up = 0;
		changed_down = false;		
		changed_up = false;
		UIBtn = btn;
		if (btn != NULL) basal_scale = CCPoint(btn->getScaleX(), btn->getScaleY());
		if (btn != NULL) basal_size = btn->getContentSize();
		label_flag = false;
		image_flag = false;
		SetButtonGoingUp(true, TIME_LIMIT);
		if (lbl != NULL) {label_flag = true; UILbl = lbl;}
		if (img != NULL) {image_flag = true; UIImg = img;}
		panelScaleX = psx;
		panelScaleY = psy;
	}

void AnimatedButtons::SetButtonGoingDown(bool buttondown, float timettu)
	{	
   button_going_down = buttondown;
   button_time_to_update_down = timettu;
   changed_down = true;	
	}

void AnimatedButtons::SetButtonGoingUp(bool buttonup, float timettu)
	{	
   button_going_up = buttonup;
   button_time_to_update_up = timettu;
   changed_up = true;	
	}

void AnimatedButtons::Update(float dt)
	{
		if (changed_down == true)
			{			
			button_time_to_update_down +=dt;

			if (button_time_to_update_down > TIME_LIMIT)
				{
					if (button_going_down == true)
					{
					UIBtn->stopAllActions();
					//changed_up = false;
					//button_time_to_update_up = 0;
					//button_going_up = false;
					UIBtn->runAction(create_button_animation2());	
					button_going_down = false;					
					}					

				button_time_to_update_down = 0;
				changed_down = false;
			
				}
					
			}

		if (changed_up == true)
			{
			
			button_time_to_update_up +=dt;

			if (button_time_to_update_up > TIME_LIMIT)
				{
					if (button_going_up == true && button_going_down == false)
					{
					CCScaleTo *resetScale1 = CCScaleTo::create(5/30.f, basal_scale.x);
					CCEaseInOut *resetScaleBouncing1 = CCEaseInOut::create(resetScale1, 1);	
					UIBtn->runAction(resetScaleBouncing1);	
				/*	CCRotateTo *rotate1 = CCRotateTo::create(5/30.f, 0);
					UIBtn->runAction(rotate1);	*/
					CCRepeatForever *acc = CCRepeatForever::create(create_button_animation1());
					UIBtn->runAction(acc);	
					button_going_up = false;	
					Pressed(false);
					}

				button_time_to_update_up = 0;
				changed_up = false;
			
				}
					
			}

	static bool viejo;
	static bool nuevo;

	if (isPressed())
	if (isPressedOutside(panelScaleX, panelScaleY)) 
	{	
	nuevo = true;
	if (button_going_up == false && button_going_down == false && viejo == false) {SetButtonGoingUp(true, 0.5f); viejo = true;}	
	}
	else
	{
	nuevo = false;
	if (button_going_up == false && button_going_down == false && viejo == true) {SetButtonGoingDown(true, 1);	viejo = false;}
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
	CCScaleTo *swell1 = CCScaleTo::create(20/30.f,basal_scale.x - 0.35f);
	CCEaseElasticOut *swellEase1 = CCEaseElasticOut::create(swell1);
	CCRotateTo *rotate1 = CCRotateTo::create(5/30.f, 180);
	//CCScaleTo *resetScale1 = CCScaleTo::create(5/30.f, basal_scale.x - 0.15f);
	//CCEaseInOut *resetScaleBouncing1 = CCEaseInOut::create(resetScale1, 1);		
	return CCSequence::create(swellEase1, NULL);
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

void AnimatedButtons::SetTouchable(bool value)
{	
	UIBtn->setTouchEnabled(value);
	//UIBtn->setColor(ccc3(255,255,255));
	//if (value == false) UIBtn->setColor(ccc3(128,128,128));
	
}

void AnimatedButtons::Pressed(bool value) 
{
	button_pressed = value;
	button_pressed_changed = true;
	if (isPressedOutside(panelScaleX, panelScaleY) == true)
		{
		 button_pressed_outside = true;
		 button_pressed_inside = false;
		}
	else {
		 button_pressed_outside = true;
		 button_pressed_inside = false;
		 }

}

bool AnimatedButtons::isPressed() 
{
	return button_pressed;
}

bool AnimatedButtons::isPressedOutside(float scaleX, float scaleY) 
{
	if (UIBtn->getTouchMovePos().x < UIBtn->getWorldPosition().x - UIBtn->getContentSize().width/2*scaleX) return true;
	if (UIBtn->getTouchMovePos().x > UIBtn->getWorldPosition().x + UIBtn->getContentSize().width/2*scaleX) return true;
	if (UIBtn->getTouchMovePos().y < UIBtn->getWorldPosition().y - UIBtn->getContentSize().height/2*scaleY) return true; 
	if (UIBtn->getTouchMovePos().y > UIBtn->getWorldPosition().y + UIBtn->getContentSize().height/2*scaleY) return true;				
	return false;	
}

void AnimatedButtons::Began()
{
SetButtonGoingDown(true, TIME_LIMIT);	
Pressed(true);
}
void AnimatedButtons::Moved()
{
Pressed(true);	
}
void AnimatedButtons::Ended()
{
SetButtonGoingUp(true, 0.5f);		
//Pressed(false);
}
void AnimatedButtons::Canceled()
{
SetButtonGoingUp(true, 1);		
//Pressed(false);
}

