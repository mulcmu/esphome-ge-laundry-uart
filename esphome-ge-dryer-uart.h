
//class constructor based off of @mannkind
//ESPHomeRoombaComponent/ESPHomeRoombaComponent.h
//https://github.com/mannkind/ESPHomeRoombaComponent

#include "esphome.h"

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
        
        StateText.reserve(32);
         
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

        int16_t distance;
        uint16_t voltage;
        bool publishJson;
        
        while ( available() ) {
            char c = read();
        }
       
        //if(millis() - millisProgress > PROGRESS_INTERVAL)  {
        //    write_str("M27\r\nM31\r\n");
        //    millisProgress = millis();
        //}

    }

//    void set_bed_setpoint(int temp_degC) {
//       ESP_LOGD(TAG, "set_bed_setpoint().");
//    }

        
  private: 
    String StateText;
   
    component_geUART(UARTComponent *parent) : PollingComponent(2000), UARTDevice(parent) 
    {
       
        this->sensor_remainingtime = new Sensor();
        this->textsensor_dryerState = new TextSensor();

    }

};
    
