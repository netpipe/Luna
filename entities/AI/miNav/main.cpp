////=============================
////Please include the miNav header and link to the miNav.o file
////=============================
//#include <iostream>
//#include "miNav.h"
//
//using namespace std;
//using namespace miNav;
//
//int mainsss()
//{
//    cout << "Creating miNavDevice\n";
////    system("PAUSE");
//    miNavDevice* myDevice = new miNavDevice;
//
//    cout << "Creating Map\n";
//  //  system("PAUSE");
//    Map* myMap = myDevice->addMap();
//
//    cout << "Adding Nodes\n";
////    system("PAUSE");
//    Node* N1 = myMap->addNode(49,34,0);
//    Node* N2 = myMap->addNode(240,9,0);
//    Node* N3 = myMap->addNode(462,35,0);
//    Node* N4 = myMap->addNode(147,62,0);
//    Node* N5 = myMap->addNode(208,77,0);
//    Node* N6 = myMap->addNode(274,64,0);
//    Node* N7 = myMap->addNode(398,67,0);
//    Node* N8 = myMap->addNode(97,93,0);
//    Node* N9 = myMap->addNode(169,111,0);
//    Node* N10 = myMap->addNode(240,116,0);
//    Node* N11 = myMap->addNode(301,124,0);
//    Node* N12 = myMap->addNode(345,90,0);
//    Node* N13 = myMap->addNode(393,121,0);
//    Node* N14 = myMap->addNode(44,119,0);
//    Node* N15 = myMap->addNode(77,154,0);
//    Node* N16 = myMap->addNode(146,188,0);
//    Node* N17 = myMap->addNode(213,192,0);
//    Node* N18 = myMap->addNode(253,171,0);
//    Node* N19 = myMap->addNode(365,169,0);
//    Node* N20 = myMap->addNode(43,200,0);
//    Node* N21 = myMap->addNode(429,198,0);
//    Node* N22 = myMap->addNode(90,260,0);
//    Node* N23 = myMap->addNode(198,266,0);
//    Node* N24 = myMap->addNode(269,241,0);
//    Node* N25 = myMap->addNode(314,233,0);
//    Node* N26 = myMap->addNode(384,223,0);
//    Node* N27 = myMap->addNode(123,330,0);
//    Node* N28 = myMap->addNode(251,301,0);
//    Node* N29 = myMap->addNode(322,312,0);
//    Node* N30 = myMap->addNode(373,287,0);
//    Node* N31 = myMap->addNode(440,305,0);
//    Node* N32 = myMap->addNode(55,372,0);
//    Node* N33 = myMap->addNode(177,368,0);
//    Node* N34 = myMap->addNode(319,389,0);
//    Node* N35 = myMap->addNode(472,374,0);
//    Node* N36 = myMap->addNode(45,317,0);
//
//    cout << "Connecting Nodes\n";
////    system("PAUSE");
//    myMap->connect2way(N1,N4);
//    myMap->connect2way(N1,N8);
//    myMap->connect2way(N1,N14);
//    myMap->connect2way(N2,N5);
//    myMap->connect2way(N2,N6);
//    myMap->connect2way(N3,N7);
//    myMap->connect2way(N4,N8);
//    myMap->connect2way(N4,N9);
//    myMap->connect2way(N4,N5);
//    myMap->connect2way(N5,N6);
//    myMap->connect2way(N5,N9);
//    myMap->connect2way(N5,N10);
//    myMap->connect2way(N6,N10);
//    myMap->connect2way(N6,N11);
//    myMap->connect2way(N6,N12);
//    myMap->connect2way(N7,N12);
//    myMap->connect2way(N7,N13);
//    myMap->connect2way(N8,N14);
//    myMap->connect2way(N8,N15);
//    myMap->connect2way(N8,N9);
//    myMap->connect2way(N9,N15);
//    myMap->connect2way(N9,N16);
//    myMap->connect2way(N9,N17);
//    myMap->connect2way(N9,N10);
//    myMap->connect2way(N10,N11);
//    myMap->connect2way(N10,N17);
//    myMap->connect2way(N10,N18);
//    myMap->connect2way(N11,N18);
//    myMap->connect2way(N11,N19);
//    myMap->connect2way(N11,N12);
//    myMap->connect2way(N12,N13);
//    myMap->connect2way(N13,N19);
//    myMap->connect2way(N14,N15);
//    myMap->connect2way(N14,N20);
//    myMap->connect2way(N15,N20);
//    myMap->connect2way(N15,N22);
//    myMap->connect2way(N15,N16);
//    myMap->connect2way(N16,N17);
//    myMap->connect2way(N16,N22);
//    myMap->connect2way(N16,N23);
//    myMap->connect2way(N17,N23);
//    myMap->connect2way(N17,N24);
//    myMap->connect2way(N17,N18);
//    myMap->connect2way(N18,N24);
//    myMap->connect2way(N18,N25);
//    myMap->connect2way(N19,N25);
//    myMap->connect2way(N19,N26);
//    myMap->connect2way(N19,N21);
//    myMap->connect2way(N20,N22);
//    myMap->connect2way(N21,N26);
//    myMap->connect2way(N22,N23);
//    myMap->connect2way(N22,N27);
//    myMap->connect2way(N22,N36);
//    myMap->connect2way(N23,N27);
//    myMap->connect2way(N23,N33);
//    myMap->connect2way(N23,N28);
//    myMap->connect2way(N23,N24);
//    myMap->connect2way(N24,N28);
//    myMap->connect2way(N24,N29);
//    myMap->connect2way(N24,N25);
//    myMap->connect2way(N25,N29);
//    myMap->connect2way(N25,N30);
//    myMap->connect2way(N25,N26);
//    myMap->connect2way(N26,N30);
//    myMap->connect2way(N27,N36);
//    myMap->connect2way(N27,N32);
//    myMap->connect2way(N27,N33);
//    myMap->connect2way(N28,N29);
//    myMap->connect2way(N29,N34);
//    myMap->connect2way(N29,N30);
//    myMap->connect2way(N30,N31);
//    myMap->connect2way(N31,N35);
//    myMap->connect2way(N32,N36);
//
//    cout << "Solving Nodes\n";
////    system("PAUSE");
//    myMap->solve();
//    cout << "Solve Complete\n";
////    system("PAUSE");
//
//    cout << "Testing the Solved Results, travelling from one side of the map to the other\n";
////    system("PAUSE");
//    Node* Position = N1;
//    Node* Destination = N35;
//    cout << "Position = (" << Position->X << "," << Position->Y << ")\n";
//    while(Position!=Destination)
//    {
//        Position = myMap->getSolution(Position,Destination);
//        cout << "Position = (" << Position->X << "," << Position->Y << ")\n";
//    }
//    cout << "Reached Destination, Solutions working!\n";
////    system("PAUSE");
//
//    delete myDevice;
//
//    return 0;
//}
