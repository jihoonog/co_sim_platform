/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Evandro de Souza
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author:  Evandro de Souza <evandro@ualberta.ca>
 * Date:    2019.05.12
 * Company: University of Alberta/Canada - Computing Science
 *
 */


#ifndef SMARTGRID_NS3_HELPER_H_
#define SMARTGRID_NS3_HELPER_H_

#include <vector>
#include <iostream>
#include <memory>
#include <string.h>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/node-container.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"

#include "json.hpp"

using namespace std;
using namespace ns3;

/**
 * Read node adjacency matrix and load into a boolean vector
 *
 * \param adjMatFileName Filename of the adjacency matrix
 * \returns Boolean array with indication of node connection
 */
vector< vector<bool> > ReadNodeAdjMatrix (string adjMatFileName);

/**
 * Read node adjacency list from a json file and loat into a boolean vector 
 * 
 * \param jsonFileName Filename of the json file that contains the adjacency list
 * \return Boolean array with indication of node connections (adjacency matrix)
 */
vector< vector<bool> > ReadNodeAdjListJson (string jsonFileName);

/**
 * Print the node adjacency matrix
 *
 * \param description Filename of the input file
 * \param array Boolean array with indication of node connection
 *
 */
void PrintNodeAdjMatrix (const char* description, vector<vector<bool> > array);


/**
 * Read node names and coordinates
 *
 * \param nodeCoordinatesFilename Filename of the coordinates file
 * \returns String array with nodes names and coordinates
 *
 */
vector<vector<string> > ReadCoordinatesFile (string nodeCoordinatesFilename);

/**
 * Read node names and coordinates from a json file
 * 
 * \param jsonFileName JSON filename that contains the nodes' locations
 * \return String array with nodes names and coordinates
 *
 */
vector<vector<string> > ReadCoordinatesJSONFile (string jsonFileName);

/**
 * Parses coords from return of ReadCoordinatesFile
 *
 * \param arrayNamesCoords Vector of node names and coords generated by ReadCoordinatesFile
 * \returns Vector of coords
 *
 */
vector<vector<double>> loadNodeCoords (vector<vector<string>> arrayNamesCoords);

/**
 * Print the node names and coordinates
 *
 * \param description Filename of the input file
 * \param array String array with indication of node coordinates
 *
 */
void PrintNamesCoordinates (const char* description, vector<vector<string> > array);


/**
 * Read node application connections
 *
 * \param appConnectionsFilename Filename of the application connections
 * \returns String array with nodes names of application connections
 *
 */
vector<vector<string> > ReadAppConnectionsFile (string nodeCoordinatesFilename);


/**
 * Print the IP addresses
 *
 * \param nodes NodeContainer with nodes
 * \param network P2P/CSMA/P2Pv6/CSMAv6
 *
 */
void PrintIpAddresses(NodeContainer nodes, string network);


/**
 * Create map to associate Ipv4 address and Node Id
 *
 * \param nodes NodeContainer with nodes
 *
 */
map<Ipv4Address, uint32_t> CreateMapIpv4NodeId(NodeContainer nodes);


/**
 * Create map to associate Ipv6 address and Node Id
 *
 * \param nodes NodeContainer with nodes
 *
 */
map<Ipv6Address, uint32_t> CreateMapIpv6NodeId(NodeContainer nodes);

/**
 * @brief Find the next hop from given source to destination. Perform
 * Breadth-First-Search (BFS) to find the next hop
 * 
 * @param clt the source of the message
 * @param srv the destination of the message
 * @param array the adjacency matrix of the network
 */
string FindNextHop(string clt, string srv, vector<vector<bool>> array);

/**
 * @brief Print the routing table.
 * @param n the node
 * @param v4 IPv4 or IPv6
 */
void PrintRoutingTable (Ptr<Node>& n, bool v4);

#endif /* SMARTGRID_NS3_HELPER_H_ */
