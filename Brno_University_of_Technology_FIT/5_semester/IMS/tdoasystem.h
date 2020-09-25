/*
 * Projekt: Simulace toku dat v systemu pro zpracovani radiovych casomernych signalu s vyuzitim v pozicnim systemu
 * Autor: Jan Ondruch, xondru14
 * Datum: 29.11.2017
 */

#ifndef TDOASYSTEM_H
#define TDOASYSTEM_H

#include <getopt.h>
#include <iostream>
#include <string>
#include <simlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <vector>
#include <memory>

using namespace std;


/*
 * Record (data) sent to the client from the server.
 */
class Record : public Process {
public:
	double ArrivalTime;
	Record(double ArrivalTime);
	void Behavior();
};

/*
 * Packet generated by the tag containing the signal (location of the tag).
 * Packet way: tag -> anchor -> RTLS Server TDOA (computation & tag merge) -> 
 *             RTLS Sensmap Server
 */
class Packet : public Process {
public:
	double ArrivalTime;
	double DelayRtlsServ;
	void Behavior();
};

/*
 * Server representing CPU login containing various apps.
 */
class Server : public Process {
private:	
	double tCPU;
public:
	void Behavior();
};

/*
 * Generation of tag signal.
 * Each tag refreshes every TAG_REF_RATE ms.
 * Every tag generates Packet for every anchor.
 */
class Tag : public Event {
private:
	vector<shared_ptr<Packet>> packets;
public:
	void Behavior();
};

/*
 * System initialization.
 * Generates tags, create new facilities and start the RTLS server.
 */
class SystemInitiator : public Event {
public:
	Server* s;
	vector<shared_ptr<Tag>> tags;
	void Behavior();
	~SystemInitiator();
};

#endif 