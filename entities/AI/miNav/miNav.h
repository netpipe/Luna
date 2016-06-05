/*
miNav - Mindinsomnia AI Pathfinding Navigation
(C) Grady O'Neill 2007
*/

#include <math.h>
#include <stdio.h>

#ifndef MINAV_H_
#define MINAV_H_

// Definition of INFINITY, increase if Map is too large
#define INFIN 300000

namespace miNav {
    // Forward referencing
    class Map;
    
    // My Node class, stores it's position, it's connections to other nodes
    // and preprocessed solutions.
    class Node
    {
        private:
            // Variables used in the pathfinding process which user's don't need
            // or shouldn't have access to.
            float distance;
            Node* next;
            Node* previous;
            bool set;
            bool unset;
            
            // Solution Structure - A linked list of solutions to different nodes
            // is used.
            struct Solu
            {
                Node* Destination;
                Node* Solution;
                Solu* next;
            }* headSolution; // Pointer to the first Solution
            
            // Connection Structure - Similar to above but only a Connection to
            // a destination exists if 'this' Node and the 'Destination'
            // Node are connected.
            struct Conn
            {
                Node* Destination;
                Conn* next;
            }* headConnection; // Pointer to the first Connection
            
            // Delete all solutions in this Node, used in Pathfinding the clear 
            // current existing Linked List of Solutions to generate a new one 
            // from scratch.
            void deleteAllSolutions();
            
            // Add solution function, used to simplyfy pathfinding code.
            void addSolution(Node*, Node*);
            
       public:
            // Public Data, constructors and destructors
            float X;
            float Y;
            float Z;
            Node();
            ~Node();
            
            // So that Map can access the private data of Node but the user can't
            friend class Map;
    };
    
    // Forward reference of miNavDevice
    class miNavDevice;
    
    // Map class, manages Node's created by it.
    class Map
    {
        private:
            //Node Structure
            Node* head;
            
            // Pathfinding Functions
            //=====================================
                // Calculate shortest path equation
                void calculateShortestPaths(Node*);
            
                // Relax Neighbours
                void relaxNeighbours(Node *);
            
                // Extract Minimum
                Node * extractMinimum();
                
                // Check to see if all Node's have 'set' to true.
                bool allSet();
            //=====================================

            // Next Map in linked list
            Map * next;            
            
        public:
            // Find the next Node to go to for a given destination.
            Node * getSolution(Node *,Node *);
            
            // Add a Node to the Map
            Node * addNode(float, float, float);
            
            // Delete a Node
            void deleteNode(Node *);
            
            // Update the Solutions stored in all Nodes in the map
            void solve();
            
            // Find the distance between two nodes
            float distance(Node *, Node *);
            
            // Connect 2 Nodes together
            void connect(Node *, Node *);
            
            // 2 way connection... just uses the connect() function twice.
            void connect2way(Node *, Node *);
            
            // Disconnect 2 Nodes
            void disconnect(Node *, Node *);
            
            // Constructor Function, sets head, next, solutions and connections to NULL and numNodes to 0;
            Map();
            
            // Destructor Function, deletes child Nodes
            ~Map();
            
            // declare miNavDevice
            friend class miNavDevice;
    };
    
    class miNavDevice
    {
        private:
            // Pointer to first Map
            Map * head;
            int Maps;
        public:
            // Add a map
            Map * addMap();
            
            // Delete a Map
            void deleteMap(Map *);
            
            // Constructor Function, sets head to Null
            miNavDevice();
            
            // Destructor Function, deletes child Maps
            ~miNavDevice();
    };
}
#endif
