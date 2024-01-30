#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "eecs388_lib.h"
#include "metal/i2c.h"

struct metal_i2c *i2c;
uint8_t bufWrite[5];
uint8_t bufRead[1];
volatile int g_angle;

//The entire setup sequence
void set_up_I2C()
{
    uint8_t oldMode;
    uint8_t newMode;
    _Bool success;

    bufWrite[0] = PCA9685_MODE1;
    bufWrite[1] = MODE1_RESTART;
    printf("%d\n",bufWrite[0]);
    
    i2c = metal_i2c_get_device(0);

    if(i2c == NULL){
        printf("Connection Unsuccessful\n");
    }
    else{
        printf("Connection Successful\n");
    }
    
    //Setup Sequence
    metal_i2c_init(i2c,I2C_BAUDRATE,METAL_I2C_MASTER);
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//reset
    delay(100);
    printf("resetting PCA9685 control 1\n");

    //Initial Read of control 1
    bufWrite[0] = PCA9685_MODE1;//Address
    success = metal_i2c_transfer(i2c,PCA9685_I2C_ADDRESS,bufWrite,1,bufRead,1);//initial read
    printf("Read success: %d and control value is: %d\n", success, bufWrite[0]);
    
    //Configuring Control 1
    oldMode = bufRead[0];
    newMode = (oldMode & ~MODE1_RESTART) | MODE1_SLEEP;
    printf("sleep setting is %d\n", newMode);
    bufWrite[0] = PCA9685_MODE1;//address
    bufWrite[1] = newMode;//writing to register
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//sleep
    bufWrite[0] = PCA9685_PRESCALE;//Setting PWM prescale
    bufWrite[1] = 0x79;
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//sets prescale
    bufWrite[0] = PCA9685_MODE1;
    bufWrite[1] = 0x01 | MODE1_AI | MODE1_RESTART;
    printf("on setting is %d\n", bufWrite[1]);
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//awake
    delay(100);
    printf("Setting the control register\n");
    bufWrite[0] = PCA9685_MODE1;
    success = metal_i2c_transfer(i2c,PCA9685_I2C_ADDRESS,bufWrite,1,bufRead,1);//initial read
    printf("Set register is %d\n",bufRead[0]);
} 

void breakup(int bigNum, uint8_t* low, uint8_t* high){
    /*
        Write Task 1 code here
    */
   *low = bigNum & 0xFF ;
   *high =(bigNum >> 8) & 0xFF ;
   //bigNum = 

}

void steering(int angle){
    /*
        Write Task 2 code here
    */
  
   int breakVal = getServoCycle(angle);
   
   //bufWrite[0] = LED;
   //bufWrite[1] = ON_L;
   //bufWrite[2] = ON_H;
   //bufWrite[3] = OFF_L;
   //bufWrite[4] = OFF_H;

   bufWrite[0] = PCA9685_LED0_ON_L;
   bufWrite[1] = 0;
   bufWrite[2] = 0;
   breakup(breakVal, &bufWrite[3], &bufWrite[4]);

   metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
}

void stopMotor(){
    /*
        Write Task 3 code here
    */
   int breakVal = 280;
   bufWrite[0] = PCA9685_LED1_ON_L;
   bufWrite[1] = 0;
   bufWrite[2] = 0;
   breakup(breakVal, &bufWrite[3], &bufWrite[4]);
   metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);

}

void driveForward(uint8_t speedFlag){
    /*
        Write Task 4 code here
    */
    int breakVal;
    if (speedFlag == 1){
        //breakVal = 313
        breakVal = 313;
        bufWrite[0] = PCA9685_LED1_ON_L;
        bufWrite[1] = 0;
        bufWrite[2] = 0;
        breakup(breakVal, &bufWrite[3], &bufWrite[4]);
        metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
    }
    else if (speedFlag == 2){
        //breakVal = 315

        breakVal = 315;
        bufWrite[0] = PCA9685_LED1_ON_L;
        bufWrite[1] = 0;
        bufWrite[2] = 0;
        breakup(breakVal, &bufWrite[3], &bufWrite[4]);
        metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
    }
    else if (speedFlag == 3){
        //breakVal = 317
       
        breakVal = 317;
       
        bufWrite[0] = PCA9685_LED1_ON_L;
        bufWrite[1] = 0;
        bufWrite[2] = 0;
        breakup(breakVal, &bufWrite[3], &bufWrite[4]);
        metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
    }

}

void driveReverse(uint8_t speedFlag){
    /*
        Write task 5 code here
    */
    int breakVal;
    if (speedFlag == 1){
        //breakVal = 257
    
        breakVal = 257;
    
        bufWrite[0] = PCA9685_LED1_ON_L;
        bufWrite[1] = 0;
        bufWrite[2] = 0;
        breakup(breakVal, &bufWrite[3], &bufWrite[4]);
        metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
    }
    else if (speedFlag == 2){
        //breakVal = 255
    
        breakVal = 255;
       
        bufWrite[0] = PCA9685_LED1_ON_L;
        bufWrite[1] = 0;
        bufWrite[2] = 0;
        breakup(breakVal, &bufWrite[3], &bufWrite[4]);;
        metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
    }
    else if (speedFlag == 3){
        //breakVal = 253
       
        breakVal = 253;
        
        bufWrite[0] = PCA9685_LED1_ON_L;
        bufWrite[1] = 0;
        bufWrite[2] = 0;
        breakup(breakVal, &bufWrite[3], &bufWrite[4]);
        metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
    }
}


void raspberrypi_int_handler(int devid)
{
    char * str = malloc(20 * sizeof(char));

    //g_angle => readline from UART0

    free(str);
}


int main()
{
    // Initialize I2C
    set_up_I2C();
    delay(2000);

    // Calibrate Motor
    printf("Calibrate Motor.\n");
    stopMotor();
    delay(2000);

    // initialize UART channels
    ser_setup(0); // uart0 (receive from raspberry pi)
    ser_setup(1); 
    
    printf("Setup completed.\n");
    printf("Begin the main loop.\n");
    
    // Initialize global angle
    g_angle = 0;

    sendData();

    return 0;
}

void sendData() {
    int devid = 1; // 1 = ttyAMA1, 0 = ttyAMA2
    int running = 1;
    char str[8]={0,0,0,0,0,0,0,0};
    int val[3] = {0,0,0};

    while(1) {
        // str
        while (running) {
            int i = 0;
            while (ser_isready(devid)) {
                printf("ser_read is ready!\n");

                str[i] = ser_read(devid);

                if (i == 7) running = 0;
                i++;
            }
        }

        sscanf(str, "%d %d %d", &val[0], &val[1], &val[2]);
        printf("%d %d %d\n", val[0], val[1], val[2]);

        steering(val[1]);
        switch (val[0]) {
            case 0:
                stopMotor();
                break;
            case 1:
                driveForward(1);
                break;
            case 2:
                driveReverse(1);
                break;
        }
        delay(val[2] * 1000);


        running = 1;
    }
}
