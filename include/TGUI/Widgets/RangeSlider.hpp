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


#ifndef TGUI_RANGE_SLIDER_HPP
#define TGUI_RANGE_SLIDER_HPP


#include <TGUI/Widget.hpp>
#include <TGUI/Renderers/RangeSliderRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief RangeSlider widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API RangeSlider : public Widget
    {
    public:

        typedef std::shared_ptr<RangeSlider> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const RangeSlider> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RangeSlider();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new slider widget
        ///
        /// @param minimum  The minimum value of the slider
        /// @param maximum  The maximum value of the slider
        ///
        /// @return The new slider
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static RangeSlider::Ptr create(int minimum = 0, int maximum = 10);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another slider
        ///
        /// @param slider  The other slider
        ///
        /// @return The new slider
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static RangeSlider::Ptr copy(RangeSlider::ConstPtr slider);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RangeSliderRenderer* getSharedRenderer();
        const RangeSliderRenderer* getSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RangeSliderRenderer* getRenderer();
        const RangeSliderRenderer* getRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the slider
        ///
        /// @param size  The new size of the slider
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the full size of the slider
        ///
        /// This size also takes the thumb into account as opposed to getSize which just returns the track size.
        ///
        /// @return Full size of the slider
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the position where the widget is drawn and where the widget is placed
        ///
        /// This is a negative offset indicating the difference between the track and thumb position when the value equals
        /// the minimum.
        ///
        /// @return Offset of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getWidgetOffset() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a minimum value
        ///
        /// @param minimum  The new minimum value
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// When the maximum value is lower than the new minimum then it will be changed to this new minimum value.
        /// The default minimum value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimum(int minimum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum value
        ///
        /// @return The current minimum value
        ///
        /// The default minimum value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getMinimum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a maximum value
        ///
        /// @param maximum  The new maximum value
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// When the minimum value is higher than the new maximum then it will be changed to this new maximum value.
        /// The default maximum value is 10.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(int maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum value
        ///
        /// @return The current maximum value
        ///
        /// The default maximum value is 100.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getMaximum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the value where the selection starts
        ///
        /// @param value  The new selection start
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        /// When larger than SelectionEnd, SelectionEnd will be set to the value as well.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionStart(int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value where the selection starts
        ///
        /// @return The current selection start
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectionStart() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the value where the selection ends
        ///
        /// @param value  The new selection end
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        /// When smaller than SelectionStart, SelectionStart will be set to the value as well.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionEnd(int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value where the selection ends
        ///
        /// @return The current selection end
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectionEnd() const;


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
        void widgetFocused() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerDown() override;


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
        Signal& getSignal(std::string signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position of the thumb based on the current value of the slider
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateThumbPositions();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<RangeSlider>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalRange onRangeChange = {"RangeChanged"}; ///< Value of the slider changed. Optional parameter: new value


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::pair<sf::FloatRect, sf::FloatRect> m_thumbs;

        // When the mouse went down, did it go down on top of the thumb? If so, which one and where?
        unsigned int m_mouseDownOnThumb = 0;
        sf::Vector2f m_mouseDownOnThumbPos;

        int m_minimum = 0;
        int m_maximum = 10;
        int m_selectionStart = 0;
        int m_selectionEnd = 0;

        // Is the slider drawn vertically?
        bool m_verticalScroll = false;

        // Does the image lie vertically?
        bool m_verticalImage = false;

        Sprite m_spriteTrack;
        Sprite m_spriteTrackHover;
        Sprite m_spriteThumb;
        Sprite m_spriteThumbHover;

        // Cached renderer properties
        Borders m_bordersCached;
        Color   m_borderColorCached;
        Color   m_borderColorHoverCached;
        Color   m_thumbColorCached;
        Color   m_thumbColorHoverCached;
        Color   m_trackColorCached;
        Color   m_trackColorHoverCached;
        Color   m_selectedTrackColorCached;
        Color   m_selectedTrackColorHoverCached;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_RANGE_SLIDER_HPP
