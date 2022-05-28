#pragma once
#ifndef Int2_hpp
#define Int2_hpp

struct Int2 {
    union {
        struct {
            int x;
            int y;
        };
        int f[2];
    };
};

#endif