#pragma once

/**
* @file
* @brief A module implementing a timer.
*/

/**
 * @brief A static struct used for storing the start time of the timer. The end time
 * is allocated statically for convinience.
 */
static struct timeval start, end;

/**
 * @brief Start the timer by setting the static timeval start to the current time.
 */
void timer_start();

/**
 * @brief Get how long the timer has run.
 * 
 * @return The number of seconds since the timer was last started.
 */
double timer_get();