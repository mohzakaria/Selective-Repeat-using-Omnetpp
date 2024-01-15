//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Coordinator.h"
#include <fstream>
Define_Module(Coordinator);
using namespace std;


std::string node = "outGateNode";
void Coordinator::initialize()
{

    std::string line;
    std::ifstream inputFile;
    inputFile.open("../../Networks_Project/src/Coordinator.txt");

    if (!inputFile.is_open()) {
        std::cout << "Error opening file" << std::endl;
    } else {
        std::string startingNode;
        std::string startingTime;

        while (getline(inputFile, line)) {
            EV << line << std::endl;

            if (!line.empty()) {
                startingNode = line[0];
                startingTime = line.substr(1);

                // Append the first character to the 'node' string
                node += startingNode;

                // Create and send a message
                cMessage *msg = new cMessage("startSession");
                scheduleAt( stoi(startingTime), msg);

            }
        }

        inputFile.close();  // Close the file when done
    }


}

void Coordinator::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage())
        {
            send(msg,node.c_str());
        }
}
