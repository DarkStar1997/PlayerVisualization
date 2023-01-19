#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/box2d.h>
#include <fmt/core.h>

int main()
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_dynamicBody;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body * groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3;
    groundBody->CreateFixture(&fixtureDef);
    float timeStep = 1 / 60.0f;
    int32_t velocityIterations = 6, positionIterations = 2;
    for(size_t i = 0; i < 60; i++)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        
        size_t body_index = 0;
        for(b2Body * node = world.GetBodyList(); node; node = node->GetNext(), body_index++)
        {
            b2Body * body = node;
            b2Vec2 position = body->GetPosition();
            float angle = body->GetAngle();
            fmt::print("body {} - x: {} y: {:.2f} theta: {}\n", body_index, position.x, position.y, angle);
        }

    }
}
