#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "graphlib.h"

#ifndef _NET_H_
#define _NET_H_

/**
  Gets the last node of a node list
  @param start of linked node list
  @return last node of list
 */
//node* getLastNode(node* start);

/**
   Gets the last edgedata of an edge list
   @param start start of a linked list
   @return last edgedata of list
 */
//edgedata* getLastEdge(edgedata* start);

/**
   Creates a new node with a given name
   Adds node at end of linked list
   @param list list to add a node
   @param name name of the node
   @return address to the new node
*/
//node* newNode(node** list, char* name);

/**
   Finds a node in a node list
   @param list search this list of nodes
   @param name find node with this name
   @return address of found node if found, else NULL
 */
//node* findNode(node* list, char* name);

/**
   Tries to remove a node from a node list
   @param list list of nodes
   @param name remove node with this name
 */
//void removeNode(node* list, char* name);

/**
   Tries to remove an edgedata from a node
   @param node1 node to search for edges
   @param name remove edgedata with this name
*/
//void removeEdge(node* node1, char* name);

/**
   Add a neighbor to a node
   @param node node to given edgedata
   @param line bus line
   @param time travel time to that stop
   @param busstop the neighbor
*/
//void appendEdge(node* node, short line, short time, char* busstop);


/**
   Add a time when a bus leaves
   @param busline busline to add time to
   @param hour hour when bus leaves
   @param min minute when the bus leaves
 */
//void addTime(busstart* busline, int hour, int min);

/**
   Add a time when a bus leaves the starting station
   @param node station to add time to
   @param busline busline to add time to
   @param hour hour when bus leaves
   @param min minute when the bus leaves
 */
//void addStartTime(node* node, int line, int hour, int min);

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
   Gets minutes of travel between two stations
   @param visitedList list of previously searched nodes
   @param from name of start bus stop
   @param to name of destination bus stop
   @param bus bus number we are travelling on
   @param time accumulated travel time
   @return minutes it takes between from and to on the bus number
 */
//int getTravelTime(node* visitedList, node* from, node* to, int bus, int time);

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
