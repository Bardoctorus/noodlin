#include "node_test.h"


void NodeTest::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("setChangeMe", "p_string"), &NodeTest::setChangeMe);
    ClassDB::bind_method(D_METHOD("getChangeMe"), &NodeTest::getChangeMe);
    ClassDB::bind_method(D_METHOD("incrementSeconds"), &NodeTest::incrementSeconds);
    ClassDB::bind_method(D_METHOD("getSecondsElapsed"), &NodeTest::getSecondsElapsed);
    ClassDB::bind_method(D_METHOD("getTestName"), &NodeTest::getTestName);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "changeMe"), "setChangeMe","getChangeMe");

}

NodeTest::NodeTest()
{
    timePassed = 0.0;
    
    changeMe = "Change Me"; 
}


NodeTest::~NodeTest()
{

}

void NodeTest::setChangeMe(String p_string)
{
    changeMe = p_string;
}


String NodeTest::getTestName() const
{
    return NodeTestName;
}



String NodeTest::getChangeMe() const 
{
    return changeMe;
}


void NodeTest::incrementSeconds()
{
    timePassed += 1;
}


double NodeTest::getSecondsElapsed() const
{
    return timePassed;
}




