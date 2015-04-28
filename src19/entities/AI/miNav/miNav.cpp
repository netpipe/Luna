/*
miNav - Mindinsomnia AI Pathfinding Navigation
(C) Grady O'Neill 2007

STATUS OF FUNCTION - Code words used during the development process to keep 
track of what needs doing: 
GREEN - Function is finished, debugged and tested. Working.
YELLOW - Function is finished and debugged. May or may not be working.
RED - Function is finished but hasn't been even run through the compiler to 
      check for errors yet. Most likely doesn't work.
BLACK - Not even finished. Possibly near being finished or not even started.
*/

#include "miNav.h"

namespace miNav
{
    // GREEN
    Node::Node()
    {
        // Basically just blank all values
        next = NULL;
        headSolution = NULL;
        headConnection = NULL;
        set = false;
        unset = false;
        previous = false;
        distance = 0;
    }
    
    // GREEN
    Node::~Node()
    {
        // Deleted created Solutions. Use function already created 
        // for this exact task
        this->deleteAllSolutions();
        
        // Go through linked list deleting all Connections
        Conn * qt = this->headConnection;
        Conn * pt = NULL;
        while(qt != NULL)
        {
            pt = qt->next;
            delete qt;
            qt = pt;
        }
    }
    
    // GREEN
    void Node::deleteAllSolutions()
    {
        // Go through linked list of solutions in a Node and delete all solutions
        Solu * q = this->headSolution;
        Solu * tmp = NULL;
        while(q != NULL)
        {
            tmp = q->next;
            delete q;
            q = tmp;
        }
        this->headSolution = NULL;
    }
    
    // GREEN
    void Node::addSolution(Node* Destination, Node* Solution)
    {
        // Add a solution for this Node to a Destination
        Solu* q = this->headSolution;
        if(q!=NULL)
        {
            while(q->next!=NULL)
            {
                q = q->next;
            }
            Solu* tmp = new Solu;
            tmp->Destination = Destination;
            tmp->Solution = Solution;
            tmp->next = NULL;
            q->next = tmp;
        }
        else
        {
            Solu* tmp = new Solu;
            tmp->Destination = Destination;
            tmp->Solution = Solution;
            tmp->next = NULL;
            this->headSolution = tmp;
        }
    }
    
    // GREEN
    float Map::distance(Node * N1, Node * N2)
    {
        // Simple distance equation applied to two Nodes
        float nX1 = N1->X;
        float nX2 = N2->X;
        float nY1 = N1->Y;
        float nY2 = N2->Y;
        float nZ1 = N1->Z;
        float nZ2 = N2->Z;
        float distance;
        distance = sqrt(pow((nX2-nX1),2)+pow((nY2-nY1),2)+pow((nZ2-nZ1),2));
        return distance;
    }
    
    // GREEN
    Map::Map()
    {
        head = NULL;
        next = NULL;
    }
    
    // GREEN
    Map::~Map()
    {
        Node * q = this->head;
        Node * p = NULL;
        while(q != NULL)
        {
            p = q->next;
            delete q;
            q = p;
        }
    }
    
    // GREEN
    Node * Map::addNode(float X, float Y, float Z)
    {
        Node * temp = new Node;
        temp->X = X;
        temp->Y = Y;
        temp->Z = Z;
        if(head == NULL)
        {
            head = temp;
        }
        else
        {
            Node * pt = head;
            while(pt->next != NULL)
            {
                pt = pt->next;
            }
            pt->next = temp;
        }
        return temp;
    }
    
    // GREEN
    Node * Map::getSolution(Node * position, Node * target)
    {
        if(position->headSolution!=NULL)
        {
            Node::Solu * q = position->headSolution;
            while(q->Destination!=target)
            {
                if(q->next!=NULL)
                {
                    q = q->next;
                }
                else
                {
                    return NULL;
                }
            }
            return q->Solution;
        }
        else
        {
            return NULL;
        }
    }
    
    // GREEN
    void Map::connect(Node * N1, Node * N2)
    {
        // Make a connection between 2 Nodes
        bool success = false;
        Node::Conn * q = N1->headConnection;
        while(q!=NULL)
        {
            if(q->Destination==N2)
            {
                success = true;
            }
            q = q->next;
        }
        if(success==false)
        {
            if(N1->headConnection==NULL)
            {
                Node::Conn * temp = new Node::Conn;
                temp->Destination = N2;
                temp->next = NULL;
                N1->headConnection = temp;
            }
            else
            {
                Node::Conn * temp = new Node::Conn;
                temp->Destination = N2;
                temp->next = NULL;
                Node::Conn * pt = N1->headConnection;
                while(pt->next!=NULL)
                {
                    pt = pt->next;
                }
                pt->next = temp;
            }
        }
    }
    
    // GREEN
    void Map::connect2way(Node * N1, Node * N2)
    {
        // Make a 2 Way connection between the Nodes
        this->connect(N1,N2);
        this->connect(N2,N1);
    }
    
    // YELLOW
    void Map::disconnect(Node * N1, Node * N2)
    {
        // Delete connection between N1 and N2 (WARNING: DOES NOT DELETE
        // CONNECTION BETWEEN N2 and N1)
        Node::Conn * q = N1->headConnection;
        Node::Conn * pt = NULL;
        while(q!=NULL)
        {
            if(q->Destination==N2)
            {
                pt->next = q->next;
                pt = q;
                delete pt;
                q = q->next;
            }
            else
            {
                pt = q;
                q = q->next;
            }
        }
    }
    
    // YELLOW
    void Map::deleteNode(Node * target)
    {
        // Go through all Node's and find any connected to target
        // Disconnect them
        Node * pt = this->head;
        while(pt!=NULL)
        {
            this->disconnect(pt,target);
            pt = pt->next;
        }        
        
        // Find the Node and remove it from the linked list and delete it.
        if(target==head)
        {
            delete target;
            head = NULL;
        }
        else
        {
            Node * q = head;
            while(q->next!=target&&q->next!=NULL)
            {
                q=q->next;
            }
            if(q->next!=NULL)
            {
                q->next = target->next;
                delete target;
            }
        }
    }
    
 
    // GREEN
    void Map::solve()
    {
        // Generate all solutions for all Nodes from every Node to every 
        // other Node
        Node * q = this->head;
        while(q!=NULL)
        {
            // Clear q for new solutions linked list
            q->deleteAllSolutions();
            
            // Do calculations for this Node
            calculateShortestPaths(q);
            
            // Generate New Linked List of Solutions
            Node * pt = this->head;
            Node * current;
            while(pt!=NULL)
            {
                // Look for the first step required to reach pt from q. 
                // Once founded addSolution() to q.
                current = pt;
                if(current!=q)
                {
                    while(current->previous!=q && current->previous!=NULL)
                    {
                        current = current->previous;
                    }
                    q->addSolution(pt,current);
                }
                else
                {
                    q->addSolution(pt,current);
                }
                
                // Go to next Node;
                pt = pt->next;
            }
            // Found all solutions for q, now go to next Node and repeat
            q = q->next;
        }
    }
    
    // GREEN
    void Map::calculateShortestPaths(Node* s)
    {
        // Reset all Pathfinding variables
        Node* q = head;
        while(q!=NULL)
        {
            q->distance = INFIN;
            q->previous = NULL;
            q->set = q->unset = false;
            q = q->next;
        }
    
        // Start pathfinding by set 's' (start) Node to unset
        s->unset = true;
        s->distance = 0;
        
        // Continue pathfinding until all Nodes set
        Node* u;
        while(allSet()!=true)
        {
            u = this->extractMinimum();
            u->set = true;
            relaxNeighbours(u);
        }
    }
    
    // GREEN
    Node* Map::extractMinimum()
    {
        // Return the unset Node with the lowest estimated distance
        Node* selected = NULL;
        float largest = INFIN + 1;
        Node* q = this->head;
        while(q!=NULL)
        {
            if(q->unset==true)
            {
                if(q->distance<largest)
                {
                    selected = q;
                    largest = q->distance;
                }
            }
            q = q->next;
        }
        selected->unset=false;
        return selected;
    }
    
    // GREEN
    void Map::relaxNeighbours(Node* u)
    {
        // Relax Neighbours 
        Node::Conn* Neigh = u->headConnection;
        while(Neigh!=NULL)
        {
            if(Neigh->Destination->distance > u->distance + this->distance(u,Neigh->Destination))    // a shorter distance exists
            {
                Neigh->Destination->distance = u->distance + this->distance(u ,Neigh->Destination);
                Neigh->Destination->previous = u;
                Neigh->Destination->unset = true;
            }
            Neigh = Neigh->next;
        }
    }
    
    // GREEN
    bool Map::allSet()
    {
        // Return true if all Nodes have set = to true
        Node* q = this->head;
        bool hitDetect = false;
        while(q!=NULL)
        {
            if(q->set==false)
            {
                hitDetect = true;
            }
            q = q->next;
        }
        if(hitDetect==true)
        {
            return false;
        }
        else
        {
            return true;
        }
    }        
    
    // GREEN
    Map * miNavDevice::addMap()
    {
        // Create a Map
        Map * temp = new Map;
        Map * ptr;
        temp->next = NULL;
        if(this->head == NULL)
        {
            this->head = temp;
        }
        else
        {
            ptr = this->head;
            while(ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = temp;
        }
        Maps++;
        return temp;
    }
    
    // GREEN
    miNavDevice::miNavDevice()
    {
        // miNav Constructor
        head = NULL;
        Maps = 0;
    }
    
    // GREEN
    miNavDevice::~miNavDevice()
    {
        // miNav Destructor that deletes all maps created by it
        Map * q = head;
        Map* p;
        while(q!=NULL)
        {
            p = q->next;
            delete q;
            q = p;
        }
    }
    
    // YELLOW
    void miNavDevice::deleteMap(Map * target)
    {
        // Remove a Map from the miNav linked list and delete it
        if(target==this->head)
        {
            delete target;
            this->head = NULL;
        }
        else
        {
            Map * q = this->head;
            while(q->next!=target&&q->next!=NULL)
            {
                q=q->next;
            }
            if(q->next!=NULL)
            {
                q->next = target->next;
                delete target;
            }
        }
        this->Maps--;
    }
}
