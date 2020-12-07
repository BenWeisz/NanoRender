#include <iostream>

class Room {
    public:
        double width;
        double length;

        Room() {};

        Room(const Room& obj) {
            length = obj.width;
            width = obj.length;
        };

        double calculateArea() {
            return length * width;
        };
};

int main() {
    Room room1;
    room1.width = 10;
    room1.length = 7;
    
    Room room2 = room1;

    std::cout << room2.calculateArea() << std::endl;
}