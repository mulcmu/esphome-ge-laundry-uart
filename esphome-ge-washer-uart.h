
//class constructor based off of @mannkind
//ESPHomeRoombaComponent/ESPHomeRoombaComponent.h
//https://github.com/mannkind/ESPHomeRoombaComponent

#define USE_UART_DEBUGGER

#include "esphome.h"
#include <vector>
#include "esphome/components/uart/uart_debugger.h"


static const char *TAG = "component.ge_UART";

class component_geUART : 
        public PollingComponent,
        public UARTDevice,
        public CustomAPIDevice {

  public:
    Sensor *sensor_remainingTime;
    Sensor *sensor_cycleCount;
    TextSensor *textsensor_State;
    TextSensor *textsensor_SubState;
    TextSensor *textsensor_Cycle;
    TextSensor *textsensor_endOfCycle;
    TextSensor *textsensor_DrynessSetting;
    TextSensor *textsensor_HeatSetting;
    TextSensor *textsensor_SoilSetting;
    TextSensor *textsensor_TempSetting;
    TextSensor *textsensor_SpinSetting;
    TextSensor *textsensor_RinseSetting;
    TextSensor *textsensor_Door;
    TextSensor *textsensor_DoorLock;  
        
    static component_geUART* instance(UARTComponent *parent)
    {
        static component_geUART* INSTANCE = new component_geUART(parent);
        return INSTANCE;
    }

    //delay setup() so that dryer boards have booted completely before
    //starting to rx/tx on bus
    float get_setup_priority() const override 
    { 
        return esphome::setup_priority::LATE; 
    }

    void setup() override
    {
        ESP_LOGD(TAG, "setup().");
        
        rx_buf.reserve(128);
        
        textsensor_State->publish_state("Unknown");
        textsensor_Cycle->publish_state("Unknown");
        textsensor_SubState->publish_state("Unknown");
        textsensor_endOfCycle->publish_state("Unknown");
        textsensor_DrynessSetting->publish_state("Unknown");
        textsensor_HeatSetting->publish_state("Unknown");
        textsensor_SoilSetting->publish_state("Unknown");
        textsensor_TempSetting->publish_state("Unknown");
        textsensor_SpinSetting->publish_state("Unknown");
        textsensor_RinseSetting->publish_state("Unknown");   
        textsensor_Door->publish_state("Unknown");
        textsensor_DoorLock->publish_state("Unknown");        
        
        sensor_remainingTime->publish_state(NAN);
        sensor_cycleCount->publish_state(NAN);
        
        set_update_interval(5);
    }

    void update() override
    {

        while ( available() ) {
            read_byte(&b);

            if( (b == 0xe2) && (last_b==0xe1 || last_b==0xe3) )  {
                //uart::UARTDebug::log_hex(uart::UARTDirection::UART_DIRECTION_RX , rx_buf, ' ');
                process_packet();                
                rx_buf.clear();            
            }
            
            last_b=b;
            rx_buf.push_back(b);
            
            if(rx_buf.size() == rx_buf.capacity() )  {
                ESP_LOGV(TAG, "rx_buf was filled!");
                uart::UARTDebug::log_hex(uart::UARTDirection::UART_DIRECTION_RX , rx_buf, ':');
                rx_buf.clear();            
            }
                
        }
        
        
        
        
        
        
        
        if(millis() - millisProgress > 200)  {

            switch(erd) {
            case 0:
                write_array(erd2000);
                erd=1;
                break;
             case 1:
                write_array(erd2001);
                erd=2;
                break;
            case 2:
                write_array(erd2002);
                erd=3;
                break;
            case 3:
                //write_array(erd2003);
                erd=4;
                break;
            case 4:
                write_array(erd2007);
                erd=5;
                break;
            case 5:
                write_array(erd200A);
                erd=6;
                break;
            case 6:
                write_array(erd2012);
                erd=7;
                break; 
            case 7:
                write_array(erd2013);
                erd=8;
                break;                
            case 8:
                write_array(erd2015);
                erd=9;
                break; 
            case 9:
                write_array(erd2016);
                erd=10;
                break; 
            case 10:
                write_array(erd2017);
                erd=11;
                break; 
            case 11:
                write_array(erd2018);
                erd=12;
                break; 
            case 12:
                //write_array(erd204D);
                erd=13;
                break;
            case 13:
                //write_array(erd2050);
                erd=0;
                break;    
            }                
            millisProgress = millis();
        }
     }

        
  private: 
    uint8_t b=0;
    uint8_t last_b=0;
    unsigned long millisProgress=0;
    uint8_t erd=0;
    
    std::vector<uint8_t> rx_buf; 
   
    //Hardcoded packets to read these ERDs, see crc.py
    //U+ connect uses 0xBE, dryer sends to 0xBF (internal wifi module?)
    //destination is 0xC0 for dryer, use 0xBB as source
    //any occurrences of 0XE0, 0XE1, 0XE2 and 0XE3 in the data need escaped with 0XE0
   
    std::vector<uint8_t> fw_broadcast= {0XE2, 0XFF, 0X08, 0XBB, 0X01, 0X9A, 0X85, 0xE3};    //FW broadcast message
    std::vector<uint8_t> erd2000= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X00, 0X9E, 0X3E, 0xE3};    //State
    std::vector<uint8_t> erd2001= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X01, 0X8E, 0X1F, 0xE3};    //Sub State
    std::vector<uint8_t> erd2002= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X02, 0XBE, 0X7C, 0xE3};    //End of Cycle
    std::vector<uint8_t> erd2003= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X03, 0XAE, 0X5D, 0xE3};    //Cycle Count
    std::vector<uint8_t> erd2007= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X07, 0XEE, 0XD9, 0xE3};    //Cycle Time Remaining
    std::vector<uint8_t> erd200A= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X0A, 0X3F, 0X74, 0xE3};    //Cycle Setting
    std::vector<uint8_t> erd2012= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X12, 0XAC, 0X4D, 0xE3};    //Door State
    std::vector<uint8_t> erd2013= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X13, 0XBC, 0X6C, 0xE3};    //Washer Door Lock
    std::vector<uint8_t> erd2015= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X15, 0XDC, 0XAA, 0xE3};    //Washer Soil Level
    std::vector<uint8_t> erd2016= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X16, 0XEC, 0XC9, 0xE3};    //Washer Temp Level
    std::vector<uint8_t> erd2017= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X17, 0XFC, 0XE8, 0xE3};    //Washer Spin Level
    std::vector<uint8_t> erd2018= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X18, 0X0D, 0X07, 0xE3};    //Washer Rinse Option
    std::vector<uint8_t> erd204D= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X4D, 0X07, 0X57, 0xE3};    //Dryer Dryness Setting
    std::vector<uint8_t> erd2050= {0XE2, 0XC0, 0X0B, 0XBB, 0XF0, 0X01, 0X20, 0X50, 0XC4, 0XCB, 0xE3};    //Dryer Heat Setting  

    component_geUART(UARTComponent *parent) : PollingComponent(200), UARTDevice(parent) 
    {
        this->sensor_remainingTime = new Sensor();
        this->sensor_cycleCount = new Sensor();
        
        this->textsensor_State = new TextSensor();
        this->textsensor_SubState = new TextSensor();
        this->textsensor_Cycle = new TextSensor();
        this->textsensor_endOfCycle = new TextSensor();
        
        this->textsensor_DrynessSetting = new TextSensor();
        this->textsensor_HeatSetting = new TextSensor();  
        
        this->textsensor_SoilSetting= new TextSensor();  
        this->textsensor_TempSetting= new TextSensor();  
        this->textsensor_SpinSetting= new TextSensor();  
        this->textsensor_RinseSetting= new TextSensor();  
        
        this->textsensor_Door= new TextSensor();  
        this->textsensor_DoorLock= new TextSensor();  
    }
    
    uint16_t crc16geabus_bit(uint16_t crc, unsigned char const *mem, size_t len) {
        unsigned char const *data = mem;
        if (data == NULL)
            return 0xe300;
        for (size_t i = 0; i < len; i++) {
            crc ^= (uint16_t)data[i] << 8;
            for (unsigned k = 0; k < 8; k++) {
                crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
            }
        }
        return crc;
    }
        
    void process_packet()  {
        if(rx_buf[1]!=0xBB)
            return;
        
        if(rx_buf[4]!=0xF0 || rx_buf[6]!=0x20)
            return;
        
        if(rx_buf.size() > 10)  {
            //0x2000:  E2 BB 0D 24 F0 01 20 00 01 00 E6 88 E3
            if(rx_buf[7]==0x00)  {
                ESP_LOGD(TAG, "erd x2000: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00: //Idle screen off
                    case 0x01: //Standby, display on
                        textsensor_State->publish_state("Off");
                        break;
                    case 0x02: //Run
                        textsensor_State->publish_state("Running");
                        break;                    
                    case 0x03: //Paused
                        textsensor_State->publish_state("Paused");
                        break;                    
                    case 0x04: //EOC
                        textsensor_State->publish_state("Done");
                        break;                    
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2000 Unknown %X",rx_buf[9]);
                        textsensor_State->publish_state(buf);
                }
            }
            
            //0x2001:  E2 BB 0D 24 F0 01 20 01 01 00 D1 B8 E3  
            if(rx_buf[7]==0x01)  {
                ESP_LOGD(TAG, "erd x2001: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00: 
                        textsensor_SubState->publish_state("N/A");
                        break;
                    case 0x01: 
                        textsensor_SubState->publish_state("Fill");
                        break;
                    case 0x02:
                        textsensor_SubState->publish_state("Soak");
                        break;                    
                    case 0x03: 
                        textsensor_SubState->publish_state("Wash");
                        break;                    
                    case 0x04: 
                        textsensor_SubState->publish_state("Rinse");
                        break;   
                    case 0x05: 
                        textsensor_SubState->publish_state("Spin");
                        break;   
                    case 0x06: 
                        textsensor_SubState->publish_state("Drain");
                        break;   
                    case 0x07: 
                        textsensor_SubState->publish_state("Extra Spin");
                        break;   
                    case 0x08: 
                        textsensor_SubState->publish_state("Extra Rinse");
                        break;                  
                    case 0x09:
                        textsensor_SubState->publish_state("Tumble");
                        break;                    
                    case 0x0A: 
                        textsensor_SubState->publish_state("Load Detection");
                        break;                    
                    case 0x80: 
                        textsensor_SubState->publish_state("Drying");
                        break;   
                    case 0x81: 
                        textsensor_SubState->publish_state("Steam");
                        break;   
                    case 0x82: 
                        textsensor_SubState->publish_state("Cool Down");
                        break;   
                    case 0x83: 
                        textsensor_SubState->publish_state("Extended Tumble");
                        break;   
                    case 0x84: 
                        textsensor_SubState->publish_state("Damp");
                        break;  
                    case 0x85: 
                        textsensor_SubState->publish_state("Air Fluff");
                        break;                           
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2001 Unknown %X",rx_buf[9]);
                        textsensor_SubState->publish_state(buf);
                }
            }
            
            //0x2002:    E2 BB 0D 24 F0 01 20 02 01 00 88 E8 E3
            if(rx_buf[7]==0x02)  {
                ESP_LOGD(TAG, "erd x2002: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00: 
                        textsensor_endOfCycle->publish_state("False");
                        break;   
                    case 0x01: 
                        textsensor_endOfCycle->publish_state("True");
                        break;                           
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2002 Unknown %X",rx_buf[9]);
                        textsensor_endOfCycle->publish_state(buf);
                }
            }
            
            //DEBUG RX: <E2 BE 0E 24 F0 01 20 07 02 0B EA 72 3F E3 E1>
            //INFO Parsed: <GEAFrame(src=0x24, dst=0xBE, payload=<F0 01 20 07 02 0B EA>, ack=True>
            //INFO Parsed payload: <ERDCommand(command=<ERDCommandID.READ: 0xF0>, erds=[0x2007:<0B EA>])>
            
            //Nothing in the packet would be escaped 0xe0 until [9] but this would be 15 hours
            //of remaining time which is implausible.  If [10] is escape character error is at most
            //3 seconds so ignore potential problem.
            if(rx_buf[7]==0x07)  {
                uint16_t seconds = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                float minutes = seconds / 60.0;
                sensor_remainingTime->publish_state(minutes);
            }
            
            if(rx_buf[7]==0x03)  {
                uint16_t cycles = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                sensor_cycleCount->publish_state(cycles);
            }            
            
            
            //0x200A:  E2 BB 0D 24 F0 01 20 0A 01 06 41 8F E3
            if(rx_buf[7]==0x0A)  {
                switch (rx_buf[9])  {
                    case 0x89:
                        textsensor_Cycle->publish_state("Mixed Load");
                        break;
                    case 0x0D:
                        textsensor_Cycle->publish_state("Delicates");
                        break;
                    case 0x80:
                        textsensor_Cycle->publish_state("Cottons");
                        break;
                    case 0x0B:
                        textsensor_Cycle->publish_state("Jeans");
                        break;
                    case 0x8B:
                        textsensor_Cycle->publish_state("Casuals");
                        break;
                    case 0x88:
                        textsensor_Cycle->publish_state("Quick Dry");
                        break;
                    case 0x06:
                        textsensor_Cycle->publish_state("Towels");
                        break;
                    case 0x04:
                        textsensor_Cycle->publish_state("Bulky");
                        break;
                    case 0x05:
                        textsensor_Cycle->publish_state("Sanitize");
                        break;
                    case 0x85:
                        textsensor_Cycle->publish_state("Air Fluff");
                        break;
                    case 0x8C:
                        textsensor_Cycle->publish_state("Warm Up");
                        break;
                    case 0x83:
                        textsensor_Cycle->publish_state("Timed Dry");
                        break;
                    case 0x14:
                        textsensor_Cycle->publish_state("Colors");
                        break;
                    case 0x09:
                        textsensor_Cycle->publish_state("Whites");
                        break;
                    case 0x82:
                        textsensor_Cycle->publish_state("Active Wear");
                        break;
                    case 0x1D:
                        textsensor_Cycle->publish_state("Quick Wash");
                        break;
                    case 0x02:
                        textsensor_Cycle->publish_state("Drain & Spin");
                        break;
                    case 0x1A:
                        textsensor_Cycle->publish_state("Deep Clean");
                        break;                        
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 200A Unknown %X",rx_buf[9]);
                        textsensor_Cycle->publish_state(buf);
                }
                        
            }
            
            //0x2012:  Door
            if(rx_buf[7]==0x12)  {
                ESP_LOGD(TAG, "erd x2012: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00: 
                        textsensor_Door->publish_state("Open");
                        break;
                    case 0x01: 
                        textsensor_Door->publish_state("Closed");
                        break;
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2012 Unknown %X",rx_buf[9]);
                        textsensor_Door->publish_state(buf);
                }
            }
            
            //0x2013:  Washer Door Lock
            if(rx_buf[7]==0x13)  {
                ESP_LOGD(TAG, "erd x2013: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00: 
                        textsensor_DoorLock->publish_state("Unlocked");
                        break;
                    case 0x01: 
                        textsensor_DoorLock->publish_state("Locked");
                        break;
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2013 Unknown %X",rx_buf[9]);
                        textsensor_DoorLock->publish_state(buf);
                }
            }            
        
            //0x2015:  washer soil
            if(rx_buf[7]==0x15)  {
                ESP_LOGD(TAG, "erd x2015: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x01: 
                        textsensor_SoilSetting->publish_state("Light");
                        break;
                    case 0x02: 
                        textsensor_SoilSetting->publish_state("Normal");
                        break;
                    case 0x03:  
                        textsensor_SoilSetting->publish_state("Heavy");                    
                        break;
                    case 0x04: 
                        textsensor_SoilSetting->publish_state("Extra Heavy");                    
                        break;       
                    case 0x05: //occurs for drain & spin cycle
                        textsensor_SoilSetting->publish_state("N/A");                    
                        break;                          
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2015 Unknown %X",rx_buf[9]);
                        textsensor_SoilSetting->publish_state(buf);
                }
            }
            
            //0x2016:  washer temp
            if(rx_buf[7]==0x16)  {
                ESP_LOGD(TAG, "erd x2016: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x06:  //occurs for drain & spin cycle
                        textsensor_TempSetting->publish_state("N/A");
                        break;
                    case 0x10:
                        textsensor_TempSetting->publish_state("Tap Cold");
                        break;
                    case 0x11:
                        textsensor_TempSetting->publish_state("Cold");
                        break;
                    case 0x12:
                        textsensor_TempSetting->publish_state("Cool");
                        break;
                    case 0x13:
                        textsensor_TempSetting->publish_state("Colors");
                        break;
                    case 0x14:
                        textsensor_TempSetting->publish_state("Warm");
                        break;
                    case 0x15:
                        textsensor_TempSetting->publish_state("Hot");
                        break;  
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2016 Unknown %X",rx_buf[9]);
                        textsensor_TempSetting->publish_state(buf);
                }
            }
            
            //0x2017: washer spin
            if(rx_buf[7]==0x17)  {
                ESP_LOGD(TAG, "erd x2017: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00:
                        textsensor_SpinSetting->publish_state("No Spin");
                        break;
                    case 0x02:
                        textsensor_SpinSetting->publish_state("Normal");
                        break;
                    case 0x03:
                        textsensor_SpinSetting->publish_state("More");
                        break;
                    case 0x04:
                        textsensor_SpinSetting->publish_state("Max");
                        break;                    
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2017 Unknown %X",rx_buf[9]);
                        textsensor_SpinSetting->publish_state(buf);
                }
            }
            
            //0x2018:  washer rinse, bit mapped, warm rinse didn't show up
            if(rx_buf[7]==0x18)  {
                ESP_LOGD(TAG, "erd x2018: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00:
                        textsensor_RinseSetting->publish_state("Standard Rinse");
                        break;
                    case 0x01:
                        textsensor_RinseSetting->publish_state("Deep Rinse");
                        break;
                    case 0x02:
                        textsensor_RinseSetting->publish_state("Extra Rinse");
                        break;
                    case 0x03:
                        textsensor_RinseSetting->publish_state("Deep + Extra Rinse");
                        break;                   
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2018 Unknown %X",rx_buf[9]);
                        textsensor_RinseSetting->publish_state(buf);
                }
            }
                        
            //0x204D:  E2 BB 0D 24 F0 01 20 4D 01 04 F9 F0 E3  
            if(rx_buf[7]==0x4D)  {
                ESP_LOGD(TAG, "erd x204D: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x00: 
                        textsensor_DrynessSetting->publish_state("N/A");
                        break;                       
                    case 0x01: 
                        textsensor_DrynessSetting->publish_state("Damp");
                        break;              
                    case 0x02: 
                        textsensor_DrynessSetting->publish_state("Less Dry");
                        break;                    
                    case 0x03: 
                        textsensor_DrynessSetting->publish_state("Dry");
                        break;
                    case 0x04: 
                        textsensor_DrynessSetting->publish_state("More Dry");
                        break;                    
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 204D Unknown %X",rx_buf[9]);
                        textsensor_DrynessSetting->publish_state(buf);
                }
            }
            
            //0x2050:  E2 BB 0D 24 F0 01 20 50 01 05 E8 E0 E3 E3  
            if(rx_buf[7]==0x50)  {
                ESP_LOGD(TAG, "erd x2050: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x01: 
                        textsensor_HeatSetting->publish_state("Air Fluff");
                        break;
                    case 0x03: 
                        textsensor_HeatSetting->publish_state("Low");
                        break;
                    case 0x04: 
                        textsensor_HeatSetting->publish_state("Medium");                    
                        break;
                    case 0x05: 
                        textsensor_HeatSetting->publish_state("High");                    
                        break;
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 2050 Unknown %X",rx_buf[9]);
                        textsensor_HeatSetting->publish_state(buf);
                }                
            }
            
        }
     }
};
    
