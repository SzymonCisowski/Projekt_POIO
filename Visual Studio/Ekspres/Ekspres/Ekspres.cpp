#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace sf;
using namespace std;




class Button
{
private:
    RectangleShape button;
    Text text;
public:
    Button() {};
    Button(string t, Vector2f size,int charSize,Color bgColor,Color textColor)
    {
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);
        button.setSize(size);
        button.setFillColor(bgColor);


    }
    void setFont(Font &font)
    {
        text.setFont(font);
    }

    void setBackColor(Color color)
    {
        button.setFillColor(color);
    }
    void setTextColor(Color color)
    {
        text.setFillColor(color);
    }
    string getText()
    {
        return text.getString();
    }
    void setPosition(Vector2f pos)
    {
        button.setPosition(pos);

    }
    void drawTo(RenderWindow& window)
    {
        window.draw(button);
        window.draw(text);
    }
    void setText(string t)
    {
        text.setString(t);
    }
     bool isMouseOver(RenderWindow& window)
    {
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;
        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;
        float btnxPosWidth = button.getPosition().x+button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if (mouseX<btnxPosWidth && mouseX> btnPosX && mouseY< btnyPosHeight && mouseY>btnPosY)
        {
            return true;
        }
        return false;
    }
     void centerText()
     {
         Vector2f pos = button.getPosition();
         float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
         float yPos = (pos.y + button.getLocalBounds().height / 3) - (text.getLocalBounds().height / 2)+3;
         text.setPosition({ xPos,yPos });
     }
};

class Image_Button
{
private:
    Sprite image;
    Texture t1;
    Text text;

public:
    Image_Button() {};
    Image_Button(string t, string path, int charSize, Color textColor)
    {
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);
        t1.loadFromFile(path);
        Sprite tmp(t1);
        image=tmp;
    }
    void setFont(Font& font)
    {
        text.setFont(font);
    }


    void setTextColor(Color color)
    {
        text.setFillColor(color);
    }
    void setPosition(Vector2f pos)
    {
        image.setPosition(pos);
        float xPos = pos.x + image.getLocalBounds().width / 3 -15;
        float yPos = pos.y + image.getLocalBounds().height;
        text.setPosition({ xPos,yPos });
    }
    void drawTo(RenderWindow& window)
    {
        window.draw(image);
        window.draw(text);
    }
    void setText(string t)
    {
        text.setString(t);
    }

    bool isMouseOver(RenderWindow& window)
    {
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;
        float btnPosX = image.getPosition().x;
        float btnPosY = image.getPosition().y;
        float btnxPosWidth = image.getPosition().x + image.getLocalBounds().width;
        float btnyPosHeight = image.getPosition().y + image.getLocalBounds().height;

        if (mouseX<btnxPosWidth && mouseX> btnPosX && mouseY< btnyPosHeight && mouseY>btnPosY)
        {
            return true;
        }
        return false;
    }
};

class coffee
{
    private:
    
    int milk;
    int power;
    int size;
    int quantity;
    string name;
public:
    Image_Button img;
    coffee(int quantity = 0) {};
    coffee(string n, int m, int p, int s, Image_Button i) : name(n), milk(m), power(p), size(s), img(i) { quantity = 0; }
    friend class coffee_machine;


    void setPower(int p)
    {
        power = p;
    }
    int getPower()
    {
        return power;
    }
    int getSize()
    {
        return size;
    }
    void setSize(int s)
    {
        size = s;
    }
    int getMilk()
    {
        return milk;
    }
    void setMilk(int m)
    {
        milk = m;
    }
    int getQuantity()
    {
        return quantity;
    }
    void coffeeCounting()
    {
        quantity++;
    }
};

class coffee_machine
{
public:
    coffee tab[3];
    int filter;
    int coffee_counter()
    {
        int c=0;
        for (int i = 0;i < 3;i++)
        {
            c += tab[i].getQuantity();
        }
        return c;
    }
    coffee_machine() {};
    void load_from_file(string path, Image_Button &b1, Image_Button &b2, Image_Button &b3)
    {
        tab[0].name = "Espresso";
        tab[1].name = "Caffe Latte";
        tab[2].name = "Cappuccino";
        tab[0].img = b1;
        tab[1].img = b2;
        tab[2].img = b3;

        fstream file;
        int i = 0;
        string tmp;
        file.open(path, fstream::in);
        do
        {

            if (i == 3)
            {
                file >> tab[0].quantity;
                file >> tab[1].quantity;
                file >> tab[2].quantity;
                file >> filter;
                break;
            }
            else
            {
                file >> tab[i].milk;
                file >> tab[i].power;
                file >> tab[i].size;
                i++;
            }
            
        } while (!file.eof());
        file.close();
    }
    void restore_default_settings(Image_Button& b1, Image_Button& b2, Image_Button& b3,Font &f)
    {
        fstream restore, file;
        restore.open("default_settings.txt", fstream::in);
        file.open("coffee_database.txt", fstream::out);
        int i = 0;

        do
        {
                string tmp;
                restore >> tmp;
                file << tmp << " ";
                restore >> tmp;
                file << tmp << " ";
                restore >> tmp;
                file << tmp << endl;

        } while (!restore.eof());

        file << "0 ";
        file << "0 ";
        file << "0 ";
        file << "0";
        for (int k = 0;k < 3;k++)
        {
            tab[k].quantity = 0;
        }
        filter = 0;
        load_from_file("coffee_database.txt", b1, b2, b3);
        tab[0].img.setPosition({ 300,220 });
        tab[0].img.setFont(f);
        tab[1].img.setPosition({ 300,220 });
        tab[1].img.setFont(f);
        tab[2].img.setPosition({ 300,220 });
        tab[2].img.setFont(f);
        restore.close();
        file.close();
    }
    bool check_filter()
    { 
        if (filter >= 5)
        { 
            filter = 0;
            return true;
           
        }
        return false;
    }
    void save_to_file()
    {
        fstream file;
        file.open("coffee_database.txt", fstream::out);
        int i = 0;
        do
        {

            if (i == 3)
            {
                file << tab[0].quantity;
                file << " ";
                file << tab[1].quantity;
                file << " ";
                file << tab[2].quantity;
                file << " ";
                file << filter;
                break;
            }
            else
            {
                file << tab[i].milk;
                file << " ";
                file << tab[i].power;
                file << " ";
                file << tab[i].size;
                i++;
                file << endl;
            }

        } while (!file.eof());
        file.close();
    }
 
};
enum state
{
    initiate = 0,
    start = 1,
    cleaning = 2,
    menu = 3,
    make_coffee_menu = 4,
    edit_database = 5,
    device_settings = 6,
    stop = 7,
    set_coffee_parameters = 8,
    make_coffee = 9,
    coffee_statistic = 10,
    restore_settings = 11,
    change_filter = 12

};

state states = initiate;

int main()
{
    RenderWindow window;
    window.create(VideoMode(800, 800), "Ekspres do kawy");
    Font arial;
    arial.loadFromFile("arial.ttf");
    Texture t1,t2;
    t1.loadFromFile("images/background.jpg");
    t2.loadFromFile("images/cleaning.gif");
    Sprite background(t1), clean(t2);
    sf::Color color_brown(205, 133, 63);
    sf::Color color_dark_brown(160, 82, 45);
    sf::Color color_grey(192, 192, 192);
    Button btn1("OFF", { 140, 40 }, 20, Color::Red, Color::White);
    Button btn2("Make coffee", { 250, 40 }, 20, color_brown, Color::White);
    Button btn3("Edit coffee database", { 250, 40 }, 20, color_brown, Color::White);
    Button btn4("Device settings", { 250, 40 }, 20,color_brown, Color::White);
    Image_Button btn5("Espresso", "images/espresso.png", 20, Color::Black);
    Image_Button btn6("Caffe Latte", "images/latte.png", 20, Color::Black);
    Image_Button btn7("Cappuccino", "images/cappuccino.png", 20, Color::Black);
    Image_Button btn8("", "images/arrow_right.png", 20, Color::Black);
    Image_Button btn9("", "images/arrow_left.png", 20, Color::Black);
    Image_Button btn10("", "images/plus.png", 20, Color::Black);
    Image_Button btn11("", "images/minus.png", 20, Color::Black);
    Image_Button btn12("", "images/plus.png", 20, Color::Black);
    Image_Button btn13("", "images/minus.png", 20, Color::Black);
    Image_Button btn14("", "images/plus.png", 20, Color::Black);
    Image_Button btn15("", "images/minus.png", 20, Color::Black);
    coffee c1("Espresso", 0, 4, 40, btn5);
    coffee c2("Caffe Latte", 80, 2, 150, btn6);
    coffee c3("Cappuccino", 50, 3, 100, btn7);

    btn1.setPosition({ 320,10 });
    btn1.setFont(arial);
    btn1.centerText();
    btn2.setPosition({ 280, 150 });
    btn2.setFont(arial);
    btn3.setPosition({ 280, 350 });
    btn3.setFont(arial);
    btn4.setPosition({ 280, 550 });
    btn4.setFont(arial);

    btn8.setPosition({ 600, 300 });
    btn9.setPosition({ 150, 300 });
    btn10.setPosition({ 550, 480 });
    btn11.setPosition({ 200, 480 });
    btn12.setPosition({ 550, 550 });
    btn13.setPosition({ 200, 550 });
    btn14.setPosition({ 550, 620 });
    btn15.setPosition({ 200, 620 });
    coffee_machine c_m;
    int counter = 0;
    int progress = 0;

    while (window.isOpen())
    {

        switch (states)
        {
        case initiate:
        {
            window.draw(background);
            btn1.drawTo(window);
            c_m.load_from_file("coffee_database.txt", btn5, btn6, btn7);
            c_m.tab[0].img.setPosition({ 300,220 });
            c_m.tab[0].img.setFont(arial);
            c_m.tab[1].img.setPosition({ 300,220 });
            c_m.tab[1].img.setFont(arial);
            c_m.tab[2].img.setPosition({ 300,220 });
            c_m.tab[2].img.setFont(arial);
            break;
        }
        case start:
        {
            btn1.setBackColor(Color::Green);
            btn1.setText("ON");
            btn1.centerText();
            btn1.drawTo(window);
            states = cleaning;
            break;
        }
        case cleaning:
        {
            Text text;
            window.clear();
            window.draw(background);
            text.setCharacterSize(40);
            text.setString("Coffee Machine Cleaning!");
            text.setPosition(160, 200);
            text.setFont(arial);
            text.setFillColor(Color::Black);
            window.draw(text);

            btn1.drawTo(window);
            clean.setPosition(200, 200);
            window.draw(clean);
            window.display();
            Sleep(3000);
            if (btn1.getText() == "ON")
            {
                states = menu;
                if (c_m.check_filter())
                {
                    states = change_filter;
                }
            }
            else if (btn1.getText() == "OFF")
            {
                states = initiate;
                c_m.save_to_file();
            }
            break;
        }
        case menu:
        {
            btn2.setText("Make coffee");
            btn2.centerText();
            btn3.setText("Edit coffee database");
            btn3.centerText();
            btn4.setText("Device settings");
            btn4.centerText();
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            
            btn1.drawTo(window);
            btn2.drawTo(window);
            btn3.drawTo(window);
            btn4.drawTo(window);

            break;
        }

        case make_coffee_menu:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);
            c_m.tab[counter].img.drawTo(window);
            btn8.drawTo(window);
            btn9.drawTo(window);
            break;
        }
        case set_coffee_parameters:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);
            c_m.tab[counter].img.drawTo(window);
            btn10.drawTo(window);
            btn11.drawTo(window);
            btn12.drawTo(window);
            btn13.drawTo(window);
            Text text;
            char buf[128];
            text.setCharacterSize(24);
            sprintf_s(buf, "Coffee size: %d ml", c_m.tab[counter].getSize());
            string out = buf;
            text.setString(out);
            text.setPosition(300, 490);
            text.setFont(arial);
            text.setFillColor(Color::Black);
            window.draw(text);

            Text text2;
            char buf2[128];
            text2.setCharacterSize(24);
            sprintf_s(buf2, "Coffee power: %d", c_m.tab[counter].getPower());
            string out2 = buf2;
            text2.setString(out2);
            text2.setPosition(300, 560);
            text2.setFont(arial);
            text2.setFillColor(Color::Black);
            window.draw(text2);

            Text text3;
            char buf3[128];
            text3.setCharacterSize(24);
            sprintf_s(buf3, "Amount of milk: %d%c", c_m.tab[counter].getMilk(),'%');
            string out3 = buf3;
            text3.setString(out3);
            text3.setPosition(300, 630);
            text3.setFont(arial);
            text3.setFillColor(Color::Black);
            window.draw(text3);

            break;
        }
        case make_coffee:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);
            c_m.tab[counter].img.drawTo(window);
            if (progress < 100) progress++; Sleep(50);
            Text text;
            char buf[128];
            text.setCharacterSize(24);
            sprintf_s(buf, "Wait! Your coffee is being prepared!: %d%c", progress,'%');
            string out = buf;
            text.setString(out);
            text.setPosition(190, 490);
            text.setFont(arial);
            text.setFillColor(Color::Black);
            window.draw(text);
            
            if (progress == 100)
            {
                window.clear();
                window.draw(background);
                btn1.setBackColor(Color::Green);
                btn1.drawTo(window);
                c_m.tab[counter].img.drawTo(window);
                text.setPosition(290, 490);
                text.setString("Your coffee is ready!!!");
                window.draw(text);
                
                window.display();
                Sleep(3000);
                states = menu;
                progress = 0;
                c_m.load_from_file("coffee_database.txt", btn5, btn6, btn7);
                c_m.tab[counter].coffeeCounting();
                c_m.filter++;
                c_m.save_to_file();
                counter = 0;
                c_m.tab[0].img.setPosition({ 300,220 });
                c_m.tab[0].img.setFont(arial);
                c_m.tab[1].img.setPosition({ 300,220 });
                c_m.tab[1].img.setFont(arial);
                c_m.tab[2].img.setPosition({ 300,220 });
                c_m.tab[2].img.setFont(arial);
            }
            

            break;
        }
        case edit_database:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);
            c_m.tab[counter].img.drawTo(window);
            btn10.drawTo(window);
            btn11.drawTo(window);
            btn12.drawTo(window);
            btn13.drawTo(window);
            btn14.drawTo(window);
            btn15.drawTo(window);
            btn8.drawTo(window);
            btn9.drawTo(window);
            Text text;
            char buf[128];
            text.setCharacterSize(24);
            sprintf_s(buf, "Coffee size: %d ml", c_m.tab[counter].getSize());
            string out = buf;
            text.setString(out);
            text.setPosition(300, 490);
            text.setFont(arial);
            text.setFillColor(Color::Black);
            window.draw(text);

            Text text2;
            char buf2[128];
            text2.setCharacterSize(24);
            sprintf_s(buf2, "Coffee power: %d", c_m.tab[counter].getPower());
            string out2 = buf2;
            text2.setString(out2);
            text2.setPosition(300, 560);
            text2.setFont(arial);
            text2.setFillColor(Color::Black);
            window.draw(text2);

            Text text3;
            char buf3[128];
            text3.setCharacterSize(24);
            sprintf_s(buf3, "Amount of milk: %d%c", c_m.tab[counter].getMilk(), '%');
            string out3 = buf3;
            text3.setString(out3);
            text3.setPosition(300, 630);
            text3.setFont(arial);
            text3.setFillColor(Color::Black);
            window.draw(text3);

            btn2.setText("Confirm");
            btn2.centerText();
            btn2.drawTo(window);

            break;
        }
        case device_settings:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);
            btn2.setText("Factory settings");
            btn2.centerText();
            btn2.drawTo(window);
            btn3.setText("Change Filter");
            btn3.centerText();
            btn3.drawTo(window);
            btn4.setText("Coffee statistic");
            btn4.centerText();
            btn4.drawTo(window);
            break;
        }
        case coffee_statistic:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);


            Text text1,text2,text3,text4;
            char buf[128];
            sprintf_s(buf, "Total number of coffees: %d", c_m.coffee_counter());
            string out = buf;
            text1.setString(out);
            text1.setPosition(200, 190);
            text1.setFont(arial);
            text1.setFillColor(Color::Black);
            window.draw(text1);
            
            sprintf_s(buf, "Total number of espresso: %d", c_m.tab[0].getQuantity());
            out = buf;
            text2.setString(out);
            text2.setPosition(200, 290);
            text2.setFont(arial);
            text2.setFillColor(Color::Black);
            window.draw(text2);
           
            sprintf_s(buf, "Total number of cappuccino: %d", c_m.tab[1].getQuantity());
            out = buf;
            text3.setString(out);
            text3.setPosition(200, 390);
            text3.setFont(arial);
            text3.setFillColor(Color::Black);
            window.draw(text3);
           
            sprintf_s(buf, "Total number of caffe latte: %d", c_m.tab[2].getQuantity());
            out = buf;
            text4.setString(out);
            text4.setPosition(200, 490);
            text4.setFont(arial);
            text4.setFillColor(Color::Black);
            window.draw(text4);
            window.display();
            Sleep(4000);
            states = menu;
            break;
        }
        case change_filter:
        {   
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);

            Text text1;
            text1.setString("Please insert new water filter!");
            text1.setCharacterSize(40);
            text1.setPosition(150, 300);
            text1.setFont(arial);
            text1.setFillColor(Color::Black);
            window.draw(text1);
            btn4.setText("Confirm");
            btn4.centerText();
            btn4.drawTo(window);
            c_m.save_to_file();
            
            break;
        }
        case restore_settings:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Green);
            btn1.drawTo(window);
            c_m.restore_default_settings(btn5, btn6, btn7,arial);

            Text text1;
            text1.setString("Default settings restored!");
            text1.setCharacterSize(40);
            text1.setPosition(200, 300);
            text1.setFont(arial);
            text1.setFillColor(Color::Black);
            window.draw(text1);
            window.display();
            Sleep(4000);
            states = menu;
            break;
        }
        case stop:
        {
            window.clear();
            window.draw(background);
            btn1.setBackColor(Color::Red);
            btn1.setText("OFF");
            btn1.centerText();
            btn1.drawTo(window);
            states = cleaning;
            break;
        }

        
        }

        Event e;

        while (window.pollEvent(e))
        {
            switch (e.type)
            {
            case Event::MouseMoved:
                if (btn1.isMouseOver(window))
                {
                    btn1.setBackColor(Color::Black);
                }
                else
                {
                    btn1.setBackColor(Color::Red);
                }
                if (btn2.isMouseOver(window))
                {
                    btn2.setBackColor(color_dark_brown);
                }
                else
                {
                    btn2.setBackColor(color_brown);
                }
                if (btn3.isMouseOver(window))
                {
                    btn3.setBackColor(color_dark_brown);
                }
                else
                {
                    btn3.setBackColor(color_brown);
                }
                if (btn4.isMouseOver(window))
                {
                    btn4.setBackColor(color_dark_brown);
                }
                else
                {
                    btn4.setBackColor(color_brown);
                }
                if (c_m.tab[counter].img.isMouseOver(window))
                {
                    c_m.tab[counter].img.setTextColor(color_grey);
                }
                else
                {
                    c_m.tab[counter].img.setTextColor(Color::Black);
                }
              



                
                break;
            case Event::MouseButtonPressed:
                if (btn1.isMouseOver(window) and states==initiate) states = start;
                if (btn1.isMouseOver(window) and states!=start and states!= make_coffee) states = stop;
                if (btn2.isMouseOver(window) and states == device_settings) states = restore_settings;
                if (btn2.isMouseOver(window) and states == menu) states = make_coffee_menu;
                if (btn2.isMouseOver(window) and states == edit_database)
                {
                    states = menu;
                    c_m.save_to_file();
                }
                //if (btn2.isMouseOver(window) and states == device_settings) states = make_coffee_menu;
                if (btn3.isMouseOver(window) and states == menu) states = edit_database;
                if (btn3.isMouseOver(window) and states == device_settings) states = change_filter;
                if (btn4.isMouseOver(window) and states == device_settings) states = coffee_statistic;
                if (btn4.isMouseOver(window) and states == menu) states = device_settings;
                if (btn4.isMouseOver(window) and states == change_filter) states = menu;
                if ((c_m.tab[counter].img.isMouseOver(window)) and states == make_coffee_menu) states = set_coffee_parameters;
                else if ((c_m.tab[counter].img.isMouseOver(window)) and states == set_coffee_parameters) states = make_coffee;
                if (btn10.isMouseOver(window))
                {
                    if(c_m.tab[counter].getSize() < 200)
                        c_m.tab[counter].setSize(c_m.tab[counter].getSize() + 10);
                }
                if (btn11.isMouseOver(window))
                {
                    if (c_m.tab[counter].getSize() > 10)
                        c_m.tab[counter].setSize(c_m.tab[counter].getSize() - 10);
                }
                if (btn12.isMouseOver(window))
                {
                    if (c_m.tab[counter].getPower() < 5)
                        c_m.tab[counter].setPower(c_m.tab[counter].getPower() + 1);
                }
                if (btn13.isMouseOver(window))
                {
                    if (c_m.tab[counter].getPower() > 1)
                        c_m.tab[counter].setPower(c_m.tab[counter].getPower() - 1);
                }
                if (btn14.isMouseOver(window))
                {
                    if (c_m.tab[counter].getMilk() < 100)
                        c_m.tab[counter].setMilk(c_m.tab[counter].getMilk() + 10);
                }
                if (btn15.isMouseOver(window))
                {
                    if (c_m.tab[counter].getMilk() > 0)
                        c_m.tab[counter].setMilk(c_m.tab[counter].getMilk() - 10);
                }
                if (btn8.isMouseOver(window) and (states == make_coffee_menu or states == edit_database))
                {
                    counter++;
                    if (counter > 2) counter = 0;
                }
                if (btn9.isMouseOver(window) and (states == make_coffee_menu or states == edit_database))
                {
                    counter--;
                    if (counter < 0) counter = 2;
                }
                    break;
            }
            
        }


        
        window.display();

        
    }
    return 0;
}