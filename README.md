# RealTimeSystems

## Example 1 - Tasks

Using the FreeRTOS, run 2 tasks which are to toggle the built in LED with different timings, on one core.

<details>
<summary>Experimental Setup</summary>
<img src="https://github.com/mlhakimz/RealTimeSystems/blob/main/Example%201/Example1_Setup.jpg">
</details>

## Example 2 - Task Scheduling

Run 2 tasks in one core. One read user input to set new LED timings, another one blinks the LED according to the user input.

<details>
<summary>Experimental Setup</summary>
<img src="https://github.com/mlhakimz/RealTimeSystems/blob/main/Example%202/Example2_Setup.jpg">
</details>

## Example 3 - Memory Management

A simple serial input echo program, with optimized memory usage by using vPortFree after every serial input so that the heap memory does not build up and cause memory leak.

## Example 4 - Queue

Using two queues and two task, where the Serial task will read serial input and echo the contents, if the content is delay x, the value x is parsed to the delay queue. Task Blinky will receive anything from the delay queue to update the blinking LED delay and send a message to the message queue everytime the LED reaches 100 blinks. The Serial task will also read the message queue and display the message whenever the queue is filled.

## Example 5 - Mutex

Using mutex, the creation of a task is not disrupted by any other functions. In this case, the setup function finished first and dereferences the variable needed for the task before the task has finished compiling. Through mutex, this problem can be avoided.

## Example 6 - Semaphore

Using Semaphores and mutexes, the writing and reading data in a buffer is not disrupted and not repeated. The critical sections of the code (Serial, read & writing on buffer) such are protected by mutexes. The Semaphores make sure that the consumer tasks do not read the same data more than once, it only execute if the semaphores are released by the producer tasks.

## Example 7 - Software Timer

Software timers are used to delay the execution of functions or carry out periodic operations. In this case, a timer is used to disable the backlight of an LCD (represented by the built in LED on the ESP32) after 5 seconds of inactivity.

## Example 8 - Hardware Interrupts

## Example 9 - Deadlock & Starvation

## Example 10 - Priority Inversion

## Example 11 - Multicore Systems
