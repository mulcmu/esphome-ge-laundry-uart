
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
    Sensor *sensor_remainingtime;

    //TODO Unknown at startup, Idle if not running and after door opened, Running while drying, Cycle finished
    //cool down
    TextSensor *textsensor_dryerState;
    TextSensor *textsensor_dryerCycle;
    
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
        
        StateText.reserve(32);
        rx_buf.reserve(128);
        tx_buf.reserve(128);
        
        //flush();
        //write_str("\r\n\r\nM155 S10\r\n");  //TODO any setup tx writes
        
        textsensor_dryerState->publish_state("Unknown");
        textsensor_dryerCycle->publish_state("Unknown");
        sensor_remainingtime->publish_state(NAN);
        
        //TODO HA services if needed, keep tumbling or wrinkle care ???
        //register_service(&component_geUART::set_bed_setpoint, "set_bed_setpoint", {"temp_degC"});
     }

    void update() override
    {
        //ESP_LOGV(TAG, "update().");

        //Debug, try to print out separate packets
        while ( available() ) {
            read_byte(&b);

            if( (b == 0xe2) && (last_b==0xe1 || last_b==0xe3) )  {
                uart::UARTDebug::log_hex(uart::UARTDirection::UART_DIRECTION_RX , rx_buf, ' ');
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
       
        if(millis() - millisProgress > 150)  {
            //write_str("M27\r\nM31\r\n");
            millisProgress = millis();
        }

    }

//    void set_bed_setpoint(int temp_degC) {
//       ESP_LOGD(TAG, "set_bed_setpoint().");
//    }

        
  private: 
    String StateText;
    uint8_t b=0;
    uint8_t last_b=0;
    unsigned long millisProgress=0;
    
    std::vector<uint8_t> rx_buf; 
    std::vector<uint8_t> tx_buf; 
   
    component_geUART(UARTComponent *parent) : PollingComponent(2000), UARTDevice(parent) 
    {
       
        this->sensor_remainingtime = new Sensor();
        this->textsensor_dryerState = new TextSensor();
        this->textsensor_dryerCycle = new TextSensor();
    }
    
    void process_packet()  {
        
        //DEBUG RX: <E2 BE 0D 24 F5 01 20 0A 01 8C 45 80 E3 E1>
        //INFO Parsed: <GEAFrame(src=0x24, dst=0xBE, payload=<F5 01 20 0A 01 8C>, ack=True>
        //INFO Parsed payload: <ERDCommand(command=<ERDCommandID.PUBLISH: 0xF5>, erds=[0x200A:<8C>])>
        if(rx_buf.size() > 12)  {
            if(rx_buf[4]==0xF5 && rx_buf[6]==0x20 && rx_buf[7]==0x0A)  {
            ESP_LOGI(TAG, "Found ERD 0x200A with published value: %X", rx_buf[9]);
                switch (rx_buf[9])  {
                    case 0x89:
                        textsensor_dryerCycle->publish_state("Mixed Load");
                        break;
                    case 0x0D:
                        textsensor_dryerCycle->publish_state("Delicates");
                        break;
                    case 0x80:
                        textsensor_dryerCycle->publish_state("Cottons");
                        break;
                    case 0x0B:
                        textsensor_dryerCycle->publish_state("Jeans");
                        break;
                    case 0x8B:
                        textsensor_dryerCycle->publish_state("Casuals");
                        break;
                    case 0x88:
                        textsensor_dryerCycle->publish_state("Quick Dry");
                        break;
                    case 0x06:
                        textsensor_dryerCycle->publish_state("Towels");
                        break;
                    case 0x04:
                        textsensor_dryerCycle->publish_state("Bulky");
                        break;
                    case 0x05:
                        textsensor_dryerCycle->publish_state("Sanitize");
                        break;
                    case 0x85:
                        textsensor_dryerCycle->publish_state("Air Fluff");
                        break;
                    case 0x8C:
                        textsensor_dryerCycle->publish_state("Warm Up");
                        break;
                    case 0x83:
                        textsensor_dryerCycle->publish_state("Timed Dry");
                        break;
                    default:
                        char buf[32];
                        sprintf(buf, "ERD 200A Unknown %X",rx_buf[9]);
                        textsensor_dryerCycle->publish_state(buf);
                }
                        
            }
        
            //DEBUG RX: <E2 BE 0E 24 F0 01 20 07 02 0B EA 72 3F E3 E1>
            //INFO Parsed: <GEAFrame(src=0x24, dst=0xBE, payload=<F0 01 20 07 02 0B EA>, ack=True>
            //INFO Parsed payload: <ERDCommand(command=<ERDCommandID.READ: 0xF0>, erds=[0x2007:<0B EA>])>        
            if(rx_buf[4]==0xF0 && rx_buf[6]==0x20 && rx_buf[7]==0x07)  {
                uint16_t seconds = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                float minutes = seconds / 60.0;
                sensor_remainingtime->publish_state(minutes);
            }
        }
        

        
        
    }

};
    
