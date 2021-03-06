#include <memory>
#include "Input_Parser.h"

Input_Parser::Input_Parser(GameStateSubject &subject, std::shared_ptr<Renderer> my_renderer, std::string binding_filename) :game_state_subject(subject){
    this->Engine_State=new Game_Engine_State_Observer(game_state_subject);
    bindings.loadBinding(binding_filename);
    //bindings.loadBinding("in_game_bindings.cfg");
    std::shared_ptr<Event_Scanner> input_events(new Event_Scanner(event, my_renderer ));
    this->input_events = input_events;
    rangeInputChanged=false;


}


Input_Parser::~Input_Parser(void){

    //delete input_events;
    delete Engine_State;
    
    
}

const std::unordered_map<std::string,bool> Input_Parser::getCurrentCommands(){ 
        return curr_commands;
    }

const std::unordered_map<std::string,float> Input_Parser::getRangeInput(){ return curr_range_input; }

const bool Input_Parser::didRangeInputChange(){
    return this->rangeInputChanged;
}

void Input_Parser::scanInput(){
    
    input_events->scanInput();
    std::unordered_map<std::string, bool> curr_key_map = input_events->getTactileMap(CURRENT_MAP);
    std::unordered_map<std::string, float> curr_range_input_map = input_events->getRangeMap(CURRENT_MAP);
    std::unordered_map<std::string, bool> prev_key_map = input_events->getTactileMap(PREVIOUS_MAP);
    std::unordered_map<std::string, float> prev_range_input_map = input_events->getRangeMap(PREVIOUS_MAP);  
    if (curr_range_input_map!=prev_range_input_map) { 
        this->rangeInputChanged=true; 
    } 
    else { 
        this->rangeInputChanged=false; 
    }  
    //std::cout << (curr_key_map!=prev_key_map) << "   " << (curr_range_input_map!=prev_range_input_map) << std::endl;
    if ((curr_key_map!=prev_key_map)||(curr_range_input_map!=prev_range_input_map)){
        std::unordered_map<std::string, bool> curr_key_map = input_events->getTactileMap(CURRENT_MAP);
        std::unordered_map<std::string, float> curr_range_input_map = input_events->getRangeMap(CURRENT_MAP);
        std::unordered_map<std::string, bool> curr_command_map = bindings.getCommandMapFromKeycodes(curr_key_map);
        this->curr_range_input = curr_range_input_map;
        this->curr_commands = curr_command_map;


        //if (curr_key_map.find(SDLK_ESCAPE)!=curr_key_map.end()){ game_state_subject.setState(QUIT); }

        //std::cout << "Prev: ";
        //print_map(prev_command_map);
        //std::cout << "Curr: ";
        //print_map(curr_command_map);
    }
}

void Input_Parser::print_map(const std::unordered_map<std::string,bool> this_map){
    for (const std::pair<std::string,bool> this_item:this_map){
        std::cout << this_item.first << ": " << this_item.second << ", ";
    }
    std::cout << std::endl;
}