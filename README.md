# coding_challenge
Accelerometer data from real BLE tag and detect movement  
# This code will fetch data from beacon_packets.txt and process the packet, it will not fetch fromr real bluetooth device.
1. Steps to compile:
   cc beacon_code.c
2. Make sure to keep beacon_packets.txt in same path.
   chmod 777 beacon_packets.txt
3. Run code
   ./a.out

# Sample output
Beacon Accelerometer Frame Detected
    X-axis fff4, Y-axis 000f, Z-axis ff00
    Battery Level 100
    Mac address 37 : 72 : a3 : 3f : 23 : ac

    Detected movement.

Beacon Accelerometer Frame Detected
    X-axis fff6, Y-axis 0011, Z-axis ff00
    Battery Level 100
    Mac address 37 : 72 : a3 : 3f : 23 : ac

    Detected movement.

Beacon Accelerometer Frame Detected
    X-axis fff4, Y-axis 0011, Z-axis ff03
    Battery Level 100
    Mac address 37 : 72 : a3 : 3f : 23 : ac

    Detected movement.
