#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "graphlib.h"

/**
 * @file net.h
 * @author Staffan Edstrom, Magnus Muhr
 */

#ifndef _NET_H_
#define _NET_H_

/**
   Initializes list of bus stops from provided file over the
   bus network. Also adds edge data containing information about
   the node's neighbours. 
   The start node of the list is called 'root'
 */
void initBusStops();

/**
   Prints list of nodes and their names with their connections
   (Function is for debugging)
   @param viewConnections 0 or 1 depending on if you want to show each node's connections or not
   @param list list of nodes to print
 */
void printNodeList(int viewConnections, node* list);

/**
   Converts hours and minutes to minutes
   @param hours time in hours
   @param minutes time in minutes
   @return hours and minutes converted to minutes
 */
int timeToMinutes(int hours, int minutes);

/**
   Converts minutes to hours
   @param minutes
   @return number of hours
 */
int minsToHours(int minutes);

/**
   Prints time on the format 12:34
   @param time of the day in minutes counting from 00:00
 */
void printMinsToClock(int finalMins);

/**
   Prints when you should leave and arrive at your start and destination
   @param path the list of nodes representing the way between two bus stops
   @param bus bus line
   @param travelTime the time it takes to travel the path
   @param hour hour when you want to leave/arrive
   @param minute minute when you want to leave/arrive
   @param action specifiy whether you want to leave or arrive at the specified time
 */
void getTimes(node* path, int bus, int travelTime, int hour, int minute, char* action);

/**
   Prints a travel route
   @param list list of nodes representing the travel path
   @param busline bus number
   @param travelTime time traveled between start and destination
   @param action specifies whether we want to arrive or leave at travelTime
 */
void printTravelPath(node* list, int busline, char* travelTime, char* action);

/**
   Starts looking for possible paths
   If found in one step, print path
   Otherwise continue search in searchPath-function
   @param from name of bus stop you want to travel from
   @param to name of bus stop you want to travel to
   @param travelTime time you want to leave or arrive
   @param action specifies whether you want to leave or arrive or just look up travel times
 */
void possiblePaths(char* from, char* to, char* travelTime, char* action);

/**
   Recursively searches through nodes for destination
   @param visitedList list of already visited nodes
   @param current node to search for destination in
   @param to destination node
   @param busline bus number
   @param travelTime time we want to leave or arrive
   @param action specifies whether we want to leave or arrive at the given travelTime
 */
void searchPath(node* visitedList, node* current, node* to, int busline, char* travelTime, char* action);

/**
   Initializes the time table of departures from the start stations to a linked list of nodes
   The first element is the variable "timetable"
 */
void initTimeTable();

/**
   Frees all the memory where the bus stops are stored
 */
void freeBusStops();

/**
   Frees all the memory where the time table of bus starts are stored
 */
void freeTimeTable();

/**
   Plans a journey between two bus stops
   @param argc number of arguments
   @param argv array of arguments
   @return 0
 */
int main(int argc, char *argv[]);

#endif
