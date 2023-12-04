#include<stdio.h>                                                               
#include <string.h>                                                         

/* Beacon accelerometer frame */                                                             
typedef struct beacon_frame_acc_mtr_s {                                         
    unsigned char data_length;                                                  
    unsigned char frame_data_type;                                              
    unsigned char flag_data;                                                    
    unsigned char flag_data_length;                                             
    unsigned char list_of_service;                                              
    unsigned char uuid1_data[2];                                                
    unsigned char uuid_length;                                                  
    unsigned char service_data;                                                 
    unsigned char uuid2_data[2];                                                
    unsigned char frame_type;                                                   
    unsigned char version_num;                                                  
    unsigned char battery_level;                                                
    unsigned char  x_axis[2];                                                   
    unsigned char y_axis[2];                                                    
    unsigned char  z_axis[2];                                                   
    char mac_add[6];                                                            
} beacon_frame_acc_mtr_t;        

/* Beacon frame */
typedef struct beacon_frame_s {                                                 
    unsigned char data_length;                                                  
    unsigned char frame_data_type;                                              
    unsigned char flag_data;                                                    
    unsigned char flag_data_length;                                             
    unsigned char manufacture_data;                                             
    unsigned char company_id[2];                                                
    unsigned char beacon_type[2];                                               
    unsigned char uuid[16];                                                     
    unsigned char major[2];                                                     
    unsigned char minor[2];                                                     
    unsigned char rssi;                                                         
} beacon_frame_t;                                                               
                                                                                
main() {                                                                        
                                                                                
    beacon_frame_t *beacon_frame = NULL;                                        
    beacon_frame_acc_mtr_t *beacon_acc_frame = NULL;                            
    char line_buffer[129] = {0};                                                
    int line_len = 129;                                                         
    int count = 0;                                                              
    char temp[10] = {0};                                                        
    unsigned char data_int[129] = {0};                                          
    int i = 0, idx = 0;                                                         
    unsigned int val = 0;                                                       
    unsigned char  beacon_flag = 0;                                             
    unsigned short int x = 0, y = 0, z = 0;                                     
    unsigned short int p_x = 0, p_y = 0, p_z = 0;

    FILE *fp = fopen("beacon_packets.txt", "r");                                    
                                                                                
    while(fgets(line_buffer, line_len, fp)) {                                   
        /* Get Packet data and convert into HEXA format */                                                              
       for (i = 0; i < strlen(line_buffer); i += 8) {                           
            strncpy(temp, line_buffer + i, 8);                                  
            temp[8] = '\0';                      
            val = (int)strtol(temp, NULL, 16);                                                                               
            for (idx = 3; idx >= 0; idx--) {   
                 if (val < 0xffff && idx >= 2) {
                     continue;
                 }
                data_int[count++] = *(char *) ((char * )&val + idx);                                                                                
            }                                                                   
            memset(temp, 0, 10);                                                
        }                                                                       
        count = 0;                                                              
        beacon_frame = (beacon_frame_t *)data_int;                              
        beacon_acc_frame = (beacon_frame_acc_mtr_t *)data_int;                  
                                                                                
        beacon_flag = 0;                                                        
                                                                                
        if (beacon_frame->beacon_type[0] == 0x02 &&                             
            beacon_frame->beacon_type[1] == 0x15) {                             
            //printf(" Found Beacon Type: %x%X \n", beacon_frame->beacon_type[0],
            //                               beacon_frame->beacon_type[1]);     
            beacon_flag = 1;                                                    
        }                                                                       
                                                                                
        if (beacon_flag == 0) {                                                 
           *(char *)((char *)&x + 1) = beacon_acc_frame->x_axis[0];             
           *(char *)((char *)&x + 0) = beacon_acc_frame->x_axis[1];             
                                                                                
           *(char *)((char *)&y + 1) = beacon_acc_frame->y_axis[0];             
           *(char *)((char *)&y + 0) = beacon_acc_frame->y_axis[1];             
                                                                                
           *(char *)((char *)&z + 1) = beacon_acc_frame->z_axis[0];             
           *(char *)((char *)&z + 0) = beacon_acc_frame->z_axis[1];             
                                                                                
            printf("Beacon Accelerometer Frame Detected\n");                    
            printf("    X-axis %04x, Y-axis %04x, Z-axis %04x \n", x, y, z);
			printf("	Battery Level %d \n", beacon_acc_frame->battery_level);
			printf("    Mac address %x : %x : %x : %x : %x : %x \n", beacon_acc_frame->mac_add[0],
                                                                     beacon_acc_frame->mac_add[1],
                                                                     beacon_acc_frame->mac_add[2],
                                                                     beacon_acc_frame->mac_add[3],
                                                                     beacon_acc_frame->mac_add[4],
                                                                     beacon_acc_frame->mac_add[5]);
            if (x != p_x || y != p_y || z != p_z) {                             
                printf("\n    Detected movement. \n");                          
            } else {                                                            
                printf("\n    Detected stationary. \n");                        
            }                                                                   
                                                                                
            p_x = x;                                                            
            p_y = y;                                                            
            p_z = z;                                                            
        } else { 
#if 0
            printf("\nBeacon Frame Detected\n");                                
            printf("    Data Len %x \n", beacon_frame->data_length);            
            printf("    Frame dat Type %x \n", beacon_frame->frame_data_type);  
            printf("    Flag data : %x \n", beacon_frame->flag_data);           
            printf("    Flag data len : %x \n", beacon_frame->flag_data_length);
            printf("    Manufacture data : %x \n", beacon_frame->manufacture_data);
            printf("    Company ID : %x%x \n", beacon_frame->company_id[0],     
                    beacon_frame->company_id[1]);                               
            printf("    Beacon Type: %02x%02X \n", beacon_frame->beacon_type[0],
                    beacon_frame->beacon_type[1]);
#endif
            printf("\n");                                                       
        }                                                                       
                                                                                
        memset(data_int, 0, 30 * sizeof(unsigned int ));                        
    }                                                                           
                                                                                
}
