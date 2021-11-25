#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace AWS
{
    enum key {
        //Letters
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        W = GLFW_KEY_W,
        V = GLFW_KEY_V,
        Y = GLFW_KEY_Y,
        X = GLFW_KEY_X,
        Q = GLFW_KEY_Q,
        Z = GLFW_KEY_Z,
        //Numbers
        N0 = GLFW_KEY_0,
        N1 = GLFW_KEY_1,
        N2 = GLFW_KEY_2,
        N3 = GLFW_KEY_3,
        N4 = GLFW_KEY_4,
        N5 = GLFW_KEY_5,
        N6 = GLFW_KEY_6,
        N7 = GLFW_KEY_7,
        N8 = GLFW_KEY_8,
        N9 = GLFW_KEY_9,
        //Numpad
        PN0 = GLFW_KEY_KP_0,
        PN1 = GLFW_KEY_KP_1,
        PN2 = GLFW_KEY_KP_2,
        PN3 = GLFW_KEY_KP_3,
        PN4 = GLFW_KEY_KP_4,
        PN5 = GLFW_KEY_KP_5,
        PN6 = GLFW_KEY_KP_6,
        PN7 = GLFW_KEY_KP_7,
        PN8 = GLFW_KEY_KP_8,
        PN9 = GLFW_KEY_KP_9,
        PADD = GLFW_KEY_KP_ADD,
        PDEC = GLFW_KEY_KP_DECIMAL,
        PMUL = GLFW_KEY_KP_MULTIPLY,
        PSUB = GLFW_KEY_KP_SUBTRACT,
        PENT = GLFW_KEY_KP_ENTER,
        PDIV = GLFW_KEY_KP_DIVIDE,
        PEQU = GLFW_KEY_KP_EQUAL,
        //Arrows
        UP = GLFW_KEY_UP,
        DOWN = GLFW_KEY_DOWN,
        LEFT = GLFW_KEY_LEFT,
        RIGHT = GLFW_KEY_RIGHT,
        //Other keys
        TAB = GLFW_KEY_TAB,
        BACKSPACE = GLFW_KEY_BACKSPACE,
        BACKSLASH = GLFW_KEY_BACKSLASH,
        GRACC = GLFW_KEY_GRAVE_ACCENT,
        SLASH = GLFW_KEY_SLASH,
        PRINT = GLFW_KEY_PRINT_SCREEN,
        SCROLL = GLFW_KEY_SCROLL_LOCK,
        APOSTROPHE = GLFW_KEY_APOSTROPHE,
        CAPSLOCK = GLFW_KEY_CAPS_LOCK,
        COMMA = GLFW_KEY_COMMA,
        DELETE = GLFW_KEY_DELETE,
        END = GLFW_KEY_END,
        ENTER = GLFW_KEY_ENTER,
        EQUAL = GLFW_KEY_EQUAL,
        ESCAPE = GLFW_KEY_ESCAPE,
        HOME = GLFW_KEY_HOME,
        INSERT = GLFW_KEY_INSERT,
        LAST = GLFW_KEY_LAST,
        MENU = GLFW_KEY_MENU,
        MINUS = GLFW_KEY_MINUS,
        PGDOWN = GLFW_KEY_PAGE_DOWN,
        PGUP = GLFW_KEY_PAGE_UP,
        NUMLOCK = GLFW_KEY_NUM_LOCK,
        PAUSE = GLFW_KEY_PAUSE,
        PERIOD = GLFW_KEY_PERIOD,
        SEMICOLON = GLFW_KEY_SEMICOLON,
        SPACE = GLFW_KEY_SPACE,
        UNKNOWN = GLFW_KEY_UNKNOWN,
        W1 = GLFW_KEY_WORLD_1,
        W2 = GLFW_KEY_WORLD_2,
        //Left keys
        LSHIFT = GLFW_KEY_LEFT_SHIFT,
        LCRTL = GLFW_KEY_LEFT_CONTROL,
        LALT = GLFW_KEY_LEFT_ALT,
        LSUP = GLFW_KEY_LEFT_SUPER,
        LBRA = GLFW_KEY_LEFT_BRACKET,
        //Left keys
        RSHIFT = GLFW_KEY_RIGHT_SHIFT,
        RCRTL = GLFW_KEY_RIGHT_CONTROL,
        RALT = GLFW_KEY_RIGHT_ALT,
        RSUP = GLFW_KEY_RIGHT_SUPER,
        RBRA = GLFW_KEY_RIGHT_BRACKET,
        //F keys
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,
    };

    class Aws_Camera
    {
    private:
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 camDirection = glm::vec3(0.0f, 0.0f, 0.0f);

    public:
        /**
         * @brief Set the Position object
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        void SetPosition(float x, float y, float z);

        /**
         * @brief Set the Rotation object
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        void SetRotation(float x, float y, float z);

        /**
         * @brief Get the Position object
         * 
         * @return glm::vec3 
         */
        glm::vec3 GetPosition() { return cameraPos; }

        /**
         * @brief Get the Front object
         * 
         * @return glm::vec3 
         */
        glm::vec3 GetFront() { return cameraFront; }

        /**
         * @brief Get the Up object
         * 
         * @return glm::vec3 
         */
        glm::vec3 GetUp() { return cameraUp; }
    };

    void Aws_Camera::SetPosition(float x, float y, float z)
    {
        cameraPos.x = x;
        cameraPos.y = y;
        cameraPos.z = z;
    }

    void Aws_Camera::SetRotation(float x, float y, float z)
    {
        camDirection.x = cos(glm::radians(x)) * cos(glm::radians(y));
        camDirection.y = sin(glm::radians(y));
        camDirection.z = sin(glm::radians(x)) * cos(glm::radians(y));
        cameraFront = glm::normalize(camDirection);
    }

    typedef Aws_Camera Camera;
}