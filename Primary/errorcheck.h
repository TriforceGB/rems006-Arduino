// Used to turn error codes into readable messages
// Messages from Library Repo
bool errorCheck(uint8_t errorCode)
{
    if (errorCode == 0)
    {
        return true;
    }
    else
    {
        Serial.print("Modbus error: " + String(errorCode) + "-");
        if (errorCode == 1)
        {
            Serial.println("Invalid Unit ID");
        }
        else if (errorCode == 2)
        {
            Serial.println("Invalid buffer");
        }
        else if (errorCode == 3)
        {
            Serial.println("Invalid quantity");
        }
        else if (errorCode == 4)
        {
            Serial.println("Response timeout");
        }
        else if (errorCode == 5)
        {
            Serial.println("Frame error");
        }
        else if (errorCode == 6)
        {
            Serial.println("CRC error");
        }
        else if (errorCode == 7)
        {
            Serial.println("Unknown communication error");
        }
        else if (errorCode == 8)
        {
            Serial.println("Unexpected unit ID in response");
        }
        else if (errorCode == 9)
        {
            Serial.println("Exception response");
        }
        else if (errorCode == 10)
        {
            Serial.println("Unexpected function code in response");
        }
        else if (errorCode == 11)
        {
            Serial.println("Unexpected response length");
        }
        else if (errorCode == 12)
        {
            Serial.println("Unexpected byte count in response");
        }
        else if (errorCode == 13)
        {
            Serial.println("Unexpected data address in response");
        }
        else if (errorCode == 14)
        {
            Serial.println("Unexpected data value in response");
        }
        else if (errorCode == 15)
        {
            Serial.println("Unexpected quantity in response");
        }
        return false;
    }
}