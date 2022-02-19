
def crc16(data: bytes) -> int:
    crc = 0xE300
    
    for b in data:
        crc ^= b << 8
    
        for j in range(0, 8):
            if crc & 0b1000000000000000:
                crc <<= 1
                crc ^= 0x1021
            else:
                crc <<= 1
    
            crc &= 0xFFFF
            
        print(f"{b:#0{4}X}" + ', ' , end='')
    
    print(f"{(crc >> 8):#0{4}X}" + ", " + f"{(crc & 0xFF):#0{4}X}" + ', 0xE3};', end='')

destination = 0xC0 #washer
#destination = 0x24 #dryer

sender = 0xBB

print("std::vector<uint8_t> fw_broadcast= {", end='')
crc16([0xE2, 0xFF , 0x08 , sender , 0x01])
print("    //FW broadcast message")

print("std::vector<uint8_t> erd2000= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x00])
print("    //State")

print("std::vector<uint8_t> erd2001= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x01])
print("    //Sub State")

print("std::vector<uint8_t> erd2002= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x02])
print("    //End of Cycle")

print("std::vector<uint8_t> erd2003= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x03])
print("    //Cycle Count")

print("std::vector<uint8_t> erd2007= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x07])
print("    //Cycle Time Remaining")

print("std::vector<uint8_t> erd200A= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x0A])
print("    //Cycle Setting")

print("std::vector<uint8_t> erd2012= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x12])
print("    //Door State")

print("std::vector<uint8_t> erd2013= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x13])
print("    //Washer Door Lock")

print("std::vector<uint8_t> erd2015= {", end='')
crc16([0xe2, destination, 0x0B, sender, 0xf0, 0x1, 0x20, 0x15]  )
print("    //Washer Soil Level")

print("std::vector<uint8_t> erd2016= {", end='')
crc16([0xe2, destination, 0x0B, sender, 0xf0, 0x1, 0x20, 0x16] )
print("    //Washer Temp Level")

print("std::vector<uint8_t> erd2017= {", end='')
crc16([0xe2, destination, 0x0B, sender, 0xf0, 0x1, 0x20, 0x17]  )
print("    //Washer Spin Level")

print("std::vector<uint8_t> erd2018= {", end='')
crc16([0xe2, destination, 0x0B, sender, 0xf0, 0x1, 0x20, 0x18]  )
print("    //Washer Rinse Option")

print("std::vector<uint8_t> erd204D= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x4D])
print("    //Dryer Dryness Setting")

print("std::vector<uint8_t> erd2050= {", end='')
crc16([0xE2, destination, 0x0B, sender, 0xF0, 0x01, 0x20, 0x50])
print("    //Dryer Heat Setting")


 
  

