#include "Bluetooth.h"
void Bluetooth ::Read_data()
{
}

void Bluetooth ::Send_data()
{
}

bool Bluetooth ::split_data(String &title, int &data)
{
    static String sbuf = "";
    if (BT.available())
    {
        char cbuf = (char)BT.read();
        if (cbuf != ',' && cbuf != '\n')
            sbuf += cbuf;
        else
        {
            title = sbuf.substring(0, sbuf.indexOf('='));
            data = sbuf.substring(sbuf.indexOf('=') + 1).toInt();
            sbuf = "";
            return true;
        }
    }
    return false;
}