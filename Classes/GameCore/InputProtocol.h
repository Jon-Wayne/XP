//
//  InputProtocol.h
//  XP
//
//  Created by Jon Wayne on 14-7-3.
//
//

#ifndef __XP__InputProtocol__
#define __XP__InputProtocol__

class InputProtocol
{
public:
    typedef enum _ButtonStatus
    {
        ButtonPress,
        ButtonRelease
    } ButtonStatus;
    
    virtual void up() = 0;
    
    virtual void down() = 0;
    
    virtual void left() = 0;
    
    virtual void right() = 0;
    
    virtual void none() = 0;
    
    virtual void buttons(int index, ButtonStatus buttonStatus) = 0;
};

#endif /* defined(__XP__InputProtocol__) */
