#ifndef __ANIMATED_BUTTONS_H__
#define __ANIMATED_BUTTONS_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class AnimatedButtons {
	public:
	AnimatedButtons() {};
	~AnimatedButtons() {};
   private:      
      bool changed_down;	    
	  bool changed_up;	    
	  bool button_going_down;	
	  bool button_going_up;
	  bool button_pressed;
	  bool button_pressed_changed;
	  bool button_pressed_outside;
	  bool button_pressed_inside;
	  float button_time_to_update_down;	 
	  float button_time_to_update_up;	 
	  bool label_flag;	  
	  bool image_flag;		  
	  cocos2d::CCPoint basal_scale;
	  cocos2d::CCPoint basal_size;
	  float panelScaleX;
	  float panelScaleY;
   public: 	
	  cocos2d::gui::UIButton*UIBtn;
	  cocos2d::gui::UIImageView* UIImg;
	  cocos2d::gui::UILabelBMFont *UILbl;
	  void Init(cocos2d::gui::UIButton* btn, cocos2d::gui::UILabelBMFont* lbl, cocos2d::gui::UIImageView* img, float psx, float psy);
      void SetButtonGoingDown(bool buttondown, float ttu);	  
	  void SetButtonGoingUp(bool buttonup, float ttu);	  
	  void Update(float dt);
	  bool IsDown() {return button_going_down;}	 
	  bool IsUp() {return button_going_up;}
	  void FadeOut(float time);
	  void Show();
	  void Hide();
	  void Pressed(bool value);
	  bool isPressed();
	  bool isPressedOutside(float scaleX, float scaleY);
	  void SetTouchable(bool value);	
	  void SetPanelScale(float x, float y) {panelScaleX = x; panelScaleY = y;}
	  cocos2d::CCSequence *create_button_animation1();
	  cocos2d::CCSequence *create_button_animation2();
	  cocos2d::CCSequence *create_button_animation3();	
	  void Began();
	  void Moved();
	  void Ended();
	  void Canceled();
};

#endif // __Inicio_SCENE_H__