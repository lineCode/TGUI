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


#include <TGUI/Widgets/BoxLayoutRatios.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BoxLayoutRatios::BoxLayoutRatios(const Layout2d& size) :
        BoxLayout{size}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::add(const tgui::Widget::Ptr& widget, const sf::String& widgetName)
    {
        insert(m_widgets.size(), widget, 1, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::add(const tgui::Widget::Ptr& widget, float ratio, const sf::String& widgetName)
    {
        insert(m_widgets.size(), widget, ratio, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::insert(std::size_t index, const tgui::Widget::Ptr& widget, const sf::String& widgetName)
    {
        insert(index, widget, 1, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::insert(std::size_t index, const tgui::Widget::Ptr& widget, float ratio, const sf::String& widgetName)
    {
        if (index < m_ratios.size())
            m_ratios.insert(m_ratios.begin() + index, ratio);
        else
            m_ratios.push_back(ratio);

        BoxLayout::insert(index, widget, widgetName);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool BoxLayoutRatios::remove(std::size_t index)
    {
        if (index < m_ratios.size())
            m_ratios.erase(m_ratios.begin() + index);

        return BoxLayout::remove(index);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::removeAllWidgets()
    {
        BoxLayout::removeAllWidgets();
        m_ratios.clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::addSpace(float ratio)
    {
        insertSpace(m_widgets.size(), ratio);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BoxLayoutRatios::insertSpace(std::size_t index, float ratio)
    {
        insert(index, Group::create(), ratio, "#TGUI_INTERNAL$HorizontalLayoutSpace#");
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool BoxLayoutRatios::setRatio(Widget::Ptr widget, float ratio)
    {
        for (std::size_t i = 0; i < m_widgets.size(); ++i)
        {
            if (m_widgets[i] == widget)
                return setRatio(i, ratio);
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool BoxLayoutRatios::setRatio(std::size_t index, float ratio)
    {
        if (index >= m_ratios.size())
            return false;

        m_ratios[index] = ratio;
        updateWidgets();
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float BoxLayoutRatios::getRatio(Widget::Ptr widget) const
    {
        for (std::size_t i = 0; i < m_widgets.size(); ++i)
        {
            if (m_widgets[i] == widget)
                return getRatio(i);
        }

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float BoxLayoutRatios::getRatio(std::size_t index) const
    {
        if (index >= m_ratios.size())
            return false;

        return m_ratios[index];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
