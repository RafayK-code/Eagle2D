#pragma once
#include "EaglePCH.h"
#include "SFML/Graphics.hpp"

#include "Core.h"
#include "Keyboard.h"

namespace Eagle
{
    class EAGLE_API Event
    {
    public:
        enum EventType
        {
            Closed,                
            Resized,               
            LostFocus,             
            GainedFocus,           
            TextEntered,           
            KeyPressed,            
            KeyReleased,           
            MouseWheelMoved,       
            MouseWheelScrolled,    
            MouseButtonPressed,    
            MouseButtonReleased,   
            MouseMoved,            
            MouseEntered,          
            MouseLeft,             
            JoystickButtonPressed, 
            JoystickButtonReleased,
            JoystickMoved,         
            JoystickConnected,     
            JoystickDisconnected,  
            TouchBegan,            
            TouchMoved,            
            TouchEnded,            
            SensorChanged,         

            Count                  
        };

        struct SizeEvent
        {
            unsigned int width;  ///< New width, in pixels
            unsigned int height; ///< New height, in pixels
        };

        struct KeyEvent
        {
            Keyboard::Key code;    ///< Code of the key that has been pressed
            bool          alt;     ///< Is the Alt key pressed?
            bool          control; ///< Is the Control key pressed?
            bool          shift;   ///< Is the Shift key pressed?
            bool          system;  ///< Is the System key pressed?
        };

        struct TextEvent
        {
            sf::Uint32 unicode; ///< UTF-32 Unicode value of the character
        };

        struct MouseMoveEvent
        {
            int x; ///< X position of the mouse pointer, relative to the left of the owner window
            int y; ///< Y position of the mouse pointer, relative to the top of the owner window
        };

        struct MouseButtonEvent
        {
            sf::Mouse::Button button; ///< Code of the button that has been pressed
            int           x;      ///< X position of the mouse pointer, relative to the left of the owner window
            int           y;      ///< Y position of the mouse pointer, relative to the top of the owner window
        };

        struct MouseWheelEvent
        {
            int delta; ///< Number of ticks the wheel has moved (positive is up, negative is down)
            int x;     ///< X position of the mouse pointer, relative to the left of the owner window
            int y;     ///< Y position of the mouse pointer, relative to the top of the owner window
        };

        struct MouseWheelScrollEvent
        {
            sf::Mouse::Wheel wheel; ///< Which wheel (for mice with multiple ones)
            float        delta; ///< Wheel offset (positive is up/left, negative is down/right). High-precision mice may use non-integral offsets.
            int          x;     ///< X position of the mouse pointer, relative to the left of the owner window
            int          y;     ///< Y position of the mouse pointer, relative to the top of the owner window
        };

        union
        {
            SizeEvent size;
            KeyEvent key;
            TextEvent text;
            MouseMoveEvent mouseMove;
            MouseButtonEvent mouseButton;
            MouseWheelEvent mouseWheel;
            MouseWheelScrollEvent mouseWheelScroll;
        };

        sf::Event::EventType GetEventType()
        {
            return event.type;
        }

        sf::Event& GetEvent()
        {
            return event;
        }

    private:
        sf::Event event;
    };
}