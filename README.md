# hyperdogAI_microROS_controller
Micro-ROS  STM32F407 firmware for MiniCheetah BLDC motor controller




Create Cube Mx project:

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


microROS agent must be connected via USART2:
    `USART2_TX ---> PA2`
    `USART2_RX ---> PA3`

CAN Interface:
    `CAN1_TX ---> PD1`
    `CAN1_RX ---> PD0`



<!-- 

gitignore:
    ```
    git rm --cached .vscode/browser.vc.db
    git rm --cached .vscode/browser.vc.db-shm
    git rm --cached .vscode/browser.vc.db-wal
    touch .gitignore
    echo .vscade/browser.vc.db >> .gitignore
    echo .vscade/browser.vc.db-shm >> .gitignore
    echo .vscade/browser.vc.db-wal >> .gitignore
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