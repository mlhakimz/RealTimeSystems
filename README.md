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

## Example 5 - Mutex

## Example 6 - Semaphore

## Example 7 - Software Timer

## Example 8 - Hardware Interrupts

## Example 9 - Deadlock & Starvation

## Example 10 - Priority Inversion

## Example 11 - Multicore Systems
