#ifndef __ANIMATED_BUTTONS_H__
#define __ANIMATED_BUTTONS_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class AnimatedButtons {
	public:
	AnimatedButtons() {};
	~AnimatedButtons() {};
   private:      
      bool changed;
	  bool button_down;
	  float button_time_to_update;	 
	  bool label_flag;	  
	  bool image_flag;	
	  cocos2d::CCPoint basal_scale;
	  cocos2d::CCPoint basal_size;
   public:      
	  cocos2d::gui::UIButton*UIBtn;
	  cocos2d::gui::UIImageView* UIImg;
	  cocos2d::gui::UILabelBMFont *UILbl;
	  void Init(cocos2d::gui::UIButton* btn, cocos2d::gui::UILabelBMFont* lbl, cocos2d::gui::UIImageView* img);
      void Set(bool buttondown, float ttu);	  
	  void Update(float dt);
	  bool IsDown() {return button_down;}
	  void FadeOut(float time);
	  void Show();
	  void Hide();
	  cocos2d::CCSequence *create_button_animation1();
	  cocos2d::CCSequence *create_button_animation2();
	  cocos2d::CCSequence *create_button_animation3();	
};

#endif // __Inicio_SCENE_H__