/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_MENU_BAR_HPP
#define TGUI_MENU_BAR_HPP


#include <TGUI/Widget.hpp>
#include <TGUI/Renderers/MenuBarRenderer.hpp>
#include <TGUI/Text.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Menu bar widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API MenuBar : public Widget
    {
    public:

        typedef std::shared_ptr<MenuBar> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const MenuBar> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MenuBar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new menu bar widget
        ///
        /// @return The new menu bar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static MenuBar::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another menu bar
        ///
        /// @param menuBar  The other menu bar
        ///
        /// @return The new menu bar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static MenuBar::Ptr copy(MenuBar::ConstPtr menuBar);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Temporary pointer to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MenuBarRenderer* getRenderer() const
        {
            return aurora::downcast<MenuBarRenderer*>(m_renderer.get());
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the menu bar
        ///
        /// @param size  The new size of the menu bar
        ///
        /// By default, the menu bar has the same width as the window and the height is 20 pixels.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu
        ///
        /// @param text  The text written on the menu
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addMenu(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu item
        ///
        /// @param menu  The name of the menu to which the menu item will be added
        /// @param text  The text written on this menu item
        ///
        /// @return True when the item was added, false when menu was not found
        ///
        /// @code
        /// menuBar->addMenu("File");
        /// menuBar->addMenu("Edit");
        /// menuBar->addMenuItem("File", "Load");
        /// menuBar->addMenuItem("File", "Save");
        /// menuBar->addMenuItem("Edit", "Undo");
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool addMenuItem(const sf::String& menu, const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu item to the last added menu
        ///
        /// @param text  The text written on this menu item
        ///
        /// @return True when the item was added, false when the menu bar doesn't contain any menus yet
        ///
        /// @code
        /// menuBar->addMenu("File");
        /// menuBar->addMenuItem("Load");
        /// menuBar->addMenuItem("Save");
        /// menuBar->addMenu("Edit");
        /// menuBar->addMenuItem("Undo");
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool addMenuItem(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a menu
        ///
        /// Any menu items that belong to this menu will be removed as well.
        ///
        /// @param menu  The name of the menu to remove
        ///
        /// @return True when the menu was removed, false when menu was not found
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenu(const sf::String& menu);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all menus
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllMenus();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a menu item
        ///
        /// @param menu      The name of the menu in which the menu item is located
        /// @param menuItem  The name of the menu item to remove
        ///
        /// @return True when the item was removed, false when menu or menuItem was not found
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenuItem(const sf::String& menu, const sf::String& menuItem);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text
        ///
        /// @param size  The new size of the text.
        ///              If the size is 0 (default) then the text will be scaled to fit in the menu bar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text
        ///
        /// @return The text size
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the minimum width of the submenus
        ///
        /// When a submenu is displayed, the width will be either this or the width of the longest text in the submenu.
        /// The default minimum width is 125 pixels.
        ///
        /// @param minimumWidth  minimum width of the submenus
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimumSubMenuWidth(float minimumWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the text and the side of the menu item
        ///
        /// @return minimum width of the submenus
        ///
        /// @see setMinimumSubMenuWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getMinimumSubMenuWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the menus open above or below the menu bar
        ///
        /// @param invertDirection  Should the menus open above the bar instead of below like it does by default?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setInvertedMenuDirection(bool invertDirection);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the menus open above or below the menu bar
        ///
        /// @return Do menus open above the bar instead of below like it does by default?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getInvertedMenuDirection() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a copy of all the menus and their menu items
        ///
        /// @return Map of menus and their items
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::map<sf::String, std::vector<sf::String>> getMenus() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the open menu when one of the menus is open
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void closeMenu();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// This function is called when the widget is added to a container.
        /// You should not call this function yourself.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setParent(Container* parent) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnWidget(sf::Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the mouse leaves the widget. If requested, a callback will be send.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseLeftWidget() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Signal& getSignal(std::string&& signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<MenuBar>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// One of the menu items was clicked.
        /// Optional parameters:
        ///     - The text of the clicked menu item
        ///     - List containing both the name of the menu and the menu item that was clicked
        SignalMenuItem onMenuItemClick = {"MenuItemClicked"};


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        struct Menu
        {
            Text text;
            std::vector<Text> menuItems;
            int selectedMenuItem = -1;
        };

        std::vector<Menu> m_menus;

        int m_visibleMenu = -1;

        unsigned int m_textSize = 0;

        float m_minimumSubMenuWidth = 125;

        bool m_invertedMenuDirection = false;

        Sprite m_spriteBackground;
        Sprite m_spriteItemBackground;
        Sprite m_spriteSelectedItemBackground;

        // Cached renderer properties
        Color m_backgroundColorCached;
        Color m_selectedBackgroundColorCached;
        Color m_textColorCached;
        Color m_selectedTextColorCached;
        float m_distanceToSideCached = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_MENU_BAR_HPP
