package networks_project;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    parameters :
        int WS=default(3);
        int WR=default(3);
        double TO=default(10);
        double PT=default(0.5);
        double TD=default(1.0);
        double ED=default(4.0);
        double DD=default(0.1);
    @display("bgb=1057,511");
    submodules:
        node0: Node0 {
            @display("p=243,191;i=device/laptop;is=vl");
        }
        node1: Node1 {
            @display("p=802,199;i=device/laptop;is=vl");
        }
        coordinator: Coordinator {
            @display("p=494,394;i=device/server;is=vl");
        }
    connections:
        coordinator.outGateNode1 --> node1.inGateCoord;
        coordinator.outGateNode0 --> node0.inGateCoord;
        node0.outGate --> node1.inGateNode;
        node1.outGate --> node0.inGateNode;
}

