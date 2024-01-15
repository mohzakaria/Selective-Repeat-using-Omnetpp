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
#include "Node0.h"

#include "nodeMessage_m.h"
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

Define_Module(Node0);
////////////////////////////////////////
//sender
std::vector<std::string> proccesedMessage;
std::vector<std::string> message;
std::vector<std::string> prefix;
vector <bool>ACKS;
std::vector<std::string> processedMessages;
vector <bool>Timeout;
vector <bool>Received1;
int expectedseqnumber=0;
ofstream outputFile;
int seqNum=0;


vector <int> duplicates;
vector <double> delays;
vector<int> modfiedbit;

vector <string> LOSS;

///////////////////////////////////////
int ExpectedFrameNumber=0;
vector<int> recievedseqnum;
int counter=1;
int seqsize=0;

void Node0::processingAndSending(int i,int k)
{
    //processedMessages.push_back(std::string("At Time ") + SIMTIME_STR(simTime()) + ", Node 0, Introducing channel error with code = " + prefix[i]);

    processedMessages.push_back("At Time " + simTime().str() + ", Node 0, Introducing channel error with code = " + prefix[i]);
    EV << "At Time " + simTime().str() + ", Node 0, Introducing channel error with code = " + prefix[i] << endl;
    std::string result; // Initialize the result string here
    std::bitset<8> checksum(0);
    string s , check , timeprint;
    std::vector<std::bitset<8>> messageBits;
    int Modificationn=-1;
    string lost="NO";
    int duplication=0;
    double delay=0;

    for (int j = 0; j < message[i].size(); j++) {
        std::bitset<8> charBit(message[i][j]);
        messageBits.push_back(charBit);
        checksum = checksum ^ charBit;
    }

    std::string tempstring= "#";
    for(int j=0;j<message[i].size();j++)
    {

        if(message[i][j]=='/'||message[i][j]=='#')
        {
            tempstring+='/';
        }
        tempstring+=message[i][j];
    }
    tempstring+='#';
    message[i]=tempstring;

    nodeMessage_Base *tosendmessage =new nodeMessage_Base("data");

    tosendmessage->setSeqNumber(i);
    tosendmessage ->setType(0);
    tosendmessage->setChecksum(checksum);


    if (prefix[i][1] == '1') //loss
    {
        LOSS[i] = "Yes";
        lost="Yes";
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));
        Timeout[i]=true;
        tosendmessage->setPayload(message[i].c_str());
        // processedMessages.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + (double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))) + " Time out event has occured, at Node 0 for frame with seq_Num " + std::to_string(i));
        scheduleAt(simTime()+(double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit[i]) + " Lost Yes" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);
        EV << s << endl;
        processedMessages.push_back(s);

    }
    else if(prefix[i][0] == '1')//modification
    {

        bool temp=true;
        int index;
        while(temp){
            index = intuniform(0, messageBits.size() - 1);
            if(message[i][index]!='/' || message[i][index]!='#')
            {
                temp=false;
            }
            Modificationn=index;
        }
        int bitRandom = intuniform(0, 7);

        messageBits[index].flip(bitRandom);
        modfiedbit[i] = index;
        string result = "#";
        for (int w = 0; w < messageBits.size(); w++) {
            char c = static_cast<char>(messageBits[w].to_ulong());
            result += c;
        }
        result+="#";

        tosendmessage->setPayload(result.c_str());
        tosendmessage->setChecksum(checksum);
        if(prefix[i][3]=='1')//Modification && delay
        {
            timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));
            delay=(double)getParentModule()->par("ED");
            delays[i] = (double)getParentModule()->par("ED");
            check = tosendmessage->getChecksum().to_string();
            s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                    " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

            EV << s << endl;
            processedMessages.push_back(s);
            scheduleAt(simTime()+(double)getParentModule()->par("ED")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
            if((double)getParentModule()->par("ED")>(double)getParentModule()->par("TO")){
                nodeMessage_Base *tosendmessage3 =new nodeMessage_Base("data");
                LOSS[i] = "Yes";
                tosendmessage3->setSeqNumber(i);
                tosendmessage3 ->setType(0);
                tosendmessage3->setChecksum(checksum);
                tosendmessage3->setPayload(tosendmessage->getPayload());
                //processedMessages.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + (double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))) + " Time out event has occured, at Node 0 for frame with seq_Num " + std::to_string(i));
                scheduleAt(simTime()+(double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage3);
            }
            if (prefix[i][2] == '1')//Modification && delay & duplicate
            {
                timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
                nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
                duplication=2;
                duplicates[i] = 2;
                tosendmessage2->setSeqNumber(i);
                tosendmessage2 ->setType(0);
                tosendmessage2->setChecksum(checksum);
                tosendmessage2->setPayload(tosendmessage->getPayload());
                check = tosendmessage->getChecksum().to_string();
                s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                        " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

                EV << s << endl;
                processedMessages.push_back(s);
                scheduleAt(simTime()+(double)getParentModule()->par("ED") +(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);

            }
        }
        else//Modification
        {
            timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));
            check = tosendmessage->getChecksum().to_string();
            s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                    " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

            EV << s << endl;
            processedMessages.push_back(s);
            scheduleAt(simTime()+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
            if (prefix[i][2] == '1')//Modification & duplicate
            {
                timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
                nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
                duplication=2;
                duplicates[i] = 2;
                tosendmessage2->setSeqNumber(i);
                tosendmessage2 ->setType(0);
                tosendmessage2->setChecksum(checksum);
                tosendmessage2->setPayload(tosendmessage->getPayload());
                check = tosendmessage->getChecksum().to_string();
                s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                        " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

                EV << s << endl;
                processedMessages.push_back(s);
                scheduleAt(simTime()+(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);
            }
        }


    }

    else if(prefix[i][3]=='1')//delay
    {  tosendmessage->setPayload(message[i].c_str());
    delay=(double)getParentModule()->par("ED");
    delays[i] = (double)getParentModule()->par("ED");
    timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));

    check = tosendmessage->getChecksum().to_string();
    s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
            " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

    processedMessages.push_back(s);
    EV << s << endl;
    scheduleAt(simTime()+(double)getParentModule()->par("ED")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
    if((double)getParentModule()->par("ED")>(double)getParentModule()->par("TO")){
        nodeMessage_Base *tosendmessage3 =new nodeMessage_Base("data");
        LOSS[i] = "Yes";
        tosendmessage3->setSeqNumber(i);
        tosendmessage3 ->setType(0);
        tosendmessage3->setChecksum(checksum);
        tosendmessage3->setPayload(tosendmessage->getPayload());
        //processedMessages.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + (double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))) + " Time out event has occured, at Node 0 for frame with seq_Num " + std::to_string(i));
        scheduleAt(simTime()+(double)getParentModule()->par("TO")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage3);
    }
    if (prefix[i][2] == '1')//delay & duplicate
    {
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
        nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
        duplication=1;
        duplicates[i] = 1;
        tosendmessage2->setSeqNumber(i);
        tosendmessage2 ->setType(0);
        tosendmessage2->setChecksum(checksum);
        tosendmessage2->setPayload(tosendmessage->getPayload());
        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

        EV << s << endl;
        processedMessages.push_back(s);
        scheduleAt(simTime()+(double)getParentModule()->par("ED") +(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);
    }
    }
    else if (prefix[i][2] == '1')//duplicate
    {
        duplication=1;
        duplicates[i] = 1;
        tosendmessage->setPayload(message[i].c_str());
        nodeMessage_Base *tosendmessage2 =new nodeMessage_Base("data");
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) );

        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

        processedMessages.push_back(s);
        EV << s << endl;
        scheduleAt(simTime()+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
        tosendmessage2->setSeqNumber(i);
        tosendmessage2 ->setType(0);
        tosendmessage2->setChecksum(checksum);
        tosendmessage2->setPayload(tosendmessage->getPayload());
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")) + (double)getParentModule()->par("DD"));
        check = tosendmessage->getChecksum().to_string();
        s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

        EV << s << endl;
        processedMessages.push_back(s);
        scheduleAt(simTime()+(double) getParentModule()->par("DD")+k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage2);
    }
    else{
        timeprint = to_string(simTime().dbl()+k*((double)getParentModule()->par("PT")));

        tosendmessage->setPayload(message[i].c_str());
        check = tosendmessage->getChecksum().to_string();
               s = "At Time " + timeprint + ", Node 0 Sent a Frame with seq_num " + to_string(i) + " and payload = " + tosendmessage->getPayload() + " and trailer= " +  check +
                       " Modified " + to_string(modfiedbit[i]) + " Lost No" + " Duplication " + to_string(duplicates[i]) + " Delay " + to_string(delays[i]);

               EV << s << endl;
               processedMessages.push_back(s);
        scheduleAt(simTime() +k*((double)getParentModule()->par("PT"))+(double)getParentModule()->par("TD"), tosendmessage);
    }
    string variableStore=tosendmessage->getPayload();
    string variableStored="";
    for(int k=1;k<variableStore.size()-1;k++)
    {
        variableStored+=variableStore[k];
    }

    //    processedMessages.push_back(std::string("At Time ") + SIMTIME_STR(simTime() + k*((double)getParentModule()->par("PT"))) +
    //            ", Node 0 Sent a Frame with seq_num " + std::to_string(i) +
    //            " and payload = " + variableStored +
    //            " and trailer = " + to_string(tosendmessage->getChecksum().to_ulong()) + // Convert bitset to string
    //            " Modified " + std::to_string(Modificationn) +
    //            " Lost " + lost +
    //            " Duplication " + std::to_string(duplication) +
    //            " Delay " + std::to_string(delay));

}
void Node0::initialize()
{
    for(int i=0;i<(int)getParentModule()->par("WR");i++)
    {
        Received1.push_back(false);
    }

    std::ifstream inputFile;
    std::string line;
    inputFile.open("../../Networks_Project/src/input0.txt");

    if (!inputFile.is_open()) {
        EV << "Error opening input file\n";
        return;
    }
    while (getline(inputFile, line)) {
        prefix.push_back(line.substr(0, 4));
        message.push_back(line.substr(5, line.size()));
        ACKS.push_back(false);
        Timeout.push_back(false);
    }
    seqsize = message.size();
    modfiedbit.resize(seqsize , -1);
    duplicates.resize(seqsize , 0);
    delays.resize(seqsize , 0);
    LOSS.resize(seqsize , "NO");
}

void Node0::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        nodeMessage_Base *sendedmessage = check_and_cast<nodeMessage_Base*>(msg);
        if(sendedmessage->getType()== 0 && Timeout[sendedmessage->getSeqNumber()])
        {
            string time = "TimeOut event at time " + to_string(simTime().dbl() - (double)getParentModule()->par("TD")) + " at Node 0 for frame with sequence number= " + to_string(sendedmessage->getSeqNumber());
            string check = sendedmessage->getChecksum().to_string();

            string s = "At Time " + to_string(simTime().dbl() - (double)getParentModule()->par("TD") ) + ", Node 0 Sent a Frame with seq_num " +
                    to_string(sendedmessage->getSeqNumber()) + " and payload = " + sendedmessage->getPayload() + " and trailer= " +  check +
                    " Modified " + to_string(modfiedbit[sendedmessage->getSeqNumber()]) + "Lost " + LOSS[sendedmessage->getSeqNumber()]
                                                                                                         + " Duplication " + to_string(duplicates[sendedmessage->getSeqNumber()]) + " Delay " + to_string(delays[sendedmessage->getSeqNumber()]);
            processedMessages.push_back(time);
            processedMessages.push_back(s);

            EV << time << endl;
            EV << s << endl;
        }
        else if(sendedmessage->getType()== 1 || sendedmessage->getType()== 2) {
            string con;
            if(sendedmessage->getType() == 1)
                con = "ACK";
            else con = "NACK";
            string control = "At Time " + to_string(simTime().dbl() ) +  " Node 0 Sending " + con + " sequence number= " + to_string(sendedmessage->getSeqNumber()) +
                    " Loss " + LOSS[sendedmessage->getSeqNumber()];
            processedMessages.push_back(control);
            EV << control << endl;
        }
        send(sendedmessage,"outGate");


    }
    else{
        std::string fromGate = msg->getArrivalGate()->getName();
        if (fromGate == "inGateCoord") {
            for(int seqNum=0;seqNum<(int)getParentModule()->par("WS");seqNum++)
            {
                processingAndSending(seqNum,seqNum+1);
            }
        }
        else if(fromGate == "inGateNode")
        {
            nodeMessage_Base *recivedmessage = check_and_cast<nodeMessage_Base*>(msg);
            if(recivedmessage->getType()==1)
            {
                string control = "At Time " + to_string(simTime().dbl() ) +  " Node 1 Sending ACK sequence number= " + to_string(recivedmessage->getSeqNumber()) +
                                        " Loss " + LOSS[recivedmessage->getSeqNumber()];
                                processedMessages.push_back(control);
                string x="No";
                if(Timeout[recivedmessage->getSeqNumber()]==true)
                {
                    x="Yes";
                }
                //processedMessages.push_back(std::string("At Time ") + SIMTIME_STR(simTime() - (double)getParentModule()->par("TD")) + ", Node 1 Sending a ACK with number " + std::to_string(recivedmessage->getSeqNumber()) + ", Loss " + x);
                //EV<<"from recciver  "<<recivedmessage->getSeqNumber();
                int recivedseqnum=recivedmessage->getSeqNumber();
                ACKS[recivedseqnum]=true;
                int k=1;
                while(ACKS[expectedseqnumber])
                {
                    if(expectedseqnumber+(int)getParentModule()->par("WS")<message.size()){

                        processingAndSending(expectedseqnumber+(int)getParentModule()->par("WS"),k);
                    }k++;
                    expectedseqnumber++;
                }

            }
            else if(recivedmessage->getType()==2)
            {
                string control = "At Time " + to_string(simTime().dbl() ) +  " Node 1 Sending NACK sequence number= " + to_string(recivedmessage->getSeqNumber()) +
                                        " Loss " + LOSS[recivedmessage->getSeqNumber()];
                                processedMessages.push_back(control);
                //EV<<"ANA NACK"<<recivedmessage->getSeqNumber();
                //processedMessages.push_back(std::string("At Time ") + SIMTIME_STR(simTime() - (double)getParentModule()->par("TD")) + ", Node 1 Sending a NACK with number " + std::to_string(recivedmessage->getSeqNumber()));
                std::vector<std::bitset<8>> messageBits;
                std::bitset<8> checksum(0);
                int recivedseqnum=recivedmessage->getSeqNumber();
                nodeMessage_Base *retransmit =new nodeMessage_Base("data");
                string PureMessage="";
                vector<bitset<8>> MessageBits;
                bool FirstEsc=false;
                // awel haga hakhod el payload afadih men el byte stuffing
                for(int i=1;i<(message[recivedseqnum].size())-1;i++)
                {

                    if(message[recivedseqnum][i]!='/')// law mesh esc khod el character
                    {
                        PureMessage+=message[recivedseqnum][i];// shelt el esc
                        bitset<8> CharacterToPush(message[recivedseqnum][i]);
                        MessageBits.push_back(CharacterToPush);
                        FirstEsc = false;

                    }
                    else
                    {
                        if(FirstEsc == true) // law tany esc hanakhodha
                        {
                            PureMessage+=message[recivedseqnum][i];// shelt el esc
                            bitset<8> CharacterToPush(message[recivedseqnum][i]);
                            MessageBits.push_back(CharacterToPush);
                            FirstEsc = false;
                        }
                        else // law awel esc hannfkesha
                        {
                            FirstEsc = true;
                        }
                    }
                }
                // ma3ana message mn gher esc ayzin methawela lel bit representation
                bitset<8> EXOR(0);
                for(int i=0;i<MessageBits.size();i++)
                {
                    EXOR=EXOR^MessageBits[i];
                }
                retransmit->setSeqNumber(recivedseqnum);
                retransmit ->setType(0);
                retransmit->setChecksum(EXOR);
                retransmit->setPayload(message[recivedseqnum].c_str());
                scheduleAt(simTime() +(double)getParentModule()->par("PT")+(double)getParentModule()->par("TD"), retransmit);

            }

            if(recivedmessage->getType()==0)
            {
                for(int i = 0 ; i < recievedseqnum.size() ; i++)
                {
                    if(recievedseqnum[i] == recivedmessage->getSeqNumber())
                    {
                       // EV<<"ANA ALREADY RECCIVED "<<recievedseqnum[i]<<endl;
                        return;
                    }
                }
                if(recivedmessage->getSeqNumber()>=ExpectedFrameNumber && recivedmessage->getSeqNumber()<=ExpectedFrameNumber+(int)getParentModule()->par("WS"))
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

                    // ma3ana message mn gher esc ayzin methawela lel bit representation
                    bitset<8> EXOR(0);
                    for(int i=0;i<MessageBits.size();i++)
                    {
                        EXOR=EXOR^MessageBits[i];
                    }

                    // keda hanbda2 n compare el checksum ely hasbnah bel checksum el received law ad b3d yb2a sah law laa yb2a ghalat

                    if(EXOR==recivedmessage->getChecksum())
                    {
                        if(recivedmessage->getSeqNumber()==ExpectedFrameNumber)
                        {

                            Received1[ExpectedFrameNumber]=true;
                            for(int y=ExpectedFrameNumber;y<ExpectedFrameNumber+(int)getParentModule()->par("WR");y++)
                            {

                                if(Received1[y])
                                {
                                    ExpectedFrameNumber++;
                                    Received1.push_back(false);
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
                            Received1[recivedmessage->getSeqNumber()]=true;
                           // EV<<"m"<<endl;
                        }

                        recievedseqnum.push_back(recivedmessage->getSeqNumber());
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
    for(int p=0;p<ACKS.size();p++)
    {
        if(ACKS[p]==false)
        {z=0;
        break;
        }
    }
    if(z==1)
    {
        outputFile.open("../output.txt");
        if (!outputFile.is_open()) {
            cout << "Error opening output file";
        } else {
            for (const auto& msg : processedMessages) {
                outputFile << msg << endl;
            }
            outputFile.close();
        }
    }

}
