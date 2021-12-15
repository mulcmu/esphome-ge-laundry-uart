
//class constructor based off of @mannkind
//ESPHomeRoombaComponent/ESPHomeRoombaComponent.h
//https://github.com/mannkind/ESPHomeRoombaComponent

#include "esphome.h"
#include <vector>
//#include "uart_debugger.h"


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
        
        //StateText.reserve(32);
         
        //flush();
        //write_str("\r\n\r\nM155 S10\r\n");  //TODO any setup tx writes
        
        textsensor_dryerState->publish_state("Unknown");
        sensor_remainingtime->publish_state(NAN);
        
        //TODO HA services if needed, keep tumbling or wrinkle care ???
        //register_service(&component_geUART::set_bed_setpoint, "set_bed_setpoint",
        //{"temp_degC"});
     }

    void update() override
    {
        ESP_LOGV(TAG, "update().");

        while ( available() ) {
            uint8_t b;
            read_byte(&b);
            rx_buf.push_back(b);
            if(rx_buf.size() == rx_buf.capacity() )  {
                //UARTDevice::UARTDebug::log_hex(UARTDevice::UARTDebug::UART_DIRECTION_RX , rx_buf, ':');
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
    //String StateText;
    
    unsigned long millisProgress=0;
    
    std::vector<uint8_t> rx_buf; 
    std::vector<uint8_t> tx_buf; 
   
    component_geUART(UARTComponent *parent) : PollingComponent(2000), UARTDevice(parent) 
    {
       
        this->sensor_remainingtime = new Sensor();
        this->textsensor_dryerState = new TextSensor();

    }

};
    
