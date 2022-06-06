#pragma once
#ifndef Vector2_hpp
#define Vector2_hpp

struct Vector2 {
    union {
        struct {
            double x;
            double y;
        };
        double f[2];
    };
};

#endif