#include "InputBox.h"
#include <iostream>
void InputBox::inputText(sf::Event event)
{
	if (((double)std::clock() - (double)lastLetter) / (double)CLOCKS_PER_SEC > 0.15)
	{
		std::string pText = text.getString();
		if (event.key.code == sf::Keyboard::BackSpace)
		{
			int i = pText.length() - 1;
			if (i >= 0)
			{
				std::string nText;
				for (int j = 0; j < i; j++)
				{
					nText += pText[j];
				}
				text.setString(nText);
			}
		}
		else if (48 <= event.text.unicode && event.text.unicode < 58)
		{
			lastLetter = std::clock();
			pText += static_cast<char>(event.text.unicode);
			text.setString(pText);
		}	
	}
}

void InputBox::toggleActive()
{
	if (!active)
	{
		box.setFillColor(box.getFillColor() + sf::Color(50, 50, 50));
		active = true;
	}
	else
	{
		box.setFillColor(box.getFillColor() - sf::Color(50, 50, 50,0));
		active = false;
	}
}

bool InputBox::getActive()
{
	return active;
}

InputBox::InputBox(sf::Vector2f _pos, std::string _text, sf::Vector2f _size)
{
	lastLetter = std::clock();
	font.loadFromFile("arial.ttf");
	pos = _pos;
	text.setFont(font);
	text.setString(_text);
	text.setCharacterSize(11);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(0, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	box.setFillColor(sf::Color(200, 200, 200));
	box.setSize(_size);
	active = false;
}

std::string InputBox::getText()
{
	return text.getString();
}

InputBox::operator int() const
{
	return std::stoi((std::string)text.getString());
}

InputBox::operator float() const
{
	return std::stof((std::string)text.getString());
}

