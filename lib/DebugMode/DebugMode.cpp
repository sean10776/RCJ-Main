#include "DebugMode.h"

/*!
 * @brief 初始化
 * @param debug
 *        決定是否連上ESP
 * @param ir
 *        讀取ir物件
 * @param li
 *        讀取Light物件
 * @param cam
 *        讀取Camera物件
 */
void DebugMode::init(bool debug, IR *ir, Light *li, Camera *cam)
{
    if (debug)
        ESP.begin(115200);
    Serial.begin(115200);
    sd.init();
    _ir = ir;
    _li = li;
    _cam = cam;
}

/*!
 * @brief 解析回傳資料 str -> str + int
 * @param title
 *        回傳名稱參照
 * @param value
 *        回傳值參照
 * @return 有值回傳(True)/ (False)
 */
bool DebugMode::Command(String &title, int &value)
{
    static String sbuf = "";
    if (ESP.available())
    {
        char cbuf = (char)ESP.read();
        if (cbuf != ',' && cbuf != '\n')
            sbuf += cbuf;
        else
        {
            title = sbuf.substring(0, sbuf.indexOf('='));
            value = sbuf.substring(sbuf.indexOf('=') + 1).toInt();
            sbuf = "";
            return true;
        }
    }
    return false;
}

/*!
 * @brief 資料轉換 str -> str + int
 * @param data
 *        資料
 * @param value
 *        資料數值
 */
void DebugMode::datatrans(String data, int *value)
{
    String sbuf = "";
    int count = 0;
    for (uint16_t i = 0; i < data.length(); i++)
    {
        char cbuf = data[i];
        if (cbuf != ',' && cbuf != '\n')
            sbuf += cbuf;
        else
        {
            *(value + count) = sbuf.substring(sbuf.indexOf('=') + 1).toInt();
            sbuf = "";
            count++;
        }
    }
}

/*!
 * @brief 傳資訊給ESP
 */
void DebugMode::SendData()
{
    String data = "";
    if (_ir)
        data += (String("IR=") + _ir->GetVal(false, false) + ',');
    if (_cam)
        data += (String("Cam=") + _cam->GetVal(0.5) + ',');
    if (_li)
    {
        int val[10] = {0};
        _li->SetVal(val);
        for (int i = 0; i < 10; i++)
        {
            data += (String("L") + i + "=" + val[i] + ',');
        }
    }
    ESP.print(data);
    ESP.flush();
}

/*!
 * @brief 調整參數+讀取SD資料
 * @return 完成return True
 */
bool DebugMode::Debug()
{
    String irdata = "", lidata = "", camdata = "", valuedata = "";
    if (_debug)
    {
        while (true)
        {
            SendData();
            String title = "";
            int val = 0;
            if (Command(title, val))
            {
                Serial.print(String(title) + " : " + val);
                if (title == "IR")
                {
                    irdata = String(title) + "=" + val + "\n";
                    _ir->Set_offset(val);
                }
                if (title == "Camera")
                    camdata = String(title) + "=" + val + "\n";
                if (title == "Pwr")
                {
                    valuedata = String(title) + "=" + val + "\n";
                }
                if (title == "LightPer")
                {
                    valuedata += String(title) + "=" + val + "\n";
                }
            }
            if (title == "Done	")
            {
                Serial.println("****Saving****");
                int lival[10] = {0};
                _li->SetVal(lival);
                for (int i = 0; i < 10; i++)
                    lidata += String("L") + i + "=" + lival[i] + "\n";
                sd.SDwrite("IR.txt", irdata);
                sd.SDwrite("Light.txt", lidata);
                sd.SDwrite("Camera.txt", camdata);
                sd.SDwrite("Value.txt", valuedata);
                delay(5);
                return true;
            }
        }
    }
    else
    {
        bool ir_offset = sd.SDread("IR.txt", irdata);
        bool li_offset = sd.SDread("Light.txt", lidata);
        bool cam_offset = sd.SDread("Camera.txt", camdata);
        bool value_offset = sd.SDread("Value.txt", valuedata);
        int data[10] = {0};
        if (ir_offset)
        {
            datatrans(irdata, data);
            _ir->Set_offset(data[0]);
        }
        if (li_offset)
        {
            datatrans(lidata, data);
            _li->SetVal(data, true);
        }
        if (cam_offset)
            ;
        if (value_offset)
        {
            datatrans(valuedata, data);
            maxspeed = data[0];
            Light_Per = data[1];
        }
    }
    return true;
}