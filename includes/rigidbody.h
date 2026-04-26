#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp> 

struct RigidBody {
    glm::vec3 velocity{0.0f};
    glm::vec3 force{0.0f};

    float mass = 1.0f;
    bool useGravity = true;
    float frictionDamping  = 0.98f; 

    void applyForce(const glm::vec3& f);
    void integrate(glm::vec3& position, float dt);
};


#endif 