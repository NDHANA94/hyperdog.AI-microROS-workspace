# hyperdogAI_microROS_controller
Micro-ROS  STM32F407 firmware for MiniCheetah BLDC motor controller for the Next Generation of HyperDog 

### $${\color{red}{Work \space \space in \space \space Progress}}$$ 
### $${\color{red}{NOT \space \space  YET \space \space READY \space \space FOR \space \space USE}}$$ 


### DONE:

- Tested `micro-ROS app` and `error indicator` on 2 seperate `FreeRTOS` tasks.
- MicroROS is established.
- Motor struct was developed;
- Developed micro-ROS custom msgs and srv for controlling motors
- Following server were developed in stm32 firmware;
    - `initLegMotors` 
    - `enableAllMotors`
    - `desableAllMotors`
    - `setMotorZeroPostion`
- Following Publishers were developed in stm32 firmware;
    - `motorsStates`
- Following Subscriptions were developed in stm32 firmware;
    - `motorCmd`

- Following clients were developed in ROS2 `hyperdog_ctrl_legs` pkg;
    - `initMotors`
    - `anableAllMotors`
    - `disableAllMotors`
    - `setMotorZeroPosition`

- Developed a mechanism to re-establish the connection with micro-ros agent.
- Created LED error code indicator for showing micro-ROS (LD3), CAN(LD5), Motor(LD6) errors.
        

### TODO:
- Increse the frequency of motorsState publish msg
- Implement Inverse kinematics and control the leg using coordinate commands
- calculate force vector within the microcontroller using motor current feedback
- Implement impedence control for the legs within the microcontroller.
- And MANY MORE............. XD

### fixed issues;
1. Could't add a 2nd server:
    * Reason: libmicroros.a of micro_ros_stm32cubemx_utils is built with following `rmw_microxrcedds` configuration in `colcon.meta` file:
        ```
        "rmw_microxrcedds": {
            "cmake-args": [
                "-DRMW_UXRCE_MAX_NODES=1",
                "-DRMW_UXRCE_MAX_PUBLISHERS=10",
                "-DRMW_UXRCE_MAX_SUBSCRIPTIONS=5",
                "-DRMW_UXRCE_MAX_SERVICES=1",
                "-DRMW_UXRCE_MAX_CLIENTS=1",
                "-DRMW_UXRCE_MAX_HISTORY=4",
                "-DRMW_UXRCE_TRANSPORT=custom"
            ]
        }
        ```
        as it's configured to have maximum 1 server, I could't add a 2nd server.
    * Solution:
        -  configured `rmw_microxrcedds` of `colcon.meta` as following;
        ```
        "rmw_microxrcedds": {
            "cmake-args": [
                "-DRMW_UXRCE_MAX_NODES=2",
                "-DRMW_UXRCE_MAX_PUBLISHERS=5",
                "-DRMW_UXRCE_MAX_SUBSCRIPTIONS=5",
                "-DRMW_UXRCE_MAX_SERVICES=15",
                "-DRMW_UXRCE_MAX_CLIENTS=0",
                "-DRMW_UXRCE_MAX_HISTORY=4",
            ]
        }
        ```

2. Could't publish `motorsStates` msg with best_efford qos-reliability mode:
    * Reason: `microxrcedds_clients` of `libmicroros.a` is built with 512 Bytes default size of `CLIENT_CUSTOM_TRANSPORT_MTU`,
                and my `motorsStates` msg size is 768 Bytes.
    * Sollution;
        - add `"-DUCLIENT_CUSTOM_TRANSPORT_MTU=1024"` into `colcon.meta`->`"microxrcedds_client"`->`"cmake-args"`
        - configure_firmware
        - build_firmware
        - use newly built `libmicroros.a` 


### Known Isues
1. Can't increase `motorsStates` publish rate with best_effort QOS-realiability mode.
    It takes around 19ms to be published one msg.
    This can be due to the size of the msg (768 B).

<!--
### ERROR CODE:

#### Micro-ROS Error-code: (LD3 - Orange LED)
    short blinks:
    `1`: Failed to create RMW transport
    `2`: Failed to allocate memory for FreeRTOS
    `3`: Failed to initialize the node
    `4`: Failed to initialize the motor feedbak publisher
    `5`: Failed to publish motor feedback / Agent is not connected

#### CAN Error-code: (LD5 - Red LED)
    short blinks: 
     `1`: Protocol Error Warning
     `2`: Error Passive   
     `3`: Parameter error ; can be ocuured due to lost of can bus connection or no msg received
     `4`: Bus-off error
     `5`: Stuff error  
     `6`: Form error  
     `7`: Acknowledgment error
     `8`: Bit recessive error
     `9`: Bit dominant error   
    `10`: CRC error  
    `11`: Rx FIFO0 overrun error
    `12`: Rx FIFO1 overrun error 
    `13`: TxMailbox 0 transmit failure due to arbitration lost
    `14`: TxMailbox 0 transmit failure due to transmit error
    `15`: TxMailbox 1 transmit failure due to arbitration lost
    `16`: TxMailbox 1 transmit failure due to transmit error
    `17`: TxMailbox 2 transmit failure due to arbitration lost
    `18`: TxMailbox 2 transmit failure due to transmit error
    `19`: Timeout error  
    `20`: Peripheral not initialized 
    `21`: Peripheral not ready 
    `22`: Peripheral not started 

#### Motor Error-code: (LD6 - Blue LED)
    long blinks indicate motor index with the error.
    short blinks indicate the error.
     `1`: motor is not initialized  
     `2`: motor parameter error
     `3`: HAL_CAN Error
     `4`: motor is offline / not connected 
     `5`: Out Of Range error      
     `6`: Over-Heat error   
     `7`: Over-Current error 
     `8`: Failed to enable the motor 
     `9`: Failed to diable the motor    
    `10`: Failed to set motor zero position
    `11`: Motor is not ready to be operated 
-->

<!-- 
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
    - `USART2_TX -> PA2`
    - `USART2_RX -> PA3`

- CAN Interface: 
    - `CAN1_TX -> PD1`
    - `CAN1_RX -> PD0`




### Fixed HAL bugs:
- stm32f4xx_hal_can.h -> HAL_CAN_GetRxMessage(----) : Not updating error code, if HAL_OK:
    fixed: add `hcan->ErrorCode &= ~ HAL_CAN_ERROR_PARAM;` to line 1587 (before `return HAL_OK;`) 
-->

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