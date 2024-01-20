/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2023 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_DEFAULT_BACKEND_WINDOW_HPP
#define TGUI_DEFAULT_BACKEND_WINDOW_HPP

#include <TGUI/Config.hpp>
#if TGUI_BUILD_AS_CXX_MODULE
    import tgui;
#else
    #include <TGUI/String.hpp>
    #include <TGUI/Color.hpp>
#endif

#if !TGUI_EXPERIMENTAL_USE_STD_MODULE
    #include <memory>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
#if !TGUI_BUILD_AS_CXX_MODULE
    class BackendGui;
    struct Event;
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief This class abstracts the backend-specific window and gui creation code
    ///
    /// Normally you don't need this class as you know what the backend is and can write backend-specific code.
    /// This class is required by e.g. the Gui Builder to work independently from the backend.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API DefaultBackendWindow
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        DefaultBackendWindow() = default;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~DefaultBackendWindow() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates the backend window and the gui
        ///
        /// @param width  Width of the window
        /// @param height Height of the window
        /// @param title  Title of the window
        ///
        /// @warning If TGUI contains multiple backends, an arbitrary one will be used
        /// @warning This function will assert when TGUI was built without a backend
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static std::shared_ptr<DefaultBackendWindow> create(unsigned int width, unsigned int height, const String& title);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the gui object that is created and destroyed by this class
        ///
        /// @return Pointer to the gui that is owned by this class
        ///
        /// @warning You can't access the gui after this backend window is destroyed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual BackendGui* getGui() const = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the window is still open
        ///
        /// @return Is the window still open?
        ///
        /// @warning You must call close() on this object to close the window, it does NOT happen automatically when the user presses
        ///          the close button of the window (in which case you receive an event of type Event::Type::Closed from pollEvent).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual bool isOpen() const = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the window
        /// @see isOpen
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void close() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves an event from the window if there is one
        ///
        /// @param event  Reference to event structure that will filled in by this function if there is an event
        ///
        /// @return True if the window had an unprocessed event. If false is returned, the event parameter is untouched.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD virtual bool pollEvent(Event& event) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draws the gui to the window
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Pass control of the main loop to TGUI, if the backend supports it
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mainLoop(Color clearColor = {240, 240, 240}) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the icon of the window
        ///
        /// @param filename  Filename of the icon to load
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setIcon(const String& filename) = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_DEFAULT_BACKEND_WINDOW_HPP
