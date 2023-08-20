# hyperdogAI_microROS_controller
Micro-ROS  STM32F407 firmware for MiniCheetah BLDC motor controller for the Next Generation of HyperDog 

### $${\color{red}{Work \space \space in \space \space Progress}}$$ 
### $${\color{red}{NOT \space \space  YET \space \space READY \space \space FOR \space \space USE}}$$ 


### DONE:

- MicroROS is established.
- Motor struct was developed;
        
        - TypeDef struct Motor:
                            - id (uint8_t)

                            - params:
                                    - p:
                                        - min (float)
                                        - max (float)
                                    - v:
                                        - min (float)
                                        - max (float)
                                    - kp: 
                                        - min (float)
                                        - max (float)
                                    - kd: 
                                        - min (float)
                                        - max (float)
                                    - i_ff: 
                                        - min (float)
                                        - max (float)
                                    - vb: 
                                        - min (float)
                                        - max (float)

                            - limit:
                                    - position:
                                        - min (float)
                                        - max (float)
                                    - velocity:
                                        - min (float)
                                        - max (float)
                                    - current: 
                                        - min (float)
                                        - max (float)

                            - cmd:
                                    - p_des:
                                        - min (float)
                                        - max (float)
                                    - v_des:
                                        - min (float)
                                        - max (float)
                                    - kp: 
                                        - min (float)
                                        - max (float)

                            - feedback:
                                    - position (float)
                                    - velocity (float)
                                    - current  (float)

                            - init_state: 4-bits value
                                    - 0b0000: nothing initialized
                                    - 0b0001: motor id is set
                                    - 0b0010: motor params are set
                                    - 0b0100: motor limits are set
                                    - 0b1000: CAN comunication is configured 
                            
                            - state: enum MOTOR_State
                                    - MOTOR_READY        = 0b00
                                    - MOTOR_INITIALIZING = 0b01
                                    - MOTOR_ENABLED      = 0b10
                                    - MOTOR_ERROR        = 0b11

                            - error_code: 11-bits
                                    - 0b00000000000: No error
                                    - 0b00000000001: motor is not initialized
                                    - 0b00000000010: motor parameter error
                                    - 0b00000000100: HAL_CAN error
                                    - 0b00000001000: motor is offline
                                    - 0b00000010000: current motor position is out of range
                                    - 0b00000100000: motor is over-heated
                                    - 0b00001000000: motor takes over-currunt
                                    - 0b00010000000: failed to enable the motor
                                    - 0b00100000000: failed to disable the motor
                                    - 0b01000000000: failed to set motor zero position
                                    - 0b10000000000: motor is not ready to be operated
                                    - 0b00000000111: initial state of the motor error_code

                            - hcan_ptr (CAN_HandleTypeDef*): pointer to hcan1
                            
                            - canTX: CAN tx message
                                    - data[8]   (uint8_t)
                                    - header    (CAN_TxHeaderTypeDef)
                                    - TxMailBox (uint32_t)

                            - canRx: CAN rx message
                                    - data[7]   (uint8_t)
                                    - header    (CAN_TxHeaderTypeDef)
                                    - filter    (CAN_FilterTypeDef)

                            - noResp_counter: to count times of no response from the motor
                                            if more than 5 times a motor response is not received:
                                                - state -> ERROR
                                                - error_code -> motor offline
        
- Following method were created for controling:

```c
    void MOTOR_initId(enum MOTORS m, uint8_t id);
    void MOTOR_initParams(enum MOTORS m, float pMax, float vMax, float kpMax, float kdMax, float iffMax, float vbMax);
    void MOTOR_initCtrlLimits(enum MOTORS m, float pDesMax, float pDesMin, float vMax, float iMax);
    void MOTOR_initCANConfig(enum MOTORS m, CAN_HandleTypeDef* hcan, uint8_t filterbank);
    void MOTOR_enable(enum MOTORS m);
    void MOTOR_disable(enum MOTORS m);
    void MOTOR_setZero(enum MOTORS m);
    void MOTOR_sendTxGetRx(enum MOTORS m);
    void MOTOR_sendHeatbeat(enum MOTORS m);
    void MOTOR_startWatchdog(); // @todo

    void _pack_cmd(enum MOTORS m); 
    void _unpack_canRx(enum MOTORS m); 
    bool _is_motor_error(enum MOTORS m, uint8_t error_word);

    float fminf(float x, float y);
    float fmaxf(float x, float y);
    int float2uint(float x, float x_min, float x_max, int bits);
    float uint2float(int x_int, float x_min, float x_max, int bits);
```

- Error indicator using 4 LEDs is partially developed.
    - `orange LED`: micro-ROS errors
        - `1 blink`: rmw error
        - `2 blinks`: rcl error
    
    - `red LED`: CAN bus errors
    - `blue LED`: Motor errors (Not implemented yet)
    - `green LED`: -

- Tested `micro-ROS node`, `CAN communication` and `error indicator` on 3 seperate `FreeRTOS` tasks.
- tested micro-ROS topics over 200 Hz frequency.
        


### TODO:
- Develope micro-ROS custom msgs and srv for controlling motors
- Implement Inverse kinematics and control the leg using coordinate commands
- calculate force vector within the microcontroller using motor current feedback
- Implement impedence control for the legs within the microcontroller.
- And MANY MORE............. XD



### How I created CubeMX project:

1. Create a new CubeMX project for stm32f407
2. `System Core -> RCC -> High Speed Clock (HSE)` : Select `Crystal/Ceramic Resonator`
3. `System Core -> SYS -> Timebase Source`: Select `TIM1`
4. `Middleware -> FREERTOS -> Interface`: Select `CMSIS_V2`
5. `Middleware -> FREERTOS -> Configuration -> Task and Queues`: Double click on the `defaultTask` and set `stack size` to `3000`. For microRos task, stack size should be greater than 10 KBytes. (3000 * 4 = 12 K).
6. `Connectivity -> UART/USART`
    - `baudrate`: `926100`
    - `DMA Settings`: 
        - `Add`: `Rx` ; `Mode`: `Circular`
        - `Add`: `TX` ; `Mode`: `Normal`
    - `NVIC Settings`: Set `UART global interrupt`
7. Set up `Clock Configuration` to achieve the highest clock possible.
8. `Project Manager`:
    - `Toolchain / IDE`: `Makefile`
    - `Generate peripheral intitialization as a pair of '.c/.h' files per peripheral`
    - Generate code by clicking `Generate Code`


### Pinouts:
 - USART2: microROS agent must be connected via 
    `USART2_TX ---> PA2`
    `USART2_RX ---> PA3`

- CAN Interface: 
    `CAN1_TX ---> PD1`
    `CAN1_RX ---> PD0`



<!-- 

gitignore:
    ```
    browser.vc.db 
    browser.vc.db-shm 
    browser.vc.db-wal
    build/*.o
    build/*.d
    build/*.lst
    ```
gitattributes:
    ```
    Drivers/** filter=lfs diff=lfs merge=lfs -text
    Drivers/CMSIS filter=lfs diff=lfs merge=lfs -text
    Drivers/STM32F4xx_HAL_Driver filter=lfs diff=lfs merge=lfs -text
    ```

git lfs:
    ```
    git lfs install
    git lfs track Drivers/**
    git lfs track micro_ros_stm32cubemx_utils
    git lfs push --all origin main
    git commit -m "lfs push"
    gt push -u origin main
    ```

 -->