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


#ifndef TGUI_TEXT_STYLE_HPP
#define TGUI_TEXT_STYLE_HPP

#include <TGUI/String.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Enumeration of the text drawing styles
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum TextStyle : unsigned int
    {
        Regular       = 0,      //!< Regular characters, no style
        Bold          = 1 << 0, //!< Bold characters
        Italic        = 1 << 1, //!< Italic characters
        Underlined    = 1 << 2, //!< Underlined characters
        StrikeThrough = 1 << 3  //!< Strike through characters
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Wrapper for text styles
    ///
    /// The class is used for 2 purposes:
    /// - Implicit converter for parameters. A function taking a TextStyles as parameter can be given either a
    ///   tgui::TextStyle (or multiple combined with | operator) or a string representation as argument.
    /// - Storing no style at all. Some style settings may be optionally set and can thus remain unspecified.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API TextStyles
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates the object without a text style
        ///
        /// The isSet function will return false when the object was created using this constructor.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        constexpr TextStyles() :
            m_isSet{false},
            m_style{Regular}
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates the object from one or more tgui::TextStyle::Style enum members
        ///
        /// @param style  Text style to set
        ///
        /// @code
        /// TextStyles style{tgui::TextStyle::Italic | tgui::TextStyle::Bold};
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        constexpr TextStyles(unsigned int style) :
            m_isSet{true},
            m_style{style}
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates the object from a string representing the text styles
        ///
        /// @param string  String to be deserialized as text styles
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextStyles(const String& string);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates the object from a string representing the text styles
        ///
        /// @param string  String to be deserialized as text styles
        ///
        /// @code
        /// TextStyles style{"Italic | Bold"};
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextStyles(const char* string);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if a style was set
        ///
        /// @return True if a text style was passed to the constructor, false when the default constructor was used
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD constexpr bool isSet() const
        {
            return m_isSet;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts this object into an unsigned int
        ///
        /// @return The text styles stored in this object, or tgui::TextStyle::Regular if no style was set
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        constexpr operator unsigned int() const
        {
            return m_style;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        bool         m_isSet; // Stores the flag indicating whether this object has been explicitly initialized or created from default.

        unsigned int m_style; // Stores the text styles represented by this object.
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_STYLE_HPP
