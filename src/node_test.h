#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/node.hpp"

using namespace godot;

class NodeTest : public Node {
    GDCLASS(NodeTest, Node)

   
    protected:
	static void _bind_methods();

    private:
        double timePassed = 0.0;
        const String NodeTestName = "Test Node";
        String changeMe = "Change Me"; 

    public:
        NodeTest();
        ~NodeTest();    
        String getTestName() const;
        void setChangeMe(String p_string);
        String getChangeMe() const ;
        void incrementSeconds();
        double getSecondsElapsed() const;
     



};