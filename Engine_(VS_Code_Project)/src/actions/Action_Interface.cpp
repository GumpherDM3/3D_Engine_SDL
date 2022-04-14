
#include "actions/Action_Interface.h"
#include "render/Camera.h"
#include <string>
#include <iostream>

const bool IAction::isRunning(){ return this->is_running; }

const std::string IAction::getName() { return this->name; }

const bool IAction::isReadyToDestroy(){ return this->readyToDestroy; }

void IAction::trigger(){ 
    this->is_key_pressed=true;
    this->is_running=true; 
}

Triangle_Modifier* IAction::getMeshModification() const{
    return mesh_modification;
}

JumpAction::JumpAction(std::string command_name){
    //passthrough
    this->command_name=command_name;
    this->is_key_pressed=false;
    this->is_running=false;
    this->readyToDestroy=false;
    this->mesh_modification = NULL;
}

void JumpAction::update(bool key_pressed){
    // Place Holder
    if (key_pressed){ is_running=true; } else { is_running=false; }
    if (is_running){

        std::cout << "Jump Pressed!";
    }
    is_running=false;
    this->readyToDestroy=true;
}

TwoAxisRangeCommand::TwoAxisRangeCommand(std::string command_name, Camera* this_camera, float x_range, float y_range):x_range(x_range),y_range(y_range){    
    this->command_name = command_name;
    is_running=true;
    this->mesh_modification = NULL;
    this->this_camera = this_camera;
}


void TwoAxisRangeCommand::update(bool key_pressed){
    if (this->mesh_modification!=NULL){ this->mesh_modification->clearMeshAssignments();}
    if (is_running){
        std::cout<< "  Applying TwoAxisMovement X: " << x_range << " Y: " << y_range;
        Vec3d rotation_vector;
        float mouse_sensitivity=360.0f;
        rotation_vector.setX(-y_range*mouse_sensitivity);
        rotation_vector.setY(x_range*mouse_sensitivity);
        rotation_vector.setZ(0);
        this_camera->rotateCamera(rotation_vector);
        
        //mesh_modification = new Rotator(rotation_vector.getX(), rotation_vector.getY(), rotation_vector.getZ(),Vec3d(0,0,0));
        
        this->is_running=false;
    }
    //this->is_running=false;
    this->readyToDestroy=true;
}

TwoAxisRangeCommand::~TwoAxisRangeCommand(){
    delete mesh_modification;
    
}





MoveAction::MoveAction(std::string command_name, Camera* this_camera, Vec3d direction, float attack, float release, float max_speed, float FPS){
    this->speed=0;
    this->is_running=false;
    this->FPS=FPS;
    this->max_speed = max_speed;
    this->attack_speed_delta = max_speed/(attack * FPS);
    this->release_speed_delta = max_speed/(release * FPS);
    this->speed;
    this->is_key_pressed=false;
    this->action_state=OFF;
    this->max_speed=max_speed;
    this->command_name = command_name;
    this->readyToDestroy=false;
    this-> direction = direction;
    this->mesh_modification = NULL;
    this->this_camera = this_camera;

}

void MoveAction::setActionState(){
    
    switch (action_state)
    {
    case OFF:{
        if (is_key_pressed) { action_state=TRIG_ATTACK; }
        
        break;
    }
    case TRIG_ATTACK:{
        is_running = true;
        action_state = ATTACK;
        break;
    }
    case ATTACK:{
        if(is_key_pressed){
            if (speed>=max_speed) { action_state=SUSTAIN; }
        }else{ 
            is_key_pressed=false;
            action_state = TRIG_RELEASE; 
        }
        break;
    }
    case SUSTAIN:{
        if(!is_key_pressed) { 
            is_key_pressed=false;
            action_state = TRIG_RELEASE; 
        }
        break;
    }
    case TRIG_RELEASE:{
        action_state=RELEASE;
        break;
    }
    case RELEASE:{
        if (is_key_pressed){ action_state=TRIG_ATTACK; }
        else{
            if(speed<=0){ 
                action_state=OFF; 
                this->mesh_modification = NULL;
            }
            else { action_state=RELEASE; }
        }
        break;
    }
    default:
        break;
    }
}

void MoveAction::setAttack(float attack){ this->attack_speed_delta = (attack * FPS)/max_speed; }

void MoveAction::setRelease(float release){ this->release_speed_delta = (release * FPS)/max_speed; }
  
    
void MoveAction::update(bool key_pressed){
    if (this->mesh_modification!=NULL){ this->mesh_modification->clearMeshAssignments();}
    this->is_key_pressed=key_pressed;
    setActionState();
    switch (action_state)
    {
    case OFF:{
        is_running=false;
        speed=0;
        break;
    }
    case TRIG_ATTACK:{
        std::cout << "TRIG_ATTACK  ";
        is_running=true;
        break;
    }
    case ATTACK:{
        std::cout << "ATTACK  ";
        speed+=attack_speed_delta;
        break;
    }
    case SUSTAIN:{
        std::cout << "SUSTAIN  ";
        speed=speed;
        break;
    }
    case TRIG_RELEASE:
        std::cout << "TRIG_RELEASE  ";
        //Place Holder
        break;
    case RELEASE:{
        std::cout << "RELEASE  ";
        speed-=release_speed_delta;
        break;
    }
    default:
        break;
    }

    if (speed>0){ 
        Vec3d translation_vector;
        translation_vector.setX(direction.getX()*speed);
        translation_vector.setY(direction.getY()*speed);
        translation_vector.setZ(direction.getZ()*speed);

        //Vec3d currCameraPos = this->this_camera->getCameraPos();
        //Vec3d newCameraPos = currCameraPos + translation_vector;
        //Vec3d newCameraPos = Vec3d(currCameraPos.getX()*speed, currCameraPos.getY()*speed, currCameraPos.getZ()*speed);

	    this->this_camera->setCameraPos(translation_vector);
        std::cout << "    " << command_name << ": " << translation_vector.getX() << "," << translation_vector.getY() << ", " << translation_vector.getZ() << ": " << this->speed;
        
        /*        
        

        mesh_modification = new Translator(translation_vector.getX(), translation_vector.getY(), translation_vector.getZ());
        */
        }

    // use speed to update meshes here

    //std::cout << "    " << command_name << ": " << this->speed;
}

MoveAction::~MoveAction(){
    delete mesh_modification;
    
}