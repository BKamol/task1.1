#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool is_letter(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

bool is_correct(string filename)
{
    ifstream in(filename);
    int state = 0;
    char c;
    bool is_correct = true;
    int m; //счетчик длины идентификатора (должен быть меньше 2)
    int n; //счетчик длины числа (должно быть равно пяти, если не учитывать знак)
    int p; //счетчик кол-ва операций (не больше 3-х)

    while (in >> c && c != ' ' && is_correct)
    {
        switch (state)
        {
        case 0:
            if (is_letter(c))
            {
                state = 1;
                m = 1;
            }
            else
            {
                is_correct = false;
            }
            break;

        case 1:
            if (is_letter(c) || is_digit(c))
            {
                m++;
            }
            else if (c == ':' && m <= 2)
            {
                state = 2;
            }
            else
            {
                is_correct = false;
            }
            break;

        case 2:
            if (c == '=')
            {
                p = 0;
                state = 3;
            }
            else
            {
                is_correct = false;
            }
            break;

        case 3:
            if (is_digit(c))
            {
                state = 4;
                n = 1;
            }
            else if (c == '+' || c == '-')
            {
                state = 5;
                n = 1;
            }
            else if (is_letter(c))
            {
                state = 6;
                m = 1;
            }
            else
            {
                is_correct = false;
            }
            break;

        case 4:
            if (is_digit(c))
            {
                n++;
            }
            else if (c == ';' && n == 5)
            {
                state = 0;
            }
            else if ((c == '+' || c == '-' || c == '/' || c == '*') && n == 5 && p < 3)
            {
                state = 3;
                p++;
            }
            else
            {
                is_correct = false;
            }
            break;

        case 5:
            if (is_digit(c))
            {
                state = 4;
                n = 1;
            }
            else
            {
                is_correct = false;
            }
            break;

        case 6:
            if (is_letter(c) || is_digit(c))
            {
                m++;
            }
            else if (c == ';' && m <= 2)
            {
                state = 0;
            }
            else if ((c == '+' || c == '-' || c == '/' || c == '*') && m <= 2 && p < 3)
            {
                state = 3;
                p++;
            }
            else
            {
                is_correct = false;
            }
        }
    }

    in.close();

    return is_correct;
}

int main()
{
    cout << is_correct("program.txt");

}

