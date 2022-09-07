# Game-server-demo
Learning to write a simple game server demo.

* Buffer

    User defined buffer for temporarily store the data received or need to be sent.

* Packet

    All messages are transferred as packets, 

* ConnectObj

    A connect-object is a wrap of a connected socket between server and client which provides interface to get received packet and send packet for user and can temporarily store the data from or to the net.

    Once there are data from net, they will be stored in `read buffer`, then user can get and process them. And once there are data need to be sent, users can store them in `write buffer`, then they will be sent automaticly.

* NetworkBase

    It manages several ConnectObjs.

* NetworkListner

    Child class of NetworkBase for listen and accept.
