# Set up and use a Rev 2.x board

These examples use the maintained [ESPHome GEA component](https://github.com/mguaylam/esphome-gea) to connect the adapter to Home Assistant.

[Back to the project overview](../README.md) · [Recommended PCB Rev 2.2](../pcb/rev2.2/README.md) · [Revision history](../pcb/README.md)

## Choose a configuration

| Configuration | Connection | Typical use |
| --- | --- | --- |
| [`gea2.yaml`](gea2.yaml) | GPIO5 TX and GPIO10 RX, inverted, 19,200 baud | Rev 2.x reference for GEA2 appliances. |
| [`gea3.yaml`](gea3.yaml) | GPIO21 TX and GPIO20 RX, non-inverted, 230,400 baud | Rev 2.x reference for GEA3 appliances. |

The appliance model determines whether it uses GEA2 or GEA3. Start with a configuration already known to work with your appliance rather than trying both while connected.

## Prepare ESPHome

If ESPHome is not installed yet, start with the official [ESPHome installation guide](https://esphome.io/install/) and [getting-started guide](https://esphome.io/install/getting-started/).

1. Copy the matching YAML file into your ESPHome configuration directory.
2. Change the `name` and `upper_name` substitutions near the top of the file.
3. Add these values to the `secrets.yaml` file in the same directory:

```yaml
wifi_ssid: "..."
wifi_password: "..."
esp_home_ota_pw: "..."
```

You can use the ESPHome Device Builder or the command line. The examples are starting points, so appliance-specific entities may need to be added or changed.

## First flash

Rev 2.x boards do not have USB. The first flash needs a **3.3 V logic** USB-to-UART adapter connected to the unpopulated J2 holes or the J3 Tag-Connect pads. Do not connect 5 V to these pins.

| J2 pin | Board signal | Connect to |
| --- | --- | --- |
| 1, square pad | 3.3 V | A regulated 3.3 V source capable of powering the ESP32 |
| 2 | Ground | Adapter ground |
| 3 | Boot | Ground only while entering the bootloader |
| 4 | Board TX | Adapter RX |
| 5 | Board RX | Adapter TX |
| 6 | Enable | Optional reset control |

Use only one power source at a time. Some USB-to-UART adapters cannot provide enough 3.3 V current for an ESP32 Wi-Fi board; use a separate regulated 3.3 V supply when needed and connect its ground to the adapter ground.

1. Connect J2 Boot to Ground.
2. Apply 3.3 V power, or power-cycle the board if it was already on. This starts the serial bootloader.
3. In ESPHome Device Builder, choose **Install** and select the serial adapter. With the command line, run:

   ```console
   esphome run your-config.yaml --device /dev/cu.your-usb-serial-device
   ```

4. When the upload finishes, disconnect Boot from Ground and power-cycle the board.

Later updates can be installed over Wi-Fi from ESPHome Device Builder. From the command line, run the same `esphome run` command and choose the network device when prompted.

## Connect to the appliance

1. Disconnect the programming adapter and install the board in its enclosure.
2. With the appliance off, connect the adapter to its service port. This connector is not Ethernet.
3. Power the appliance and wait for the board to join Wi-Fi.
4. Add the discovered ESPHome device in Home Assistant.

With the supplied configurations, the green LED shows Wi-Fi connection and the yellow LED shows GEA bus activity. The red LED is available to ESPHome but is not assigned a status by these examples.
