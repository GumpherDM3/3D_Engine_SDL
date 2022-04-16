#ifndef CAMERA_H
#define CAMERA_H

#include "utility/Vec3d.h"
#include "utility/Mat4x4.h"


class Camera{
    public:
        Camera();
        Mat4x4 buildViewMatrix();

        void setCameraPos(Vec3d pos_vector);
        void setCameraDir(Vec3d dir_vector);
        void rotateCamera(Vec3d rotation_vector);
        Vec3d getCameraPos();
        Vec3d getCameraDir();

        

    private:
        Vec3d calc_vTarget();
        Vec3d vTarget;
        Vec3d camera;
        Vec3d lookVector;
        //Vec3d newForward;
        float pitch_delta=0.0f;
        float yaw_delta=0.0f;
        float pitch_total=0.0f;
        float yaw_total=0.0f;

};

#endif