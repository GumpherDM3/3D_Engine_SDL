#include "Mat4x4.h"

Mat4x4::Mat4x4(){
    // Initialize empty 4x4 matrix to 0.0f
    for (int x=0;x<4;x++){
        for (int y=0;y<4;y++){
            m[x][y] = 0.0f;
        }
    }
        
}