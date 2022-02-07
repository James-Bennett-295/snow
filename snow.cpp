#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using std::cout;
using std::string;

int randNum()
{
    FILE *randFile = fopen("/dev/random", "r");
    char character = getc(randFile);
    fclose(randFile);
    int num = (int)character;
    if (num < 0) num = -num;
    num %= 100;
    if (num == 0) num = 1;
    return num;
};

int getWinWidth()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
};

int getWinHeight()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
};

string genSnowLayer()
{
    string snowLayer;
    int winWidth = getWinWidth();
    while (snowLayer.length() < winWidth)
    {
        snowLayer += string(randNum(), ' ');
        snowLayer += "❄";
    };
    snowLayer = snowLayer.substr(0, winWidth-1);
    while (snowLayer[snowLayer.length()-1] != ' ') {
        snowLayer = snowLayer.substr(0, snowLayer.length()-1);
    };
    return snowLayer;
};

int main()
{
    int x = getWinHeight();
    string snowLayerArr[x+2] = {};
    int snowLayerArrLen = 0;
    while (x--)
    {
        snowLayerArr[snowLayerArrLen] = genSnowLayer();
        snowLayerArrLen++;
    };
    string oldSnowLayerArr[snowLayerArrLen] = {};
    while (true)
    {
        usleep(60000);
        for (int i = 0; i < snowLayerArrLen; i++)
        {
            oldSnowLayerArr[i] = snowLayerArr[i];
        };
        for (int i = snowLayerArrLen; i >= 0; i--)
        {
            snowLayerArr[i+1] = oldSnowLayerArr[i];
        };
        snowLayerArr[0] = genSnowLayer();
        for (int i = 0; i < snowLayerArrLen; i++)
        {
            cout << snowLayerArr[i] << '\n';
        };
    };
    return 0;
};
