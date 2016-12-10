#ifndef INFORMATICA_OLYMPIADE_2016_2017_TESTS_DIRECTION_H
#define INFORMATICA_OLYMPIADE_2016_2017_TESTS_DIRECTION_H

enum class Direction {
    UP,
    RIGHT,
    DOWN ,
    LEFT
};

inline std::ostream& operator<<(std::ostream& os, const Direction direction)
{
    switch(direction) {
        case Direction::UP:
            os << "UP";
            break;

        case Direction::DOWN:
            os << "DOWN";
            break;

        case Direction::LEFT:
            os << "LEFT";
            break;

        case Direction::RIGHT:
            os << "RIGHT";
            break;
    }

    return os;
}
#endif //INFORMATICA_OLYMPIADE_2016_2017_TESTS_DIRECTION_H
