#pragma once

class InputListener {
public:
    InputListener();
    ~InputListener();
};

class InputSystem {
public:
    static void Create();
    static void Release();
};