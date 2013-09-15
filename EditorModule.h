//
//  EditorModule.h
//  FEXMac
//
//  Created by Fancyzero on 13-9-8.
//
//

#ifndef __FEXMac__EditorModule__
#define __FEXMac__EditorModule__

#include "FE.h"
#include "LevelBase.h"
#include "TouchController.h"
FE_NS_BEGIN

class AddController :public TouchController
{
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
};

class EditController :public TouchController
{
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    
};

class EditorModule
{
public:
    enum EditMode
    {
        edit,
        add,
        game,
    };
    EditorModule();

    EditMode get_edit_mode()
    {
        return edit_mode;
    }
    
    void set_editmode( EditMode mode )
    {
        edit_mode = mode;
    }
    
    LevelTrigger& get_template_trigger()
    {
        return template_trigger;
    }
    LevelTrigger& get_current_trigger()
    {
        switch ( get_edit_mode() )
        {
            case edit:
                return dummy_trigger;
                break;
            case add:
                return get_template_trigger();
                break;
            case game:
                return dummy_trigger;
                break;
        }
    }
    void pick_object( const cocos2d::CCPoint& pos );
    void select_object( GameObjPtr obj );
    void unselect_object( GameObjPtr obj );
    static EditorModule* get_instance();
protected:
    EditMode   edit_mode;
    LevelTrigger dummy_trigger;
    LevelTrigger template_trigger;//trigger use to add new object
    std::vector<std::shared_ptr<GameObjBase> > selected_objects;
};
FE_NS_END
#endif /* defined(__FEXMac__EditorModule__) */
