/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_CONTAINER_HPP
#define TGUI_CONTAINER_HPP


#include <list>

#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    struct Callback;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Parent class for widgets that store multiple widgets.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Container : public Widget
    {
      public:

        typedef SharedWidgetPtr<Container> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container(const Container& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container& operator= (const Container& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the global font.
        ///
        /// This font will be used by all widgets that are created after calling this function.
        ///
        /// \param filename  Path of the font file to load
        ///
        /// \return True if loading succeeded, false if it failed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setGlobalFont(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the global font.
        ///
        /// This font will be used by all widgets that are created after calling this function.
        ///
        /// \param font  Font to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setGlobalFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the global font.
        ///
        /// This is the font that is used for newly created widget by default.
        ///
        /// \return global font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font& getGlobalFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of all the widgets.
        ///
        /// \return Vector of all widget pointers
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector< Widget::Ptr >& getWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of the names of all the widgets.
        ///
        /// \return Vector of all widget names
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<sf::String>& getWidgetNames();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Adds a widget to the container.
        ///
        /// \param widgetPtr   Pointer to the widget you would like to add
        /// \param widgetName  If you want to access the widget later then you must do this with this name
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container); // Create a picture and add it to the container
        /// container.remove(pic);             // Remove the picture from the container
        /// container.add(pic);                // Add the picture to the container again
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void add(const Widget::Ptr& widgetPtr, const sf::String& widgetName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to an earlier created widget.
        ///
        /// \param widgetName The name that was given to the widget when it was added to the container.
        ///
        /// \return Pointer to the earlier created widget
        ///
        /// \warning This function will return nullptr when an unknown widget name was passed.
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container, "picName");
        /// tgui::Picture::Ptr pic2 = container.get("picName");
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr get(const sf::String& widgetName) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to an earlier created widget.
        ///
        /// \param widgetName The name that was given to the widget when it was added to the container.
        ///
        /// \return Pointer to the earlier created widget.
        ///         The pointer will already be casted to the desired type.
        ///
        /// \warning This function will return nullptr when an unknown widget name was passed.
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container, "picName");
        /// tgui::Picture::Ptr pic2 = container.get<tgui::Picture>("picName");
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <class T>
        typename T::Ptr get(const sf::String& widgetName) const
        {
            return typename T::Ptr(get(widgetName));
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Makes a copy of any existing widget and returns the pointer to the new widget.
        ///
        /// \param oldWidget     A pointer to the old widget.
        /// \param newWidgetName If you want to access the widget later then you must do this with this name
        ///
        /// \return Pointer to the new widget
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container, "picName");
        /// tgui::Picture::Ptr pic2 = container.copy(pic, "picName_2");
        /// tgui::Picture::Ptr pic3 = container.copy(container.get("picName"), "picName_3");
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr copy(const Widget::Ptr& oldWidget, const sf::String& newWidgetName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a single widget that was added to the container.
        ///
        /// \param widget  Pointer to the widget to remove
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container, "picName");
        /// tgui::Picture::Ptr pic2(container, "picName2");
        /// container.remove(pic);
        /// container.remove(container.get("picName2"));
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a single widget that was added to the container.
        ///
        /// \param widget  Pointer to the widget to remove
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(Widget* widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all widgets that were added to the container.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the name of a widget.
        ///
        /// \param widget  Widget of which the name should be changed
        /// \param name    New name for the widget
        ///
        /// \return True when the name was changed, false when the widget wasn't part of this container.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setWidgetName(const Widget::Ptr& widget, const std::string& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the name of a widget.
        ///
        /// \param widget  Widget of which the name should be retrieved
        /// \param name    Name for the widget
        ///
        /// \return False is returned when the widget wasn't part of this container.
        ///         In this case the name parameter is left unchanged.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getWidgetName(const Widget::Ptr& widget, std::string& name) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focuses a widget.
        ///
        /// The previously focused widget will be unfocused.
        ///
        /// \param widget  The widget that has to be focused.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusWidget(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focuses a widget.
        ///
        /// The previously focused widget will be unfocused.
        ///
        /// \param widget  The widget that has to be focused.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusWidget(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focuses the next widget.
        ///
        /// The currently focused widget will be unfocused, even if it was the only widget.
        /// When no widget was focused, the first widget in the container will be focused.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusNextWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focuses the previous widget.
        ///
        /// The currently focused widget will be unfocused, even if it was the only widget.
        /// When no widget was focused, the last widget in the container will be focused.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusPreviousWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unfocus all the widgets.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Uncheck all the radio buttons.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheckRadioButtons();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places a widget before all other widgets.
        ///
        /// \param widget  The widget that should be moved to the front
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToFront(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places a widget behind all other widgets.
        ///
        /// \param widget  The widget that should be moved to the back
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToBack(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Bind a function to the callbacks of all child widgets.
        ///
        /// When a child widget tells this widget about the callback then the global callback function(s) will be called.
        /// If no global callback function has been bound then the callback is passed to the parent of this widget.
        ///
        /// \param func  Pointer to a free function with a reference to a Callback widget as parameter.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void bindGlobalCallback(std::function<void(const Callback&)> func);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Bind a function to the callbacks of all child widgets.
        ///
        /// When a child widget tells this widget about the callback then the global callback function(s) will be called.
        /// If no global callback function has been bound then the callback is passed to the parent of this widget.
        ///
        /// \param func      Pointer to a member function with a reference to a Callback widget as parameter.
        /// \param classPtr  Pointer to the widget of the class.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        void bindGlobalCallback(void (T::*func)(const Callback&), T* const classPtr)
        {
            m_GlobalCallbackFunctions.push_back(std::bind(func, classPtr, std::placeholders::_1));
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unbind the global callback function(s).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void unbindGlobalCallback();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads a form from a file.
        ///
        /// The widgets will be loaded and added to the container.
        /// Note that even when this function fails, some widgets might have been loaded already.
        ///
        /// \param filename  Filename of the widget file that is to be loaded
        ///
        /// \return
        ///        - true on success
        ///        - false when the file could not be opened
        ///        - false when the file contains a mistake
        ///        - false when one of the widgets couldn't be loaded
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool loadWidgetsFromFile(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Save the widgets to a file.
        ///
        /// \param filename  Filename of the widget file that is to be created
        ///
        /// \return
        ///        - true on success
        ///        - false when the file couldn't be created
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool saveWidgetsToFile(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the distance between the position of the container and a widget that would be drawn inside
        ///        this container on relative position (0,0).
        ///
        /// \return Offset of the widgets in the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getWidgetsOffset() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is used internally by child widget to alert there parent about a callback.
        // If it reaches the gui, then the callback can be obtained by calling the pollCallback function of the gui.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void addChildCallback(const Callback& callback);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void textEntered(sf::Uint32 key);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetUnfocused();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When this function is called then all the widgets receive the event (if there are widgets).
        // The function returns true when the event is consumed and false when the event was ignored by all widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool handleEvent(sf::Event& event);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Focuses the next widget in the container. If the last widget was focused then all widgets will be unfocused and
        // this function will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusNextWidgetInContainer();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When the tab key is pressed then this function is called. The focus will move to the next widget (if there is one).
        // This function will only work when tabKeyUsageEnabled is true.
        // The function will return true when another widget was focused.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool tabKeyPressed();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Checks above which widget the mouse is standing.
        // If there is no widget below the mouse then this function will return a null pointer.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr mouseOnWhichWidget(float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will call the draw function from all the widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void drawWidgetContainer(sf::RenderTarget* target, const sf::RenderStates& states = sf::RenderStates::Default) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::vector<Widget::Ptr> m_Widgets;
        std::vector<sf::String>  m_ObjName;

        // The id of the focused widget
        unsigned int m_FocusedWidget;

        sf::Font m_GlobalFont;

        // Is the container focused? If so, then one of the widgets inside the container may be focused
        bool m_ContainerFocused;

        // A list that stores all functions that receive callbacks triggered by child widgets
        std::list< std::function<void(const Callback&)> > m_GlobalCallbackFunctions;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API GuiContainer : public Container
    {
      public:

        typedef SharedWidgetPtr<Container> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unbind the global callback function(s).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unbindGlobalCallback();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Doesn't has any effect.
        ///
        /// \param width   Ignored
        /// \param height  Ignored
        ///
        /// The window size cannot be changed by a widget.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the container (same size as the window).
        ///
        /// \return Size of the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /// Returns a nullptr.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual GuiContainer* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /// Returns false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /// This function does nothing.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        sf::RenderWindow* m_Window;


        friend class Gui;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CONTAINER_HPP
