#pragma once
#ifndef Vector3_hpp
#define Vector3_hpp

struct Vector3 {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float f[3];
    };
};

#endif