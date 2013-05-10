/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Objects.hpp>
#include <TGUI/ClickableObject.hpp>
#include <TGUI/Label.hpp>
#include <TGUI/Button.hpp>
#include <TGUI/GroupObject.hpp>
#include <TGUI/ChildWindow.hpp>
#include <TGUI/MessageBox.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::MessageBox() :
    m_TextSize(16)
    {
        m_Callback.objectType = Type_MessageBox;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::MessageBox(const MessageBox& copy) :
    ChildWindow               (copy),
    m_ButtonConfigFileFilename(copy.m_ButtonConfigFileFilename),
    m_Buttons                 (copy.m_Buttons),
    m_TextSize                (copy.m_TextSize)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox::~MessageBox()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox& MessageBox::operator= (const MessageBox& right)
    {
        if (this != &right)
        {
            MessageBox temp(right);
            this->ChildWindow::operator=(right);

            std::swap(m_ButtonConfigFileFilename, temp.m_ButtonConfigFileFilename);
            std::swap(m_Buttons,                  temp.m_Buttons);
            std::swap(m_TextSize,                 temp.m_TextSize);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MessageBox* MessageBox::clone()
    {
        return new MessageBox(*this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool MessageBox::load(const std::string& configFileFilename)
    {
        // When everything is loaded successfully, this will become true.
        m_Loaded = false;

        // Create the text label if it doesn't exist yet
        if (get("MessageBoxText") == NULL)
        {
            Label::Ptr label(*this, "MessageBoxText");
            label->setTextSize(m_TextSize);
        }

        // Open the config file
        ConfigFile configFile;
        if (!configFile.open(configFileFilename))
        {
            TGUI_OUTPUT("TGUI error: Failed to open " + configFileFilename + ".");
            return false;
        }

        // Read the properties and their values (as strings)
        std::vector<std::string> properties;
        std::vector<std::string> values;
        if (!configFile.read("MessageBox", properties, values))
        {
            TGUI_OUTPUT("TGUI error: Failed to parse " + configFileFilename + ".");
            return false;
        }

        // Close the config file
        configFile.close();

        // Find the folder that contains the config file
        std::string configFileFolder = "";
        std::string::size_type slashPos = configFileFilename.find_last_of("/\\");
        if (slashPos != std::string::npos)
            configFileFolder = configFileFilename.substr(0, slashPos+1);

        bool childWindowPropertyFound = false;
        bool buttonPropertyFound = false;

        // Handle the read properties
        for (unsigned int i = 0; i < properties.size(); ++i)
        {
            std::string property = properties[i];
            std::string value = values[i];

            if (property == "textcolor")
            {
                Label::Ptr(get("MessageBoxText"))->setTextColor(configFile.readColor(value));
            }
            else if (property == "childwindow")
            {
                if ((value.length() < 3) || (value[0] != '"') || (value[value.length()-1] != '"'))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for Scrollbar in section ChatBox in " + configFileFilename + ".");
                    return false;
                }

                if (!ChildWindow::load(configFileFolder + value.substr(1, value.length()-2)))
                {
                    TGUI_OUTPUT("TGUI error: Failed to load the internal ChildWindow for MessageBox.");
                }
                else
                    childWindowPropertyFound = true;
            }
            else if (property == "button")
            {
                if ((value.length() < 3) || (value[0] != '"') || (value[value.length()-1] != '"'))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for Scrollbar in section ChatBox in " + configFileFilename + ".");
                    return false;
                }

                m_ButtonConfigFileFilename = configFileFolder + value.substr(1, value.length()-2);
                buttonPropertyFound = true;
            }
            else
            {
                TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section MessageBox in " + configFileFilename + ".");
            }
        }

        if (!childWindowPropertyFound)
        {
            TGUI_OUTPUT("TGUI error: Missing a ChildWindow property in section MessageBox in " + configFileFilename + ".");
            return false;
        }
        if (!buttonPropertyFound)
        {
            TGUI_OUTPUT("TGUI error: Missing a Button property in section MessageBox in " + configFileFilename + ".");
            return false;
        }

        return m_Loaded = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::setText(const sf::String& text)
    {
        if (m_Loaded)
        {
            Label::Ptr(get("MessageBoxText"))->setText(text);

            rearrange();
        }
        else
        {
            TGUI_OUTPUT("TGUI error: Failed to set the text. MessageBox was not loaded completely.");
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String MessageBox::getText()
    {
        if (m_Loaded)
            return Label::Ptr(get("MessageBoxText"))->getText();
        else
        {
            TGUI_OUTPUT("TGUI error: Failed to set the text. MessageBox was not loaded completely.");
            return "";
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::setTextSize(unsigned int size)
    {
        m_TextSize = size;

        if (m_Loaded)
        {
            Label::Ptr(get("MessageBoxText"))->setTextSize(size);

            for (unsigned int i = 0; i < m_Buttons.size(); ++i)
                m_Buttons[i]->setTextSize(m_TextSize);

            rearrange();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int MessageBox::getTextSize() const
    {
        return m_TextSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::addButton(const sf::String& caption)
    {
        if (m_Loaded)
        {
            Button::Ptr button(*this);
            button->load(m_ButtonConfigFileFilename);
            button->setTextSize(m_TextSize);
            button->setText(caption);
            button->bindCallbackEx(&MessageBox::ButtonClickedCallbackFunction, this, tgui::Button::LeftMouseClicked | tgui::Button::SpaceKeyPressed | tgui::Button::ReturnKeyPressed);

            m_Buttons.push_back(button);

            rearrange();
        }
        else // MessageBox wasn't loaded
        {
            TGUI_OUTPUT("TGUI error: Could not add a button. MessageBox was not loaded completely.");
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::rearrange()
    {
        if (!m_Loaded)
            return;

        Label::Ptr label = get("MessageBoxText");

        // Calculate the button size
        float buttonWidth = 5 * m_TextSize;
        float buttonHeight = m_TextSize * 10.0 / 8.0;
        for (unsigned int i = 0; i < m_Buttons.size(); ++i)
        {
            float width = sf::Text(m_Buttons[i]->getText(), *m_Buttons[i]->getTextFont(), m_TextSize).getLocalBounds().width;
            if (buttonWidth < width * 10.0 / 9.0)
                buttonWidth = width * 10.0 / 9.0;
        }

        // Calculate the space needed for the buttons
        float distance = buttonHeight * 2.0 / 3.0;
        float buttonsAreaWidth = distance;
        for (unsigned int i = 0; i < m_Buttons.size(); ++i)
        {
            m_Buttons[i]->setSize(buttonWidth, buttonHeight);
            buttonsAreaWidth += m_Buttons[i]->getSize().x + distance;
        }

        // Calculate the suggested size of the window
        float width = 2*distance + label->getSize().x;
        float height = 3*distance + label->getSize().y + buttonHeight;

        // Make sure the buttons fit inside the message box
        if (buttonsAreaWidth > width)
            width = buttonsAreaWidth;

        // Set the size of the window
        setSize(width, height);

        // Set the text on the correct position
        label->setPosition(distance, distance);

        // Set the buttons on the correct position
        float leftPosition = 0;
        float topPosition = 2*distance + label->getSize().y;
        for (unsigned int i = 0; i < m_Buttons.size(); ++i)
        {
            leftPosition += distance + ((width - buttonsAreaWidth) / (m_Buttons.size()+1));
            m_Buttons[i]->setPosition(leftPosition, topPosition);
            leftPosition += m_Buttons[i]->getSize().x;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void MessageBox::ButtonClickedCallbackFunction(const Callback& callback)
    {
        if (m_CallbackFunctions[ButtonClicked].empty() == false)
        {
            m_Callback.trigger = ButtonClicked;
            m_Callback.text    = static_cast<Button*>(callback.object)->getText();
            addCallback();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
