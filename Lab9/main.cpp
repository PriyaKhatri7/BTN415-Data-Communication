#include <iostream>
#include <string>

struct new_packet {
    char number;
    unsigned char urg : 1;
    unsigned char ack : 1;
    unsigned char psh : 1;
    unsigned char rst : 1;
    unsigned char syn : 1;
    unsigned char fin : 1;
    unsigned char : 2; //padding
    unsigned int size;
    char* data;
    unsigned char crc;
    unsigned int checksum;
};

void display(unsigned char byte) {
    for (int k = 0; k < 8; k++) {
        std::cout << (int)(byte >> 7);
        byte = byte << 1;
    }
    std::cout << std::endl;
}

unsigned char calculate_packet_crc(new_packet my_packet) {
    //in the new_package data field, ignore other struct fields using a CRC circuit as shown in the image below
    unsigned char biteregister, enter, send, state = 0;
    int size = strlen(my_packet.data);
    for (int i = 0; i < size; i++)
    {
        biteregister = my_packet.data[i];

        for (int j = 0; j < 8; j++)
        {
            enter = biteregister >> 7;
            send = ((state & 0x80) >> 7) ^ //similar to slides - examples
                ((state & 0x20) >> 5) ^ ((state & 0x04) >> 2) ^ enter;
            state = (state << 1) + send;
            biteregister = biteregister << 1;
        }
    }
    return state;
}

unsigned int calculate_packet_checksum(new_packet my_packet) {
    unsigned int sum = 0;
    unsigned int* ptr = (unsigned int*)my_packet.data; //assigns the address of ptr

    for (unsigned int i = 0; i < strlen(my_packet.data) / sizeof(unsigned int); i++) //
    {
        sum += *ptr++;
    }
    int modulus = strlen(my_packet.data) % sizeof(unsigned int);
    int reminder = 0;
    if (modulus != 0) {
        memcpy(&reminder, ptr, modulus);
    }
    sum += reminder;
    return sum;
}

int main() {

    new_packet my_packet;

    my_packet.number = 1;
    my_packet.urg = 0;
    my_packet.ack = 1;
    my_packet.psh = 0;
    my_packet.rst = 1;
    my_packet.syn = 0;
    my_packet.fin = 1;
    std::cout << "Enter your message " << std::endl;
    std::string DataBuffer;
    std::getline(std::cin, DataBuffer);
    my_packet.data = new char[DataBuffer.length()];
    strcpy(my_packet.data, DataBuffer.c_str());
    my_packet.crc = calculate_packet_crc(my_packet);
    my_packet.checksum = calculate_packet_checksum(my_packet);

    return 0;
}