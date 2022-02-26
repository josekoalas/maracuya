//project fresa, 2017-2022
//by jose pazos perez

#pragma once

#include <variant>

//: Follow the instructions on fresa/ecs/ecs.h to create a file like this

namespace Fresa::Component
{
    struct Test {
        Serialize(Test, i, j);
        int i;
        float j;
    };
    
    using ComponentType = std::variant<Test>;
}
