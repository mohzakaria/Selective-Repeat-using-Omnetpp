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
#include "Node1.h"

#include "nodeMessage_m.h"
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

Define_Module(Node1);
////////////////////////////////////////
//sender
std::vector<std::string> proccesedMessage1;
std::vector<std::string> message1;
std::vector<std::string> prefix1;
vector <bool>ACKS1;
std::vector<std::string> processedMessages1;
vector <bool>Timeout1;
vector <bool>Received;
int expectedseqnumber1=0;
ofstream outputFile1;
int seqNum1=0;


vector <int> duplicates1;
vector <double> delays1;
vector<int> modfiedbit1;

vector <string> LOSS1;

///////////////////////////////////////
int ExpectedFrameNumber1=0;
vector<int> recievedseqnum1;
int counter1=1;
int seqsize1=0;

void Node1::processingAndSending(int i,int k)
{
    //processedMessages1.push_back(std::string("At Time ") + SIMTIME_STR(simTime()) + ", Node 1, Introducing channel error with code = " + prefix1[i]);

    processedMessages1.push_back("At Time " + simTime().str() + ", Node 1, Introducing channel error with code = " + prefix1[i]);
    EV << "At Time " + simTime().str() + ", Node 1, Introducing channel error with code = " + prefix1[i] << endl;
    std::string result; // Initialize the result string here
    std::bitset<8> checksum(0);
    string s , check , timeprint;
    std::vector<std::bitset<8>> messageBits;
    int Modificationn=-1;
    string lost="NO";
    int duplication=0;
    double delay=0;

    for (int j = 0; j < message1[i].size(); j++) {
        std::bitset<8> charBit(message1[i][j]);
        messageBits.push_back(charBit);
        checksum = checksum ^ charBit;
    }

    std::string tempstring= "#";
    for(int j=0;j<message1[i].size();j++)
    {

        if(message1[i][j]=='/'||message1[i][j]=='#')
        {
            tempstring+='/';
        }
        tempstring+=message1[i][j];
    }
    tempstring+='#';
    message1[i]=tempstring;

    nodeMessage_Base *tosendmessage =new nodeMessage_Base("data");

    tosendmessage->setSeqNumber(i);
    tosendmessage ->setType(0);
    tosendmessage->setChecksum(checksum);


    if (prefix1[i][1] == '1') //loss
    {
        LOSS1[i] = "Yes";
        lost="Yes";
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));
        Timeout1[i]=true;
        tosendmessage->setPayload(message1[i].c_str());
        // processedMessages1.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + (double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))) + " Time out event has occured, at Node 1 for frame with seq_Num " + std::to_string(i));
        scheduleAt(simTime()+(double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit1[i]) + " Lost Yes" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);
        EV << s << endl;
        processedMessages1.push_back(s);

    }
    else if(prefix1[i][0] == '1')//modification
    {

        bool temp=true;
        int index;
        while(temp){
            index = intuniform(0, messageBits.size() - 1);
            if(message1[i][index]!='/' || message1[i][index]!='#')
            {
                temp=false;
            }
            Modificationn=index;
        }
        int bitRandom = intuniform(0, 7);

        messageBits[index].flip(bitRandom);
        modfiedbit1[i] = index;
        string result = "#";
        for (int w = 0; w < messageBits.size(); w++) {
            char c = static_cast<char>(messageBits[w].to_ulong());
            result += c;
        }
        result+="#";

        tosendmessage->setPayload(result.c_str());
        tosendmessage->setChecksum(checksum);
        if(prefix1[i][3]=='1')//Modification && delay
        {
            timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));
            delay=(double)getParentModule()->par("ED");
            delays1[i] = (double)getParentModule()->par("ED");
            check = tosendmessage->getChecksum().to_string();
            s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                    " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

            EV << s << endl;
            processedMessages1.push_back(s);
            scheduleAt(simTime()+(double)getParentModule()->par("ED")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
            if((double)getParentModule()->par("ED")>(double)getParentModule()->par("TO")){
                nodeMessage_Base *tosendmessage3 =new nodeMessage_Base("data");
                LOSS1[i] = "Yes";
                tosendmessage3->setSeqNumber(i);
                tosendmessage3 ->setType(0);
                tosendmessage3->setChecksum(checksum);
                tosendmessage3->setPayload(tosendmessage->getPayload());
                //processedMessages1.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + (double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))) + " Time out event has occured, at Node 1 for frame with seq_Num " + std::to_string(i));
                scheduleAt(simTime()+(double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage3);
            }
            if (prefix1[i][2] == '1')//Modification && delay & duplicate
            {
                timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
                nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
                duplication=2;
                duplicates1[i] = 2;
                tosendmessage2->setSeqNumber(i);
                tosendmessage2 ->setType(0);
                tosendmessage2->setChecksum(checksum);
                tosendmessage2->setPayload(tosendmessage->getPayload());
                check = tosendmessage->getChecksum().to_string();
                s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                        " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

                EV << s << endl;
                processedMessages1.push_back(s);
                scheduleAt(simTime()+(double)getParentModule()->par("ED") +(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);

            }
        }
        else//Modification
        {
            timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));
            check = tosendmessage->getChecksum().to_string();
            s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                    " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

            EV << s << endl;
            processedMessages1.push_back(s);
            scheduleAt(simTime()+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
            if (prefix1[i][2] == '1')//Modification & duplicate
            {
                timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
                nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
                duplication=2;
                duplicates1[i] = 2;
                tosendmessage2->setSeqNumber(i);
                tosendmessage2 ->setType(0);
                tosendmessage2->setChecksum(checksum);
                tosendmessage2->setPayload(tosendmessage->getPayload());
                check = tosendmessage->getChecksum().to_string();
                s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                        " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

                EV << s << endl;
                processedMessages1.push_back(s);
                scheduleAt(simTime()+(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);
            }
        }


    }

    else if(prefix1[i][3]=='1')//delay
    {  tosendmessage->setPayload(message1[i].c_str());
    delay=(double)getParentModule()->par("ED");
    delays1[i] = (double)getParentModule()->par("ED");
    timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));

    check = tosendmessage->getChecksum().to_string();
    s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
            " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

    processedMessages1.push_back(s);
    EV << s << endl;
    scheduleAt(simTime()+(double)getParentModule()->par("ED")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
    if((double)getParentModule()->par("ED")>(double)getParentModule()->par("TO")){
        nodeMessage_Base *tosendmessage3 =new nodeMessage_Base("data");
        LOSS1[i] = "Yes";
        tosendmessage3->setSeqNumber(i);
        tosendmessage3 ->setType(0);
        tosendmessage3->setChecksum(checksum);
        tosendmessage3->setPayload(tosendmessage->getPayload());
        //processedMessages1.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + (double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))) + " Time out event has occured, at Node 1 for frame with seq_Num " + std::to_string(i));
        scheduleAt(simTime()+(double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage3);
    }
    if (prefix1[i][2] == '1')//delay & duplicate
    {
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
        nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
        duplication=1;
        duplicates1[i] = 1;
        tosendmessage2->setSeqNumber(i);
        tosendmessage2 ->setType(0);
        tosendmessage2->setChecksum(checksum);
        tosendmessage2->setPayload(tosendmessage->getPayload());
        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

        EV << s << endl;
        processedMessages1.push_back(s);
        scheduleAt(simTime()+(double)getParentModule()->par("ED") +(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);
    }
    }
    else if (prefix1[i][2] == '1')//duplicate
    {
        duplication=1;
        duplicates1[i] = 1;
        tosendmessage->setPayload(message1[i].c_str());
        nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) );

        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

        processedMessages1.push_back(s);
        EV << s << endl;
        scheduleAt(simTime()+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
        tosendmessage2->setSeqNumber(i);
        tosendmessage2 ->setType(0);
        tosendmessage2->setChecksum(checksum);
        tosendmessage2->setPayload(tosendmessage->getPayload());
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

        EV << s << endl;
        processedMessages1.push_back(s);
        scheduleAt(simTime()+(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);
    }
    else{
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));

        tosendmessage->setPayload(message1[i].c_str());
        check = tosendmessage->getChecksum().to_string();
               s = "At Time " + timeprint + ", Node 1 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                       " Modified " + to_string(modfiedbit1[i]) + " Lost No" + " Duplication " + to_string(duplicates1[i]) + " Delay " + to_string(delays1[i]);

               EV << s << endl;
               processedMessages1.push_back(s);
        scheduleAt(simTime() +k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
    }
    string variableStore=tosendmessage->getPayload();
    string variableStored="";
    for(int k=1;k<variableStore.size()-1;k++)
    {
        variableStored+=variableStore[k];
    }

    //    processedMessages1.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + k*((double)getParentModule()->par("PT"))) +
    //            ", Node 1 Sent a Frame with seq_num " + std::to_string(i) +
    //            " and payload = " + variableStored +
    //            " and trailer = " + to_string(tosendmessage->getChecksum().to_ulong()) + // Convert bitset to string
    //            " Modified " + std::to_string(Modificationn) +
    //            " Lost " + lost +
    //            " Duplication " + std::to_string(duplication) +
    //            " Delay " + std::to_string(delay));

}
void Node1::initialize()
{
    for(int i=0;i<(int)getParentModule()->par("WR");i++)
    {
        Received.push_back(false);
    }

    std::ifstream inputFile;
    std::string line;
    inputFile.open("../../Networks_Project/src/input1.txt");

    if (!inputFile.is_open()) {
        EV << "Error opening input file\n";
        return;
    }
    while (getline(inputFile, line)) {
        prefix1.push_back(line.substr(0, 4));
        message1.push_back(line.substr(5, line.size()));
        ACKS1.push_back(false);
        Timeout1.push_back(false);
    }
    seqsize1 = message1.size();
    modfiedbit1.resize(seqsize1 , -1);
    duplicates1.resize(seqsize1 , 0);
    delays1.resize(seqsize1 , 0);
    LOSS1.resize(seqsize1 , "NO");
}

void Node1::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        nodeMessage_Base *sendedmessage = check_and_cast<nodeMessage_Base*>(msg);
        if(sendedmessage->getType()== 0 && Timeout1[sendedmessage->getSeqNumber()])
        {
            string time = "TimeOut event at time " + to_string(simTime().dbl() - (double)getParentModule()->par("TD")) + " at Node 1 for frame with sequence number= " + to_string(sendedmessage->getSeqNumber());
            string check = sendedmessage->getChecksum().to_string();

            string s = "At Time " + to_string(simTime().dbl() - (double)getParentModule()->par("TD") ) + ", Node 1 Sent a Frame with seq_num " +
                    to_string(sendedmessage->getSeqNumber()) + " and payload = " + sendedmessage->getPayload() + " and trailer= " +  check +
                    " Modified " + to_string(modfiedbit1[sendedmessage->getSeqNumber()]) + "Lost " + LOSS1[sendedmessage->getSeqNumber()]
                                                                                                         + " Duplication " + to_string(duplicates1[sendedmessage->getSeqNumber()]) + " Delay " + to_string(delays1[sendedmessage->getSeqNumber()]);
            processedMessages1.push_back(time);
            processedMessages1.push_back(s);

            EV << time << endl;
            EV << s << endl;
        }
        else if(sendedmessage->getType()== 1 || sendedmessage->getType()== 2) {
            string con;
            if(sendedmessage->getType() == 1)
                con = "ACK";
            else con = "NACK";
            string control = "At Time " + to_string(simTime().dbl() ) +  " Node 1 Sending " + con + " sequence number= " + to_string(sendedmessage->getSeqNumber()) +
                    " Loss " + LOSS1[sendedmessage->getSeqNumber()];
            processedMessages1.push_back(control);
            EV << control << endl;
        }
        send(sendedmessage,"outGate");


    }
    else{
        std::string fromGate = msg->getArrivalGate()->getName();
        if (fromGate == "inGateCoord") {
            for(int seqNum1=0;seqNum1<(int)getParentModule()->par("WS");seqNum1++)
            {
                processingAndSending(seqNum1,seqNum1+1);
            }
        }
        else if(fromGate == "inGateNode")
        {
            nodeMessage_Base *recivedmessage = check_and_cast<nodeMessage_Base*>(msg);
            if(recivedmessage->getType()==1)
            {
                string control = "At Time " + to_string(simTime().dbl() ) +  " Node 0 Sending ACK sequence number= " + to_string(recivedmessage->getSeqNumber()) +
                                        " Loss " + LOSS1[recivedmessage->getSeqNumber()];
                                processedMessages1.push_back(control);
                string x="No";
                if(Timeout1[recivedmessage->getSeqNumber()]==true)
                {
                    x="Yes";
                }
                //processedMessages1.push_back(std::string("At Time ") + SIMTIME_STR(simTime() - (double)getParentModule()->par("TD")) + ", Node 1 Sending a ACK with number " + std::to_string(recivedmessage->getSeqNumber()) + ", Loss " + x);
                //EV<<"from recciver  "<<recivedmessage->getSeqNumber();
                int recivedseqnum=recivedmessage->getSeqNumber();
                ACKS1[recivedseqnum]=true;
                int k=1;
                while(ACKS1[expectedseqnumber1])
                {
                    if(expectedseqnumber1+(int)getParentModule()->par("WS")<message1.size()){

                        processingAndSending(expectedseqnumber1+(int)getParentModule()->par("WS"),k);
                    }k++;
                    expectedseqnumber1++;
                }

            }
            else if(recivedmessage->getType()==2)
            {
                string control = "At Time " + to_string(simTime().dbl() ) +  " Node 0 Sending NACK sequence number= " + to_string(recivedmessage->getSeqNumber()) +
                                        " Loss " + LOSS1[recivedmessage->getSeqNumber()];
                                processedMessages1.push_back(control);
                //EV<<"ANA NACK"<<recivedmessage->getSeqNumber();
                //processedMessages1.push_back(std::string("At Time ") + SIMTIME_STR(simTime() - (double)getParentModule()->par("TD")) + ", Node 1 Sending a NACK with number " + std::to_string(recivedmessage->getSeqNumber()));
                std::vector<std::bitset<8>> messageBits;
                std::bitset<8> checksum(0);
                int recivedseqnum=recivedmessage->getSeqNumber();
                nodeMessage_Base *retransmit =new nodeMessage_Base("data");
                string PureMessage="";
                vector<bitset<8>> MessageBits;
                bool FirstEsc=false;
                // awel haga hakhod el payload afadih men el byte stuffing
                for(int i=1;i<(message1[recivedseqnum].size())-1;i++)
                {

                    if(message1[recivedseqnum][i]!='/')// law mesh esc khod el character
                    {
                        PureMessage+=message1[recivedseqnum][i];// shelt el esc
                        bitset<8> CharacterToPush(message1[recivedseqnum][i]);
                        MessageBits.push_back(CharacterToPush);
                        FirstEsc = false;

                    }
                    else
                    {
                        if(FirstEsc == true) // law tany esc hanakhodha
                        {
                            PureMessage+=message1[recivedseqnum][i];// shelt el esc
                            bitset<8> CharacterToPush(message1[recivedseqnum][i]);
                            MessageBits.push_back(CharacterToPush);
                            FirstEsc = false;
                        }
                        else // law awel esc hannfkesha
                        {
                            FirstEsc = true;
                        }
                    }
                }
                // ma3ana message1 mn gher esc ayzin methawela lel bit representation
                bitset<8> EXOR(0);
                for(int i=0;i<MessageBits.size();i++)
                {
                    EXOR=EXOR^MessageBits[i];
                }
                retransmit->setSeqNumber(recivedseqnum);
                retransmit ->setType(0);
                retransmit->setChecksum(EXOR);
                retransmit->setPayload(message1[recivedseqnum].c_str());
                scheduleAt(simTime() +(double)getParentModule()->par("PT")+(double)getParentModule()->par("TD"), retransmit);

            }

            if(recivedmessage->getType()==0)
            {
                for(int i = 0 ; i < recievedseqnum1.size() ; i++)
                {
                    if(recievedseqnum1[i] == recivedmessage->getSeqNumber())
                    {
                       // EV<<"ANA ALREADY RECCIVED "<<recievedseqnum1[i]<<endl;
                        return;
                    }
                }
                if(recivedmessage->getSeqNumber()>=ExpectedFrameNumber1 && recivedmessage->getSeqNumber()<=ExpectedFrameNumber1+(int)getParentModule()->par("WS"))
                {

                    string MessageLoad=(recivedmessage->getPayload());
                    string PureMessage="";
                    vector<bitset<8>> MessageBits;
                    bool FirstEsc=false;
                    // awel haga hakhod el payload afadih men el byte stuffing
                    for(int i=1;i<(MessageLoad.size())-1;i++)
                    {

                        if(MessageLoad[i]!='/')// law mesh esc khod el character
                        {
                            PureMessage+=MessageLoad[i];// shelt el esc
                            bitset<8> CharacterToPush(MessageLoad[i]);
                            MessageBits.push_back(CharacterToPush);
                            FirstEsc = false;

                        }
                        else
                        {
                            if(FirstEsc == true) // law tany esc hanakhodha
                            {
                                PureMessage+=MessageLoad[i];// shelt el esc
                                bitset<8> CharacterToPush(MessageLoad[i]);
                                MessageBits.push_back(CharacterToPush);
                                FirstEsc = false;
                            }
                            else // law awel esc hannfkesha
                            {
                                FirstEsc = true;
                            }
                        }
                    }

                    // ma3ana message1 mn gher esc ayzin methawela lel bit representation
                    bitset<8> EXOR(0);
                    for(int i=0;i<MessageBits.size();i++)
                    {
                        EXOR=EXOR^MessageBits[i];
                    }

                    // keda hanbda2 n compare el checksum ely hasbnah bel checksum el received law ad b3d yb2a sah law laa yb2a ghalat

                    if(EXOR==recivedmessage->getChecksum())
                    {
                        if(recivedmessage->getSeqNumber()==ExpectedFrameNumber1)
                        {

                            Received[ExpectedFrameNumber1]=true;
                            for(int y=ExpectedFrameNumber1;y<ExpectedFrameNumber1+(int)getParentModule()->par("WR");y++)
                            {

                                if(Received[y])
                                {
                                    ExpectedFrameNumber1++;
                                    Received.push_back(false);
                                }
                                else
                                {
                                    break;
                                }
                            }


                        }
                        else
                        {
                         //   EV<<"ksamdkmaskfmsakmgflksadlgmklsmgksdomfkasdm"<<endl;
                            Received[recivedmessage->getSeqNumber()]=true;
                           // EV<<"m"<<endl;
                        }

                        recievedseqnum1.push_back(recivedmessage->getSeqNumber());
                        recivedmessage->setType(1); // positive ack w sa3etha haset el seq number bel current + ws ashan kolo recieved sah
                        //EV<<"ANA HAB3AT DELWATY "<<simTime()<<"SEQ NUM"<<recivedmessage->getSeqNumber()<<endl;
                        scheduleAt(simTime()+(double)getParentModule()->par("TD"), recivedmessage);

                    }
                    else
                    {
                       // EV<<"EEEEXXXXXXXXOOOOORRRR"<<EXOR<<endl;
                        //EV<<"Wrong Nack sent"<<simTime()<<endl;
                        recivedmessage->setType(2); // negative ack
                        scheduleAt(simTime()+(double)getParentModule()->par("TD"), recivedmessage);

                    }

                }
            }

        }


    }

    // TODO - Generated method body
    int z=1;
    for(int p=0;p<ACKS1.size();p++)
    {
        if(ACKS1[p]==false)
        {z=0;
        break;
        }
    }
    if(z==1)
    {
        outputFile1.open("../output.txt");
        if (!outputFile1.is_open()) {
            cout << "Error opening output file";
        } else {
            for (const auto& msg : processedMessages1) {
                outputFile1 << msg << endl;
            }
            outputFile1.close();
        }
    }

}
