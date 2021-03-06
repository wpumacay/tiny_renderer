
#include <input_py.h>

namespace py = pybind11;

namespace engine
{
    void bindings_inputKey( py::module& m )
    {
        py::enum_<engine::Keys>( m, "Keys", py::arithmetic() )
            .value( "KEY_SPACE", engine::Keys::KEY_SPACE )
            .value( "KEY_APOSTROPHE", engine::Keys::KEY_APOSTROPHE )
            .value( "KEY_COMMA", engine::Keys::KEY_COMMA )
            .value( "KEY_MINUS", engine::Keys::KEY_MINUS )
            .value( "KEY_PERIOD", engine::Keys::KEY_PERIOD )
            .value( "KEY_SLASH", engine::Keys::KEY_SLASH )
            .value( "KEY_0", engine::Keys::KEY_0 )
            .value( "KEY_1", engine::Keys::KEY_1 )
            .value( "KEY_2", engine::Keys::KEY_2 )
            .value( "KEY_3", engine::Keys::KEY_3 )
            .value( "KEY_4", engine::Keys::KEY_4 )
            .value( "KEY_5", engine::Keys::KEY_5 )
            .value( "KEY_6", engine::Keys::KEY_6 )
            .value( "KEY_7", engine::Keys::KEY_7 )
            .value( "KEY_8", engine::Keys::KEY_8 )
            .value( "KEY_9", engine::Keys::KEY_9 )
            .value( "KEY_SEMICOLON", engine::Keys::KEY_SEMICOLON )
            .value( "KEY_EQUAL", engine::Keys::KEY_EQUAL )
            .value( "KEY_A", engine::Keys::KEY_A )
            .value( "KEY_B", engine::Keys::KEY_B )
            .value( "KEY_C", engine::Keys::KEY_C )
            .value( "KEY_D", engine::Keys::KEY_D )
            .value( "KEY_E", engine::Keys::KEY_E )
            .value( "KEY_F", engine::Keys::KEY_F )
            .value( "KEY_G", engine::Keys::KEY_G )
            .value( "KEY_H", engine::Keys::KEY_H )
            .value( "KEY_I", engine::Keys::KEY_I )
            .value( "KEY_J", engine::Keys::KEY_J )
            .value( "KEY_K", engine::Keys::KEY_K )
            .value( "KEY_L", engine::Keys::KEY_L )
            .value( "KEY_M", engine::Keys::KEY_M )
            .value( "KEY_N", engine::Keys::KEY_N )
            .value( "KEY_O", engine::Keys::KEY_O )
            .value( "KEY_P", engine::Keys::KEY_P )
            .value( "KEY_Q", engine::Keys::KEY_Q )
            .value( "KEY_R", engine::Keys::KEY_R )
            .value( "KEY_S", engine::Keys::KEY_S )
            .value( "KEY_T", engine::Keys::KEY_T )
            .value( "KEY_U", engine::Keys::KEY_U )
            .value( "KEY_V", engine::Keys::KEY_V )
            .value( "KEY_W", engine::Keys::KEY_W )
            .value( "KEY_X", engine::Keys::KEY_X )
            .value( "KEY_Y", engine::Keys::KEY_Y )
            .value( "KEY_Z", engine::Keys::KEY_Z )
            .value( "KEY_LEFT_BRACKET", engine::Keys::KEY_LEFT_BRACKET )
            .value( "KEY_BACKSLASH", engine::Keys::KEY_BACKSLASH )
            .value( "KEY_RIGHT_BRACKET", engine::Keys::KEY_RIGHT_BRACKET )
            .value( "KEY_GRAVE_ACCENT", engine::Keys::KEY_GRAVE_ACCENT )
            .value( "KEY_WORLD_1", engine::Keys::KEY_WORLD_1 )
            .value( "KEY_WORLD_2", engine::Keys::KEY_WORLD_2 )
            .value( "KEY_ESCAPE", engine::Keys::KEY_ESCAPE )
            .value( "KEY_ENTER", engine::Keys::KEY_ENTER )
            .value( "KEY_TAB", engine::Keys::KEY_TAB )
            .value( "KEY_BACKSPACE", engine::Keys::KEY_BACKSPACE )
            .value( "KEY_INSERT", engine::Keys::KEY_INSERT )
            .value( "KEY_DELETE", engine::Keys::KEY_DELETE )
            .value( "KEY_RIGHT", engine::Keys::KEY_RIGHT )
            .value( "KEY_LEFT", engine::Keys::KEY_LEFT )
            .value( "KEY_DOWN", engine::Keys::KEY_DOWN )
            .value( "KEY_UP", engine::Keys::KEY_UP )
            .value( "KEY_PAGE_UP", engine::Keys::KEY_PAGE_UP )
            .value( "KEY_PAGE_DOWN", engine::Keys::KEY_PAGE_DOWN )
            .value( "KEY_HOME", engine::Keys::KEY_HOME )
            .value( "KEY_END", engine::Keys::KEY_END )
            .value( "KEY_CAPS_LOCK", engine::Keys::KEY_CAPS_LOCK )
            .value( "KEY_SCROLL_LOCK", engine::Keys::KEY_SCROLL_LOCK )
            .value( "KEY_NUM_LOCK", engine::Keys::KEY_NUM_LOCK )
            .value( "KEY_PRINT_SCREEN", engine::Keys::KEY_PRINT_SCREEN )
            .value( "KEY_PAUSE", engine::Keys::KEY_PAUSE )
            .value( "KEY_F1", engine::Keys::KEY_F1 )
            .value( "KEY_F2", engine::Keys::KEY_F2 )
            .value( "KEY_F3", engine::Keys::KEY_F3 )
            .value( "KEY_F4", engine::Keys::KEY_F4 )
            .value( "KEY_F5", engine::Keys::KEY_F5 )
            .value( "KEY_F6", engine::Keys::KEY_F6 )
            .value( "KEY_F7", engine::Keys::KEY_F7 )
            .value( "KEY_F8", engine::Keys::KEY_F8 )
            .value( "KEY_F9", engine::Keys::KEY_F9 )
            .value( "KEY_F10", engine::Keys::KEY_F10 )
            .value( "KEY_F11", engine::Keys::KEY_F11 )
            .value( "KEY_F12", engine::Keys::KEY_F12 )
            .value( "KEY_F13", engine::Keys::KEY_F13 )
            .value( "KEY_F14", engine::Keys::KEY_F14 )
            .value( "KEY_F15", engine::Keys::KEY_F15 )
            .value( "KEY_F16", engine::Keys::KEY_F16 )
            .value( "KEY_F17", engine::Keys::KEY_F17 )
            .value( "KEY_F18", engine::Keys::KEY_F18 )
            .value( "KEY_F19", engine::Keys::KEY_F19 )
            .value( "KEY_F20", engine::Keys::KEY_F20 )
            .value( "KEY_F21", engine::Keys::KEY_F21 )
            .value( "KEY_F22", engine::Keys::KEY_F22 )
            .value( "KEY_F23", engine::Keys::KEY_F23 )
            .value( "KEY_F24", engine::Keys::KEY_F24 )
            .value( "KEY_F25", engine::Keys::KEY_F25 )
            .value( "KEY_KP_0", engine::Keys::KEY_KP_0 )
            .value( "KEY_KP_1", engine::Keys::KEY_KP_1 )
            .value( "KEY_KP_2", engine::Keys::KEY_KP_2 )
            .value( "KEY_KP_3", engine::Keys::KEY_KP_3 )
            .value( "KEY_KP_4", engine::Keys::KEY_KP_4 )
            .value( "KEY_KP_5", engine::Keys::KEY_KP_5 )
            .value( "KEY_KP_6", engine::Keys::KEY_KP_6 )
            .value( "KEY_KP_7", engine::Keys::KEY_KP_7 )
            .value( "KEY_KP_8", engine::Keys::KEY_KP_8 )
            .value( "KEY_KP_9", engine::Keys::KEY_KP_9 )
            .value( "KEY_KP_DECIMAL", engine::Keys::KEY_KP_DECIMAL )
            .value( "KEY_KP_DIVIDE", engine::Keys::KEY_KP_DIVIDE )
            .value( "KEY_KP_MULTIPLY", engine::Keys::KEY_KP_MULTIPLY )
            .value( "KEY_KP_SUBTRACT", engine::Keys::KEY_KP_SUBTRACT )
            .value( "KEY_KP_ADD", engine::Keys::KEY_KP_ADD )
            .value( "KEY_KP_ENTER", engine::Keys::KEY_KP_ENTER )
            .value( "KEY_KP_EQUAL", engine::Keys::KEY_KP_EQUAL )
            .value( "KEY_LEFT_SHIFT", engine::Keys::KEY_LEFT_SHIFT )
            .value( "KEY_LEFT_CONTROL", engine::Keys::KEY_LEFT_CONTROL )
            .value( "KEY_LEFT_ALT", engine::Keys::KEY_LEFT_ALT )
            .value( "KEY_LEFT_SUPER", engine::Keys::KEY_LEFT_SUPER )
            .value( "KEY_RIGHT_SHIFT", engine::Keys::KEY_RIGHT_SHIFT )
            .value( "KEY_RIGHT_CONTROL", engine::Keys::KEY_RIGHT_CONTROL )
            .value( "KEY_RIGHT_ALT", engine::Keys::KEY_RIGHT_ALT )
            .value( "KEY_RIGHT_SUPER", engine::Keys::KEY_RIGHT_SUPER )
            .value( "KEY_MENU", engine::Keys::KEY_MENU );

        py::enum_<engine::KeyAction>( m, "KeyAction", py::arithmetic() )
            .value( "KEY_RELEASED", engine::KeyAction::KEY_RELEASED )
            .value( "KEY_PRESSED", engine::KeyAction::KEY_PRESSED )
            .value( "KEY_REPEAT", engine::KeyAction::KEY_REPEAT );
    }

    void bindings_inputMouse( py::module& m )
    {
        py::enum_<engine::Mouse>( m, "Mouse", py::arithmetic() )
            .value( "BUTTON_LEFT", engine::Mouse::BUTTON_LEFT )
            .value( "BUTTON_BUTTON_RIGHT", engine::Mouse::BUTTON_RIGHT )
            .value( "BUTTON_BUTTON_MIDDLE", engine::Mouse::BUTTON_MIDDLE );

        py::enum_<engine::MouseAction>( m, "MouseAction", py::arithmetic() )
            .value( "BUTTON_RELEASED", engine::MouseAction::BUTTON_RELEASED )
            .value( "BUTTON_PRESSED", engine::MouseAction::BUTTON_PRESSED );
    }

    void bindings_inputManager( py::module& m )
    {
        py::class_< CInputManager >( m, "InputManager" )
            .def_static( "Init", &CInputManager::Init )
            .def_static( "Release", &CInputManager::Release )
            .def_static( "IsKeyDown", &CInputManager::IsKeyDown )
            .def_static( "CheckSingleKeyPress", &CInputManager::CheckSingleKeyPress )
            .def_static( "IsMouseDown", &CInputManager::IsMouseDown )
            .def_static( "GetScrollOffX", &CInputManager::GetScrollOffX )
            .def_static( "GetScrollOffY", &CInputManager::GetScrollOffY )
            .def_static( "GetScrollAccumValueX", &CInputManager::GetScrollAccumValueX )
            .def_static( "GetScrollAccumValueY", &CInputManager::GetScrollAccumValueY )
            .def_static( "GetCursorPosition", []() -> py::array_t<engine::float32>
                {
                    return tinymath::vector_to_nparray<engine::float32,2>( CInputManager::GetCursorPosition() );
                } );
    }
}